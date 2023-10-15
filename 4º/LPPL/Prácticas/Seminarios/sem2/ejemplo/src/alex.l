/*****************************************************************************/
/** Ejemplo  S E M - 2                    2023-2024 <jmbenedi@prhlt.upv.es> **/
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
entero         {digito}+

%%

{delimitador}   {if (verbosidad) ECHO; }
"+"             { retornar (MAS_);     }
"-"             { retornar (MENOS_);   }
"*"             { retornar (POR_);     }
"/"             { retornar (DIV_);     }
"("             { retornar (APAR_);    }
")"             { retornar (CPAR_);    }
{entero}        { retornar (CTE_);     }
.		{ yyerror("Caracter desconocido") ;}
%%
