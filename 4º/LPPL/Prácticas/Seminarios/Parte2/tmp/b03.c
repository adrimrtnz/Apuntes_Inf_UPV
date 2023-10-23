// Ejemplo de manipulacion de vectores: 8 errores
//-----------------------------------------------
int main() 
{
  int  a[20];
  int  b; 
  bool c; 
  bool d[0];     // Talla inapropiada del array
  int  a;        // Identificador variable repetido
  bool b[21];    // Identificador del array repetido
  
  e = 27;        // Objeto no declarado
  c = a[2];      // Error de tipos en la "asignacion"
  a[4] = c;      // Error de tipos en la asignacion a un `array'
    
  a[c] = 1 ;     // El indice del "array" debe ser entero
  b[14] = 27;    // La variable debe ser de tipo "array"

  return 0;
}
