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
  COMMA
  TYPES

// Operator associativity & precedence
%left EQU DIF LES LOQ GRE GOQ
%left PLUS SUB
%left MUL DIV MOD
%left INT FLOAT
%left AND OR NOT
%left VAR
%left IF WHILE
%nonassoc NO_ELSE
%nonassoc ELSE


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
  varList* varList;
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
%type <varList> var_dec

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
program: INTD MAIN OPENPARENTHESIS CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS { root = $6; };

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
  var_dec SEMICOLON {
    $$ = variable_declaration($1);
  }
  |
  printf SEMICOLON{
    $$ = printf_declaration($1);
  }
  |
  scanf SEMICOLON{
    $$ = scanf_declaration($1);
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
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS cmd %prec NO_ELSE {
    $$ = if_command($3, $5);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS cmd ELSE cmd {
    $$ = if_command_else_command($3, $5, $7);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list %prec NO_ELSE CLOSECURLYBRACKETS {
    $$ = if_commands($3,$6);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS ELSE cmd {
    $$ = if_commands_else_command($3, $6, $9);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS ELSE OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = if_commands_else_commands($3, $6, $10);
  }
  |
  IF OPENPARENTHESIS bexpr CLOSEPARENTHESIS cmd ELSE OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = if_command_else_commands($3, $5, $8);
  }
  ;

while_expr: 
  WHILE OPENPARENTHESIS bexpr CLOSEPARENTHESIS cmd{
    $$ = while_command($3, $5);
  }
  |
  WHILE OPENPARENTHESIS bexpr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = while_commands($3, $6);
  } 
  ;

atr:
  VAR EQUAL expr {
    $$ = var_assignment($1,$3);
  }
  ;

decl:
  VAR {
    $$ = var_declaration($1);
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

var_dec: 
  INTD list_var {
    $$ = ast_varlist(INTD, $2);
  }
  |
  FLOATD list_var {
    $$ = ast_varlist(FLOATD, $2);
  }
;

list_var:
  decl {
    $$ = ast_declaration($1, NULL);
  }
  |
  decl COMMA list_var {
    $$ = ast_declaration($1, $3);
  }
  |
  atr COMMA list_var{
    $$ = ast_assignment($1, $3);
  }
  |
  atr {
    $$ = ast_assignment($1, NULL);
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
  OPENPARENTHESIS expr CLOSEPARENTHESIS {
    $$ = ast_pexpr($2);
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
    $$ = ast_boolOperation(NOT,$2, NULL);
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

