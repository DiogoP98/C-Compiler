// Tokens
%token
  INT
  FLOAT
  PLUS
  SUB
  MUL
  DIV
  OR
  AND
  NOT
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
%left INT FLOAT
%left AND OR

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  CommandList* commandlist;
  Expr* exprValue;
  ExprList* exprList; 
  BoolExpr* boolExpr;
}

%type <intValue> INT
%type <commandlist> list
%type <exprValue> expr
%type <boolExpr> bexpr

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
CommandList* list;
}

%%
program: 'int main() {' list '}' {root = $1;};

list:
  {
    $$ = NULL;
  }
  |
  cmd list{

  };
cmd:
  if_expr {

  }
  |
  while_expr {

  }
  |
  decl ';' {

  }
  ;

expr_list:
    { 
      $$ = NULL; 
    }
    |
    expr expr_list {
      $$ = ast_exprlist($1, $2);
    }
    |
    bexpr expr_list {
      $$ = ast_exprlist2($1, $2);
    };

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
  };
  
bexpr:
  bexpr OR bexpr {
    $$ = ast_boolOperation(OR, $1, $3);
  }
  |
  bexpr AND bexpr {
    $$ = ast_boolOperation(AND, $1, $3);
  }
  |
  NOT bexpr {
    $$ = ast_boolNot(NOT,$2);
  }
  |
  expr {
    $$ = ast_singleExpr($1);
  }
  |
  expr DIF expr {
    $$ = ast_boolOperation2(DIF, $1, $3);
  }
  |
  expr LES expr {
    $$ = ast_boolOperation2(LES, $1, $3);
  }
  |
  expr LOQ expr {
    $$ = ast_boolOperation2(LOQ, $1, $3);
  }
  |
  expr GRE expr {
    $$ = ast_boolOperation2(GRE, $1, $3);
  }
  |
  expr GOQ expr {
    $$ = ast_boolOperation2(GOQ, $1, $3);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

