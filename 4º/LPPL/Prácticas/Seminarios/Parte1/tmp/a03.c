// Ejemplo de manipulacion de vectores 
//------------------------------------
int a[10];

int main()
{ int i;

  i = 0;
  while (i < 10) { a[i] = i;    i++; }
  i = 9;
  while (i >= 0) { print(a[i]); i--; } 
  
  return 0;
}
