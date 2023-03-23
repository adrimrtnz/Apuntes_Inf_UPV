//EJEMPLO LUCHADOR 

threshold_ammo(20).
threshold_health(25).
flashed.

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

+flash : not(flashed)
<-
  +flashed;
  ?velocity([X,Y,Z]);
  -+velocity([2+X,2+Y,2+Z]).

+get_health : health(X) & threshold_health(Y) & X < Y
<-
  ?base(B);
  +goto(B);
  -patrolling.

+patrol : not(patrolling) & pack_taken(T,N)
<-
  +patrolling.

+get_ammo : ammo(X) & threshold_ammo(Y) & X < Y
<-
  ?base(B);
  +goto(B);
  -patrolling.

+friends_in_fov(ID,Type,Angle,Distance,Health,Position)
<-
  .look_at(Position);
  .shoot(3,Position).

+target_reached(T): patrolling & team(200)
  <-
  ?patroll_point(P);
  -+patroll_point(P+1);
  -target_reached(T).

+patroll_point(P): total_control_points(T) & P<T
<-
  ?control_points(C);
  .nth(P,C,A);
  .goto(A).
 // .print("Voy a Pos: ", A).

+patroll_point(P): total_control_points(T) & P==T
<-
  -patroll_point(P);
  +patroll_point(0).
 
 /*  En modo arena no hace falta disparar al enemigo  
+enemies_in_fov(ID,Type,Angle,Distance,Health,Position)
<-
  .shoot(3,Position).
*/
  

