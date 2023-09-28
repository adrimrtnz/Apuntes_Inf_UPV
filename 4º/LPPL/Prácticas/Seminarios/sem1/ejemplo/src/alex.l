/*****************************************************************************/
/**  Ejemplo de FLEX: S E M - 1           2023-2024 <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "header.h"

#define  retornar(x) {if (verbosidad) ECHO; }
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
real           {digito}+"." | "."{digito}+ | {digito}+"."{digito}*
id             {letra}[{letra}{digito}\_]*
comentario     "//"["Meter lo que sea, nos la pela"]"\n"
/*-----------------------------------------------------------------------------
  Tiene que haber, como mínimo, tantas expresiones como símbolos
-----------------------------------------------------------------------------*/
%%
{delimitador}  { if (verbosidad) ECHO; }
"+"	           { retornar (MAS_);      }
"-"            { retornar (MENOS_);    }
"*"            { retornar (POR_);      }
"/"            { retornar (DIV_);      }
"("            { retornar (APAR_);     }
")"            { retornar (CPAR_);     }
{entero}       { retornar (CTE_);      }
{real}         { retornar (CTER_);     }
{id}           { retornar (ID_);       }
.	             { yyerror("Caracter desconocido"); }

%%
/*****************************************************************************/
