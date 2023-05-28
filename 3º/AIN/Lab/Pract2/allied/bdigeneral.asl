//TEAM_ALLIED

threshold_ammo(20).
threshold_health(25).

+flag (F): team(100)
  <-
  .register_service("general");
  .print("Soy el GENERAL, esta noche dormiremos en el INFIERNO!!!");
  .get_medics;
  .get_backups;
  .get_fieldops.

+flag_taken: team(100)
  <-
  .print("In ASL, TEAM_ALLIED flag_taken");
  ?base(B);
  +returning;
  .goto(B);
  -exploring.

+tenemos_bandera(Pos)[source(S)]: team(100)
 <-
  // Falta guardar NUEVA posición BANDERA
  //-+flag(Pos);
  .get_backups;
  .get_medics;
  .get_medics;
  ?myBackups(B);
  ?myMedics(M);
  ?myFieldops(F);
  .send(M, tell, tenemos_bandera(Pos));
  .send(B,tell, tenemos_bandera(Pos));
  .send(F, tell, tenemos_bandera(Pos));
  .print("[GENERAL]: El soldado ", S, " tiene la bandera.");
  .wait(2000);
  +checkAlive.

+portadorVivo[source(A)]
 <-
    -+sigueVivo.




+checkAlive 
<-
  if (not portadorVivo) {
    .print("El portador ha muerto");
    // Reanuda la búsqueda de la bandera
    // comunicar última posición bandera
  };
  if (portadorVivo) {
    -portadorVivo;
    .print("El portador sigue vivo");
  }.

+heading(H): exploring
  <-
  .wait(2000);
  .turn(0.375).

//+heading(H): returning
//  <-
//  .print("returning").

+target_reached(T): team(100)
  <-
  .print("target_reached");
  +exploring;
  .turn(0.375).

//+friends_in_fov(ID,Type,Angle,Distance,Health,Position)

+health(X): threshold_health(Y) & X < Y
  <-
  +avrakedabra.

// si veo un amigo no disparo
+enemies_in_fov(_,_,Angle,_,_,Position): not friends_in_fov(ID,Type,Angle,Distance,Health,Position_F) 
  <-
  .shoot(3,Position).

+enemies_in_fov(_,_,Angle,_,_,Position) : avrakedabra & not friends_in_fov(ID,Type,Angle,Distance,Health,Position_F)
  <-
  ?ammo(A);
  .shoot(A,Position).

// llega una solicitud de ayuda médica
+cureMe(Pos)[source(A)]: not askforcure & not selectMedic
  <-
  .get_medics;
  +askforcure;
  ?myMedics(M);
  +posMedic([]); // lista de posiciones de los médicos
  +idMedic([]); // lista de los IDs de los médicos
  .send(M,tell,cureMe(Pos));
  .wait(1000);
  !!selectMedic(Pos).

// eligo el médico más cercano
+!selectMedic(Pos): askforcure & not selectingMedic
  <-
  +selectingMedic;
  ?posMedic(B);
  ?idMedic(I);
  .length(B, Bl);

  if (Bl > 0) {
    .closestMedic(Pos, B, Medic);
    .nth(0,Medic,AAA);
    .nth(AAA,I,A);
    .send(A, tell, youCure);
    .send(I, tell, elseCure); // Esto hay que revisarlo
  };
  -posMedic(_);
  -idMedic(_);
  -selectingMedic;
  -askforcure.

// un médico me confirma que sigue vivo
+stillAlive(Pos)[source(A)]: askforcure & not selectMedic
 <- 
 .wait(500);
 //los medicos vivos se añaden a la lista
 ?posMedic(B);
 .concat(B,[Pos],B1); 
 -+posMedic(B1);
 ?idMedic(I);
 .concat(I,[A],I1); 
 -+idMedic(I1);
 -stillAlive(Pos).

//llega una solicitud de munición
+askAmmo(Pos)[source(A)]: not askForAmmo & not selectOp
 <-
 .wait(500);
 +askForAmmo;
 .get_fieldops;
 ?myFieldops(F);
 +posOp([]);
 //+IDOp([]);
 .send(F,tell,askAmmo(Pos));
 .wait(1000); // esperando respuesta de los operativos
 !!selectOp(Pos).

+!selectOp(Pos): askForAmmo & not selectOp
 <-
 +selectOp;
 .wait(500).
 