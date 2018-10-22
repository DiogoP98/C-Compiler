// Tokens
%token
  INT
  BOOL
  PLUS
  SUB
  MUL
  DIV
  EQU
  DIF
  LES
  LOQ
  GRE
  GOQ

// Operator associativity & precedence
%left EQU DIF LES LOQ GRE GOQ
%left PLUS SUB
%left MUL DIV MOD
%left INT BOOL

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  ExprList* exprList; 
  BoolExpr* boolExpr;
}

%type <intValue> INT
%type <exprValue> expr
%type <exprList> expr_list
%type <boolExpr> bool_expr

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
ExprList* root;
}

%%
program: expr_list {root = $1;}

expr_list:
    { 
      $$ = NULL; 
    }
    |
    expr expr_list {
      $$ = ast_exprlist($1, $2);
    }
    |
    bool_expr expr_list {
	  $$ = ast_boolExprlist($1,$2);
    }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  }
  |
  expr SUB expr {
    $$ = ast_operation(SUB, $1, $3);
  }
  |
  expr MUL expr {
    $$ = ast_operation(MUL, $1, $3);
  } 
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr MOD expr {
    $$ = ast_operation(MOD, $1, $3);
  }
  
bool_expr:
  expr {
    $$ = ast_bool($1);
  }
  |
  expr EQU expr {
    $$ = ast_boolOperation(EQU, $1, $3);
  }
  |
  expr DIF expr {
    $$ = ast_boolOperation(DIF, $1, $3);
  }
  |
  expr LES expr {
    $$ = ast_boolOperation(LES, $1, $3);
  }
  |
  expr LOQ expr {
    $$ = ast_boolOperation(LOQ, $1, $3);
  }
  |
  expr GRE expr {
    $$ = ast_boolOperation(GRE, $1, $3);
  }
  |
  expr GOQ expr {
    $$ = ast_boolOperation(GOQ, $1, $3);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

