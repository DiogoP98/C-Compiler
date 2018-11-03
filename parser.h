/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 92 "parser.bison" /* yacc.c:1919  */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
CommandList* root;

#line 57 "parser.h" /* yacc.c:1919  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    INT = 259,
    FLOAT = 260,
    PLUS = 261,
    SUB = 262,
    MUL = 263,
    DIV = 264,
    OR = 265,
    AND = 266,
    NOT = 267,
    EQU = 268,
    DIF = 269,
    LES = 270,
    LOQ = 271,
    GRE = 272,
    GOQ = 273,
    IF = 274,
    ELSE = 275,
    WHILE = 276,
    INTD = 277,
    FLOATD = 278,
    SCAN = 279,
    PRINT = 280,
    VAR = 281,
    SEMICOLON = 282,
    EQUAL = 283,
    OPENPARENTHESIS = 284,
    CLOSEPARENTHESIS = 285,
    OPENCURLYBRACKETS = 286,
    CLOSECURLYBRACKETS = 287,
    OPENSQUAREBRACKETS = 288,
    CLOSESQUAREBRACKETS = 289,
    COMMA = 290,
    TYPES = 291,
    MOD = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 54 "parser.bison" /* yacc.c:1919  */

  int intValue;
  float floatValue;
  char* stringValue;
  char* typesValue;
  CommandList* commandList;
  Command* cmdType;
  IFexpression* ifExpression;
  WHILEexpression* whileExpression;
  PRINTF_EXP* printf_exp;
  SCANF_EXP* scan_expr;
  DeclarationList* list_decl;
  ScanDeclarationList* scan_list;
  ASG* assignment;
  DECL* declaration;
  Expr* exprValue;
  BoolExpr* boolExpr;

#line 126 "parser.h" /* yacc.c:1919  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
