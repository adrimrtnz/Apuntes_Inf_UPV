// Ejemplo de manipulacion de funciones: 9 errores
//------------------------------------------------

bool X[20];
bool main (int A, bool A, int B)  // Parametro repetido
{
  bool A;                 // Identificador de variable repetido
  return 14;              // Error de tipos en el "return" 
}

int Y (int A, bool B)   
{
  int X[10];
  return X;               // En la expresion del 'return'
}

int main ()               // Identificador de funcion repetido
{
  int x; bool y;             
  x = 14;  y = true;
  if (x) {                // La expresion del `if' debe ser 'logico'
    x = X(x, y);          // La variable debe ser una funcion
    x = Y(y, x);          // En el dominio de los parametros actuales
  }
  else {}
  return 0;                
}                         // [Opcional] Hay mas de un `main'
