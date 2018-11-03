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
  IF
  THEN
  ELSE
  WHILE
  INTD
  FLOATD
  SCAN
  PRINT
  VAR
  PRINTF_EXPR
  SCAN_EXPR
  STARTOFPROGRAM
  SEMICOLON
  EQUAL
  OPENPARENTHESIS
  CLOSEPARENTHESIS
  OPENCURLYBRACKETS
  CLOSECURLYBRACKETS
  OPENSQUAREBRACKETS
  CLOSESQUAREBRACKETS
  COMMA
  SPACE

// Operator associativity & precedence
%left EQU DIF LES LOQ GRE GOQ
%left PLUS SUB
%left MUL DIV MOD
%left INT FLOAT
%left AND OR
%left VAR
%left IF THEN ELSE WHILE
%left SCAN PRINT


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  float floatValue;
  char* stringValue;
  CommandList* commandList;
  Command* cmdType;
  IFexpression* ifExpression;
  WHILEexpression* whileExpression;
  DeclarationList* list_decl;
  ASG* assignment;
  DECL* declaration;
  Expr* exprValue;
  BoolExpr* boolExpr;
}

%type <intValue> INT
%type <floatValue> FLOAT
%type <stringValue> VAR
%type <cmdType> cmd
%type <commandList> list
%type <exprValue> expr
%type <boolExpr> bexpr
%type <ifExpression> if_expr
%type <whileExpression> while_expr
%type <list_decl> list_var
%type <assignment> atr
%type <declaration> decl

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
CommandList* root;
}

%%
program: STARTOFPROGRAM list CLOSECURLYBRACKETS { root = $2; }

list:
  cmd list{
    $$ = ast_commandList($1, $2);
  }
  |
  cmd {
    $$ = ast_commandList($1, NULL);
  }
  ;

cmd:
  if_expr {
    $$ = if_declaration($1);
  }
  |
  while_expr {
    $$ = while_declaration($1);
  }
  |
  INTD list_var SEMICOLON {
    $$ = declaration_declaration($2);
  }
  |
  FLOATD list_var SEMICOLON {
    $$ = declaration_declaration($2);
  }
  |
  PRINT OPENPARENTHESIS PRINTF_EXPR COMMA list_var CLOSEPARENTHESIS SEMICOLON {

  }
  |
  SCAN OPENPARENTHESIS SCAN_EXPR CLOSEPARENTHESIS SEMICOLON {
  
  }
  |
  list_var SEMICOLON {
    $$ = assignment_declaration($1);
  }
  ;

if_expr:
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS list {
    $$ = if_command($3, $5);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS list ELSE list {
    $$ = if_else_command($3, $5, $7);
  }
  |
  IF OPENPARENTHESIS bexpr ") {" list CLOSECURLYBRACKETS {
    $$ = if_command($3,$5);
  }
  |
  IF OPENPARENTHESIS bexpr ") {" list CLOSECURLYBRACKETS ELSE list {
    $$ = if_else_command($3, $5, $5);
  }
  |
  IF OPENPARENTHESIS bexpr ") {" list CLOSECURLYBRACKETS ELSE '{' list CLOSECURLYBRACKETS {
    $$ = if_else_command($3, $5, $9);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS list ELSE '{' list CLOSECURLYBRACKETS {
    $$ = if_else_command($3, $5, $8);
  }
  ;

while_expr: 
  WHILE OPENPARENTHESIS bexpr CLOSEPARENTHESIS list{
    $$ = while_command($3, $5);
  }
  |
  WHILE OPENPARENTHESIS bexpr ") {" list CLOSECURLYBRACKETS {
    $$ = while_command($3, $5);
  } 
  ;

atr:
  VAR EQUAL expr {
    $$ = var_assignment($1,$3);
  }
  |
  VAR OPENSQUAREBRACKETS INT CLOSECURLYBRACKETS EQUAL expr {
    $$ = array_assignment($1,$3,$6);
  }
  ;

decl:
    VAR {
      $$ = var_declaration($1);
    }
    |
    VAR OPENSQUAREBRACKETS INT CLOSECURLYBRACKETS {
      $$ = array_declaration($1,$3);
    }
  ;

list_var:
  decl {
    $$ = declaration($1,NULL);
  }
  |
  decl COMMA list_var{
    $$ = declaration($1,$3);
  }
  |
  atr {
    $$ = assignment($1, NULL);
  }
  |
  atr COMMA list_var{
    $$ = assignment($1, $3);
  }
  ;

expr: 
  INT {
    $$ = ast_integer($1);
  }
  |
  FLOAT {
    $$ = ast_float($1);
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
  expr EQU expr {
    $$ = ast_boolOperation2(EQU, $1, $3);
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

