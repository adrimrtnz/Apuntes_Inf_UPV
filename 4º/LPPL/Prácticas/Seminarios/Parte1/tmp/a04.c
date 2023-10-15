// Ejemplo de manipulacion de registros 
//-------------------------------------
int main()
{
  struct{ int c1; bool c2; } r;  int x;
  
  read(x); r.c1 = x * 7;
  if ( r.c1 >= 0 ) r.c2 = true;
  else { r.c2 = false; r.c1 = -r.c1; }
  if (r.c2 == false) print(r.c1);
  else {}
  
  return 0;
}
