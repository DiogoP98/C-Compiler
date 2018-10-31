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
  Command* cmdValue;
  CommandList* commandlist;
  Expr* exprValue;
  ExprList* exprList;
  BoolExpr* boolExpr;
}

%type <intValue> INT
%type <floatValue> FLOAT
%type <numValue> num
%type <cmdValue> cmd
%type <commandList> list
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
program: "int main() {" list '}' { root = $1; }

list:
  {
    $$ = NULL;
  }
  |
  cmd list{
    $$ = commandlist($1, $2);
  }
  |
  cmd {
    $$ = commandlist($1, NULL);
  }
  ;

cmd:
  if_expr {
    $$ = if_command($1)
  }
  |
  while_expr {

  }
  |
  decl ';' {

  }
  |
  PRINT '(' print_expr ')' ';' {

  }
  |
  SCAN '(' scan_expr ')' ';' {
  }
  |
  atr ';' {

  }
  ;

if_expr:
  IF '(' bexpr ')' cmd {

  }
  |
  IF '(' bexpr ')' cmd ELSE cmd {

  }
  |
  IF '(' bexpr ") {" cmd '}' {

  }
  IF '(' bexpr ") {" cmd '}' ELSE cmd {

  }
  |
  IF '(' bexpr ") {" cmd '}' ELSE '{' cmd '}' {

  }
  |
  IF '(' bexpr ')' cmd ELSE '{' cmd '}' {

  }
  ;

while_expr: 
  WHILE'(' bexpr ')' {

  }
  |
  WHILE '(' bexpr ") {" '}' {

  } 
  ;

decl: 
 INTD list_var{

 }
 |
 FLOAT list_var{

 }
 ;

list_var:
  VAR {

  }
  |
  VAR ',' list_var{

  }
  |
  VAR '=' expr ',' list_var{

  }
  |
  VAR'[' num ']' ',' list_var{

  }
  ;

print_expr:
  {
  }
  ;

scan_expr: 
  {}
  ;

expr: 
  num {
    $$ = ast_number($1);
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

num:
  INT {
    $$ = ast_integer($1);
  }
  |
  FLOAT {
    $$ = ast_float($1);
  }
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

