//TEAM_ALLIED 

threshold_ammo(20).
threshold_health(25).

+flag (F): team(100) 
  <-
  ?base(B);
  .create_control_points(B, 100, 1, C);
  .nth(0,C,P);
  .get_service("general");
  .wait(5000); // para no ir delante de todos
  .goto(P).

+target_reached(T): team(100) & not goint_to_flag
  <-
  +goint_to_flag;
  .print("target_reached");
  ?flag(F);
  .goto(F).

+flag_taken: team(100) 
  <-
  .print("In ASL, TEAM_ALLIED flag_taken");
  .get_service("general");
  ?general(G);
  ?position(P);
  .send(G, tell, tenemos_bandera(P));
  .print("Mando mensaje a General: ", G);
  ?base(B);
  +returning;
  .goto(B);
  -exploring.

+tenemos_bandera(Pos)[source(G)]: not tengo_bandera
 <-
   .goto(Pos);
   -+flag(Pos).

+heading(H): exploring
  <-
  .reload;
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

+health(X): X < 15 & tengo_bandera
<-
// Mandar posición
.print("Soy el portador y voy a morir").

+health(X): threshold_health(Y) & X < Y & not cureMe
  <-
  +cureMe;
  /**.get_medics; // Con esto se crea la lista myMedics(Medics_List)
  ?myMedics(Medics_List);
  ?position(P);
  .send(Medics_List, tell, ir_a(P)); 
  **/
  // Meter la petición de botiquín
  +avrakedabra.

+enemies_in_fov(ID,Type,Angle,Distance,Health,Position) : 
  not friends_in_fov(ID_F,Type_F,Angle,Distance_F,Health_F,Position_F) 
  <-
  .shoot(3,Position).

+enemies_in_fov(ID,Type,Angle,Distance,Health,Position) : 
  avrakedabra & not friends_in_fov(ID_F,Type_F,Angle,Distance_F,Health_F,Position_F)
  <-
  ?ammo(A);
  .print("avrakedabra");
  .shoot(A,Position).