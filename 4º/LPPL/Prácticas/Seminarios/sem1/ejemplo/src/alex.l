/*****************************************************************************/
/**  Ejemplo de FLEX: S E M - 1           2023-2024 <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "header.h"
/*#include "asin.h"*/

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
id             {letra}[{letra}{digito}\_]*

comentario     \/\/.*\n

boolean        TRUE|FALSE
opIncre        "++"|"--"
opLogic        &&|"||"
opIgual        ==|!=
opRel          >|<|>=|<=
reservada      "int"|"bool"|"read"|"print"|"if"|"else"|"while"|"struct"
tipo_simple    "int"|"bool"

/*-----------------------------------------------------------------------------
  Tiene que haber, como mínimo, tantas expresiones como símbolos
-----------------------------------------------------------------------------*/
%%
{delimitador}  { if (verbosidad) ECHO; }

{reservada}    { retornar (RESERVED_); }
{opIncre}      { retornar (OPINC_);    }
{boolean}      { retornar (BOOL_);     }

"+"	           { retornar (MAS_);      }
"-"            { retornar (MENOS_);    }
"*"            { retornar (POR_);      }
"/"            { retornar (DIV_);      }
"("            { retornar (APAR_);     }
")"            { retornar (CPAR_);     }
{entero}       { retornar (CTE_);      }
{real}         { retornar (CTER_);     }
{id}           { retornar (ID_);       }

{opLogic}      { retornar (OPLOG_)     }
{opIgual}      { retornar (OPIG_)      }
{opRel}        { retornar (OPREL_)     }

.	             { yyerror("Caracter desconocido"); }

%%
/*****************************************************************************/
