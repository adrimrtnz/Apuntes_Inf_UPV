// Ejemplo con errores en operadores aritmeticos: 8 errores
//---------------------------------------------------------
int main() 
{
  int x[4];
  int i;
  bool b;

  read(b);             // El argumento del "read" debe ser "entero"
  while (i) {          // La expresion del "while" debe ser "logica"
    x[2] = i * b;      // Error de tipos en "expresion multiplicativa"
    x[2] = x[i] + b;   // Error de tipos en "expresion aditiva"
    i = x;             // El identificador debe ser de tipo simple
    i = -b;            // Error en "expresion unaria"
    ++b;               // Error en operador prefijo
  }
  print(x[20] > i);    // La expresion del "print" debe ser "entera"

  return 0;
}
