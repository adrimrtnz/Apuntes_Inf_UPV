//Alumno: Adrian Martinez Martinez

threshold_ammo(20).
threshold_health(25).

+flag(F): team(200)
<-
  .create_control_points(F,100,3,C);
  +control_points(C);
  //.wait(5000);
  .length(C,L);
  +total_control_points(L);
  +patrolling;
  +patroll_point(0);
  .print("Got control points:", C).

// -------------- REABASTECIMINETO ------------------- //
+pack_taken(T,N)
<-
  .print("Pack tacken de tipo: ", T);
  if(T == "medic") {
    .print("SALUD RECUPERADA, Me siento mejor");
    -+threshold_health(25);
    -get_health(H);
  };
  
  if(T == "fieldop") {
    .print("RECARGA DE AMMO, piu piu");
    -get_ammo(A);
  };

  /*
  Si se recoge paquete por estar cerca pero estaba en modo covarde, retomalo
  */
  if (coward) {
    -+coward;
  } else {
    ?patroll_point(P);
    -+patroll_point(P);
  }.

+get_ammo(Position) : not pack_taken(T,N) & T == 1002
<-
  .print("Voy a por AMMO");
  .goto(Position).

/* 
  Le damos prioridad a que si se encuentra un paquete y lo necesita,
  vaya a por él por encima de todo
*/
+packs_in_fov(ID,Type,Angle,Distance,Health,Position)
: Type == 1002 & not get_ammo(Position) & not friends_in_fov(ID,Type,Angle,Distance,Health,Position)
<-
  ?ammo(X);
  ?threshold_ammo(Y);
  ?position(P);
  
  if (X < Y) {
    .print("Veo pack AMMO y voy a por ello AMMO: ", X);
    .look_at(Position);
    +get_ammo(P);
    -patrolling;
  }.

+get_health(Position) : not pack_taken(T,N) & T == 1001
<-
  .print("Voy a por SALUD");
  .goto(Position).
  

+packs_in_fov(ID,Type,Angle,Distance,Health,Position)
: Type == 1001 & not get_health(Position) & not friends_in_fov(ID,Type,Angle,Distance,Health,Position)
<-
  ?threshold_health(X);
  ?health(Y);
  if (Y < X) {
    .print("Veo pack health y voy a por ello SALUD: ", Y);
    .look_at(Position);
    +get_health(Position);
    -patrolling;
  }.


// ----------------- COBARDE ---------------------- //
/*
  Si activa si la salud cae de un determinado umbral
*/
+coward
<-
  ?position([X,Y,Z]);
  if (X > 128 & Z < 128) {
    .print("Me viene mejor la esquina sup-der");
    .goto([240,0,15]);
  };
  if (X < 128 & Z < 128) {
    .print("Me viene mejor la esquina sup-izq");
    .goto([15,0,15]);
  };
  if (X > 128 & Z > 128) {
    .print("Me viene mejor la esquina inf-der");
    .goto([240,0,240]);
  };
  if (X < 128 & Z > 128) {
    .print("Me viene mejor la esquina inf-izq");
    .goto([15,0,240]);
  };
  -patrolling;
  .print("He elegido mi destino").

+target_reached(T) : coward
<-
  .wait(500); // Espera un poco, la cobardia cansa
  .print("He llegado a la esquina siendo un cobarde");
  .print("QUE HE HECHO?, tengo que volver a la batalla");
  -coward;
  .print("Ya no soy un COBARDE");
  +retoma_tu_vida;
  .print("Retomare mi deber").

+retoma_tu_vida
<-
  ?ammo(A);
  ?threshold_ammo(TA);
  ?health(H);
  if (A < TA | H < 25) {
    .print("Voy a intentar ir a base a por suministros");
    ?base(B);
    .goto(B);
  } 
  else {
    .print("Vuelvo a patrullar las calles");
    ?flag(F);
    .create_control_points(F,100,3,C);
    +control_points(C);
    .length(C,L);
    +total_control_points(L);
    +patrolling;
    +patroll_point(0);
  }.
  -retoma_tu_vida.


// ----------------------------------------------- //
+health(X): threshold_health(Y) & X < Y
<-
  if (not coward) {
    .print("Mi planeta me llama, adios!");
    +coward;
  }.


/*
  NO PARECE FUNCIONAR EL .turn(R)
  Si me hacen daño pero no tengo enemigos a la vista,
  miro a los lados
*/
+health(X): 
  not friends_in_fov(ID,Type,Angle,Distance,Health,Position) 
  & position([X,Y,Z])
<-
  .print("Alguien me dispara y no se de donde");
  .turn(0.5).

  /*
  // Mira derecha
	.look_at([X,Y,Z+1]);
	.wait(500);

  // Mira abajo
	.look_at([X+1,Y,Z]);
	.wait(500);

  // Mira izquierda
	.look_at([X,Y,Z-1]);
	.wait(500);

  // Mira arriba
	.look_at([X-1,Y,Z]);
	.wait(500).
  */


+patrol : not(patrolling) & pack_taken(T,N)
<-
  -pack_taken(T,N);
  ?patroll_point(P);
  -+patroll_point(P);
  +patrolling.


+ammo(X): threshold_ammo(Y) & X < Y
<-
  /*
    La comprobacion del coward estaba antes en 
    la guarda de arriba como "& not coward", pero
    no parece hacerle caso
  */
  if (not coward) {
    ?base(B);
    .goto(B);
    -patrolling;
  }.


/*
  NO FUNCIONA BIEN, ENTRA EN UN BUCLE PARANORMAL
  PERO LA DEJO COMENTADA PARA FUTUROS EXPERIMENTOS
  Si estoy huyendo pero tengo enemigos a la vista,
  varío un poco mi destino
*/
/*
+friends_in_fov(ID,Type,Angle,Distance,Health,Position)
: coward
<-
  .print("Quiero huir pero tengo enemigos en mi camino");
  ?destination([X,Y,Z]);

  if (Z < 128) {
    .goto([X,0,Z+10]);
  }else {
    .goto([X,0,Z-10]);
  };
  .wait(200).
  */

+friends_in_fov(ID,Type,Angle,Distance,Health,Position)
<-
  ?ammo(A);
  if (A > 0) {
    .look_at(Position);
    .shoot(4,Position);

    // Si lo ves dispara, pero solo persigue si no eres un gallina
    if (not coward) {
      .goto(Position); 
    };
  }.

+target_reached(T): patrolling & team(200)
  <-
  ?patroll_point(P);
  -+patroll_point(P+1);
  -target_reached(T).

+target_reached(T): not patrolling
<-
  +retoma_tu_vida.

+patroll_point(P): total_control_points(T) & P<T
<-
  ?control_points(C);
  .nth(P,C,A);
  .goto(A).
 // .print("Voy a Pos: ", A).

+patroll_point(P): total_control_points(T) & P==T
<-
  /* Por dar variedad, cambia la ruta una vez completada */
  +retoma_tu_vida.
 
 /*  En modo arena no hace falta disparar al enemigo  
+enemies_in_fov(ID,Type,Angle,Distance,Health,Position)
<-
  .shoot(3,Position).
*/
  

