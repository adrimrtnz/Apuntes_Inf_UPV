/*****************************************************************************/
/**  Ejemplo de FLEX: S E M - 1           2023-2024 <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "header.h"
#include "asin.h"

#define  retornar(x) {if (verbosidad) ECHO ; return (x) ; }
%}
/*-----------------------------------------------------------------------------
  Estas opciones evitan "warnings" innecesarios y permiten obtener el
  numero de linea actual en la variable global "yylineno".
-----------------------------------------------------------------------------*/
%option noinput       
%option nounput       
%option yylineno  

delimitador    [ \t\n]+
digito         [0-9]
letra          [a-zA-Z]
entero         {digito}+
real           {digito}+"."{digito}*|"."{digito}+
constante      {entero}|{real}
id             {letra}[a-zA-Z0-9\_]*
comentario     \/\/.*\n

/*-----------------------------------------------------------------------------
  Tiene que haber, como mínimo, tantas expresiones como símbolos
-----------------------------------------------------------------------------*/
%%
{delimitador}  { if (verbosidad) ECHO; }
{comentario}   { if (verbosidad) ECHO; }

int            { retornar (INT_);      }
bool           { retornar (BOOL_);     }
struct         { retornar (STRUCT_);   }
while          { retornar (WHILE_);    }
read           { retornar (READ_);     }
print          { retornar (PRINT_);    }
if             { retornar (IF_);       }
else           { retornar (ELSE_);     }
true           { retornar (TRUE_);     }
false          { retornar (FALSE_);    }
return         { retornar (RETURN_);   }

"{"            { retornar (ALLAVE_);   }
"}"            { retornar (CLLAVE_);   }
"["            { retornar (ACORCH_);   }
"]"            { retornar (CCORCH_);   }
">="           { retornar (GEQ_);      }
"<="           { retornar (LEQ_);      }
">"            { retornar (GREATER_);  }
"<"            { retornar (LESSTHAN_); }
"=="           { retornar (EQ_);       }
"!="           { retornar (NEQ_);      }
"!"            { retornar (NOT_);      }
"="            { retornar (ASIG_);     }
"&&"           { retornar (AND_);      }
"||"           { retornar (OR_);       }
";"            { retornar (PUNTCOMA_); }
","            { retornar (COMA_);     }
"."            { retornar (PUNT_);     }

"++"           { retornar (INCR_);     }
"--"           { retornar (DECRE_);    }
"+"	           { retornar (MAS_);      }
"-"            { retornar (MENOS_);    }
"*"            { retornar (POR_);      }
"/"            { retornar (DIV_);      }
"("            { retornar (APAR_);     }
")"            { retornar (CPAR_);     }
{constante}    { retornar (CTE_);      }
{id}           { retornar (ID_);       }

.	             { yyerror("Caracter desconocido"); }

%%
/*****************************************************************************/
