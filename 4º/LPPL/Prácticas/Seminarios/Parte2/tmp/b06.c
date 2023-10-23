// Ejemplo sintactico-semantico (absurdo) sin errores.
// Comprobad el resultado con la funcion "verTdS". Verificad
// que los parametros se situen en orden inverso en la TdS
// y que tengan desplazamientos negativos.
//----------------------------------------------------------
bool a;
int  b[27];
struct { int  c1; bool c2; int  c3; } c;

int F (int x, int y)
{ 
   bool a[27]; int b; 

  return y-x;
}

int d[27];
int e;

int main()
{
  int x[27];
  struct { int  y1; bool y2; } y; 
  int z; 

  read(z); read(e);

  if (z < e) print( F(z, e));
  else print( F(e, z));

  return 0;
}
