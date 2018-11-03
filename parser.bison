// Tokens
%token
  MAIN
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
  ELSE
  WHILE
  INTD
  FLOATD
  SCAN
  PRINT
  VAR
  SEMICOLON
  EQUAL
  OPENPARENTHESIS
  CLOSEPARENTHESIS
  OPENCURLYBRACKETS
  CLOSECURLYBRACKETS
  OPENSQUAREBRACKETS
  CLOSESQUAREBRACKETS
  COMMA
  TYPES

// Operator associativity & precedence
%left EQU DIF LES LOQ GRE GOQ
%left PLUS SUB
%left MUL DIV MOD
%left INT FLOAT
%left AND OR
%left VAR
%left IF WHILE
%left ELSE
%left SCAN PRINT


// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
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
}

%type <intValue> INT
%type <floatValue> FLOAT
%type <stringValue> VAR
%type <typesValue> TYPES
%type <cmdType> cmd
%type <commandList> list
%type <exprValue> expr
%type <boolExpr> bexpr
%type <ifExpression> if_expr
%type <whileExpression> while_expr
%type <list_decl> list_var
%type <scan_list> list_scan_var
%type <assignment> atr
%type <declaration> decl
%type <printf_exp> printf
%type <scan_expr> scanf

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
program: INTD MAIN OPENPARENTHESIS CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS { root = $6; }

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
  printf SEMICOLON{
    $$ = printf_declaration($1);
  }
  |
  scanf SEMICOLON{
    $$ = scanf_declaration($1);
  }
  |
  list_var SEMICOLON {
    $$ = assignment_declaration($1);
  }
  ;


printf:
  PRINT OPENPARENTHESIS TYPES COMMA list_var CLOSEPARENTHESIS{
    $$ = ast_printf($3,$5);
  }
  ;

scanf:
  SCAN OPENPARENTHESIS TYPES COMMA list_scan_var CLOSEPARENTHESIS {
    $$ = ast_scanf($3,$5);
  };

if_expr:
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS list {
    $$ = if_command($3, $5);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS list ELSE list {
    $$ = if_else_command($3, $5, $7);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = if_command($3,$6);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS ELSE list {
    $$ = if_else_command($3, $6, $9);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS ELSE OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = if_else_command($3, $6, $10);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS list ELSE OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = if_else_command($3, $5, $8);
  }
  ;

while_expr: 
  WHILE OPENPARENTHESIS bexpr CLOSEPARENTHESIS list{
    $$ = while_command($3, $5);
  }
  |
  WHILE OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = while_command($3, $6);
  } 
  ;

atr:
  VAR EQUAL expr {
    $$ = var_assignment($1,$3);
  }
  |
  VAR OPENSQUAREBRACKETS INT CLOSESQUAREBRACKETS EQUAL expr {
    $$ = array_assignment($1,$3,$6);
  }
  ;

decl:
    VAR {
      $$ = var_declaration($1);
    }
    |
    VAR OPENSQUAREBRACKETS INT CLOSESQUAREBRACKETS {
      $$ = array_declaration($1,$3);
    }
  ;

list_scan_var:
  '&'decl COMMA list_scan_var {
    $$ = ast_scanlist($2,$4);
  }
  |
  '&'decl {
    $$ = ast_scanlist($2,NULL);
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
  OPENPARENTHESIS expr CLOSEPARENTHESIS {
    $$ = ast_singleExpr($2);
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

