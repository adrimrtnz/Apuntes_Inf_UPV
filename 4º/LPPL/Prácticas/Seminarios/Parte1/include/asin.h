/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ASIN_H_INCLUDED
# define YY_YY_ASIN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BOOL_ = 258,                   /* BOOL_  */
    INT_ = 259,                    /* INT_  */
    STRUCT_ = 260,                 /* STRUCT_  */
    WHILE_ = 261,                  /* WHILE_  */
    READ_ = 262,                   /* READ_  */
    PRINT_ = 263,                  /* PRINT_  */
    IF_ = 264,                     /* IF_  */
    ELSE_ = 265,                   /* ELSE_  */
    TRUE_ = 266,                   /* TRUE_  */
    FALSE_ = 267,                  /* FALSE_  */
    ALLAVE_ = 268,                 /* ALLAVE_  */
    CLLAVE_ = 269,                 /* CLLAVE_  */
    ACORCH_ = 270,                 /* ACORCH_  */
    CCORCH_ = 271,                 /* CCORCH_  */
    NOT_ = 272,                    /* NOT_  */
    GEQ_ = 273,                    /* GEQ_  */
    LEQ_ = 274,                    /* LEQ_  */
    GREATER_ = 275,                /* GREATER_  */
    LESSTHAN_ = 276,               /* LESSTHAN_  */
    EQ_ = 277,                     /* EQ_  */
    NEQ_ = 278,                    /* NEQ_  */
    ASIG_ = 279,                   /* ASIG_  */
    RETURN_ = 280,                 /* RETURN_  */
    AND_ = 281,                    /* AND_  */
    OR_ = 282,                     /* OR_  */
    PUNTCOMA_ = 283,               /* PUNTCOMA_  */
    COMA_ = 284,                   /* COMA_  */
    PUNT_ = 285,                   /* PUNT_  */
    INCR_ = 286,                   /* INCR_  */
    DECRE_ = 287,                  /* DECRE_  */
    MAS_ = 288,                    /* MAS_  */
    MENOS_ = 289,                  /* MENOS_  */
    POR_ = 290,                    /* POR_  */
    DIV_ = 291,                    /* DIV_  */
    APAR_ = 292,                   /* APAR_  */
    CPAR_ = 293,                   /* CPAR_  */
    CTE_ = 294,                    /* CTE_  */
    ID_ = 295                      /* ID_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ASIN_H_INCLUDED  */
