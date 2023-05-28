//TEAM_ALLIED 

+flag (F): team(100) 
  <-
  .get_service("general");
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

+enemies_in_fov(ID,Type,Angle,Distance,Health,Position)
  <- 
  .shoot(3,Position).