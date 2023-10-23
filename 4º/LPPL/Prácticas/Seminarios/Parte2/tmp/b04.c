// Ejemplo de manipulacion de registros: 5 errores
//------------------------------------------------
int main ( )
{
  struct { int  a1; bool a2; int  a3; } a;
  int  b;   bool c;
  struct {
    int  d1;
    bool d2;
    int  d1;                 // Nombre de campo repetido
  } c;                       // Identificador estructura repetido
  int e;

  b = c.c1 + 27;             // El identificador debe ser "struct"
  a.a2 = b * 2;              // Error en la "asignacion" a una"struct"
  c = a.a4 && true;          // Campo no declarado

   return 0;
}
