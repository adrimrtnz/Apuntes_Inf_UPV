/*****************************************************************************/
/** Ejemplo  S E M - 2                    2023-2024 <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "header.h"
%}

%token BOOL_  INT_  STRUCT_  WHILE_  READ_  PRINT_  IF_  ELSE_
%token TRUE_  FALSE_  ALLAVE_  CLLAVE_  ACORCH_  CCORCH_  NOT_
%token GEQ_  LEQ_  GREATER_  LESSTHAN_  EQ_  NEQ_  ASIG_  RETURN_
%token AND_  OR_  PUNTCOMA_  COMA_  PUNT_  INCR_  DECRE_
%token MAS_  MENOS_  POR_  DIV_  APAR_  CPAR_  CTE_  ID_

%%

programa        : listDecla
                ;

listDecla       : decla
                | listDecla decla
                ;

decla           : declaVar 
                | declaFunc
                ;

declaVar        : tipoSimp ID_ PUNTCOMA_
                | tipoSimp ID_ ACORCH_ CTE_ CCORCH_ PUNTCOMA_
                | STRUCT_ ALLAVE_ listCamp CLLAVE_ ID_ PUNTCOMA_
                ;

tipoSimp        : INT_ 
                | BOOL_
                ;

listCamp        : tipoSimp ID_ PUNTCOMA_
                | listCamp tipoSimp ID_ PUNTCOMA_
                ;

declaFunc       : tipoSimp ID_ APAR_ paramForm CPAR_ ALLAVE_ declaVarLocal listInst RETURN_ expre PUNTCOMA_ CLLAVE_
                ;
paramForm       : /* cadena vacia */
                | listParamForm
                ;

listParamForm   : tipoSimp ID_ 
                | tipoSimp ID_ COMA_ listParamForm
                ;

declaVarLocal   : /* cadena vacia */
                | declaVarLocal declaVar
                ;

listInst        : /* cadena vacia */
                | listInst inst
                ;

inst            : ALLAVE_ listInst CLLAVE_
                | instExpre
                | instEntSal
                | instSelec
                | instIter
                ;

instExpre       : expre PUNTCOMA_
                | PUNTCOMA_
                ;
              
instEntSal      : READ_ APAR_ ID_ CPAR_ PUNTCOMA_
                | PRINT_ APAR_ expre CPAR_ PUNTCOMA_
                ;

instSelec       : IF_ APAR_ expre CPAR_ inst ELSE_ inst
                ;

instIter        : WHILE_ APAR_ expre CPAR_ inst
                ;

expre           : expreLogic
                | ID_ ASIG_ expre
                | ID_ ACORCH_ expre CCORCH_ ASIG_ expre
                | ID_ PUNT_ ID_ ASIG_ expre
                ;

expreLogic      : expreIgual
                | expreLogic opLogic expreIgual
                ;

expreIgual      : expreRel
                | expreIgual opIgual expreRel
                ;

expreRel        : expreAd
                | expreRel opRel expreAd
                ;

expreAd         : expreMul
                | expreAd opAd expreMul
                ;

expreMul        : expreUna
                | expreMul opMul expreUna
                ;

expreUna        : expreSufi
                | opUna expreUna
                | opIncre ID_
                ;

expreSufi       : const
                | APAR_ expre CPAR_
                | ID_
                | ID_ opIncre
                | ID_ PUNT_ ID_
                | ID_ ACORCH_ expre CCORCH_
                | ID_ APAR_ paramAct CPAR_
                ;        

const           : CTE_ 
                | TRUE_ 
                | FALSE_
                ;

paramAct        : /* cadena vacia */
                | listParamAct
                ;

listParamAct    : expre
                | expre COMA_ listParamAct
                ;

opLogic         : AND_
                | OR_
                ;

opIgual         : EQ_
                | NEQ_
                ;

opRel           : GREATER_
                | LESSTHAN_
                | GEQ_
                | LEQ_
                ;

opAd            : MAS_
                | MENOS_
                ;

opMul           : POR_
                | DIV_
                ;

opUna           : MAS_
                | MENOS_
                | NOT_
                ;

opIncre         : INCR_
                | DECRE_
                ;
                
%%
