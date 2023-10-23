%{
#include <stdio.h>
#include "header.h"
}%

%token MAS_ MENOS_ POR_ DIV_ APAR_ CPAR_
%token CTE_ CTER_ ID_ OPIG_ OPREL_ RESERVED_

%%
expMat          : exp ;
exp             : exp MAS_ term | exp MENOS_ term | term ;
term            : term POR_


tipoSimp        : int | bool
listCamp        : tipoSimp ID_ ; | listCamp tipoSimp ID_ ;
decla           : declaVar | declaFunc
declaVar        : tipoSimp ID_ ; | tipoSimp ID_ [CTE_]; | struct { listCamp } ID_ ;
declaFunc       : tipoSimp ID_ ( paramForm ) { declaVarLocal listInst return expre ; }
paramForm       :  | listParamForm
listParamForm   : tipoSimp ID_ | tipoSimp ID_, listParamForm
declaVarLocal   :  | declaVarLocal declaVar  
cons            : CTE_ | TRUE | FALSE
%%