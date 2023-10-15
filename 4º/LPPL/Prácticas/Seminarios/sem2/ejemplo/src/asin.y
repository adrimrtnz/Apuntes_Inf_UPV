/*****************************************************************************/
/** Ejemplo  S E M - 2                    2023-2024 <jmbenedi@prhlt.upv.es> **/
/*****************************************************************************/
%{
#include <stdio.h>
#include <string.h>
#include "header.h"
%}

%token  APAR_  CPAR_  MAS_  MENOS_  POR_  DIV_
%token  CTE_

%%

expMat : exp
       ;
exp    : exp  MAS_    term
       | exp  MENOS_  term
       | term         
       ;
term   : term  POR_  fac
       | term  DIV_  fac   
       | fac             
       ;
fac    : APAR_  exp  CPAR_ 
       | CTE_            
       ;


programa        : listDecla
                ;

listDecla       : decla
                | listDecla decla
                ;

decla           : declaVar 
                | declaFunc
                ;

declaVar        : tipoSimp ID_ 
                | tipoSimp ID_ [CTE_] 
                | struct { listCamp } ID_ 
                ;

tipoSimp        : int 
                | bool
                ;

listCamp        : tipoSimp ID_ 
                | listCamp tipoSimp ID_
                ;

declaFunc       : tipoSimp ID_ APAR_ paramForm CPAR_ { declaVarLocal listInst return expre ; }
                ;
paramForm       : /* cadena vacia */
                | listParamForm
                ;

listParamForm   : tipoSimp ID_ 
                | tipoSimp ID_ , listParamForm
                ;

declaVarLocal   : /* cadena vacia */
                | declaVarLocal declaVar
                ;  

cons            : CTE_ 
                | TRUE 
                | FALSE
                ;

%%
