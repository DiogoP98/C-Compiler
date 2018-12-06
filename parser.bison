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
  NOTOP
  IGU
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
  '&'
  TYPES

// Operator associativity & precedence
%left IGU DIF LES LOQ GRE GOQ
%left PLUS SUB
%left MUL DIV MOD
%left OPENPARENTHESIS CLOSEPARENTHESIS
%left INT FLOAT
%left AND OR NOTOP
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
  TYPES_STR* string_types;
  varList* varList;
  DeclarationList* list_decl;
  AsgList* asg_list;
  ScanDeclarationList* scan_list;
  Expr* exprValue;
  NUMBER* number;
}

%type <intValue> INT
%type <floatValue> FLOAT
%type <stringValue> VAR
%type <typesValue> TYPES
%type <cmdType> cmd
%type <commandList> list
%type <exprValue> expr
%type <ifExpression> if_expr
%type <whileExpression> while_expr
%type <list_decl> list_var
%type <scan_list> list_scan_var
%type <printf_exp> printf
%type <scan_expr> scanf
%type <varList> var_dec
%type <string_types> string
%type <number> num
%type <asg_list> list_asg

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symbol_table.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);

CommandList* root;
ItemsList* list;

int checkExistence(char* name, ItemsList* list);
}

%%
program: INTD MAIN OPENPARENTHESIS CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
  root = $6;
};

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
  var_dec{
    $$ = variable_declaration($1);
  }
  |
  list_asg SEMICOLON {
    $$ = assignment_declaration($1);
  }
  |
  printf {
    $$ = printf_declaration($1);
  }
  |
  scanf {
    $$ = scanf_declaration($1);
  }
  ;


printf:
  PRINT OPENPARENTHESIS string COMMA list_var CLOSEPARENTHESIS SEMICOLON{
    $$ = ast_printf($3,$5);
  }
  |
  PRINT OPENPARENTHESIS string CLOSEPARENTHESIS SEMICOLON{
    $$ = ast_printf($3, NULL);
  }
  ;

scanf:
  SCAN OPENPARENTHESIS string COMMA list_scan_var CLOSEPARENTHESIS SEMICOLON{
    $$ = ast_scanf($3,$5);
  }
  ;

string:
  TYPES {
    $$ = ast_string_of_types($1);
  }
  ;

if_expr:
  IF OPENPARENTHESIS expr CLOSEPARENTHESIS cmd %prec NO_ELSE {
    $$ = if_command($3, $5);
  }
  |
  IF OPENPARENTHESIS expr CLOSEPARENTHESIS cmd ELSE cmd {
    $$ = if_command_else_command($3, $5, $7);
  }
  |
  IF OPENPARENTHESIS expr CLOSEPARENTHESIS OPENCURLYBRACKETS list %prec NO_ELSE CLOSECURLYBRACKETS {
    $$ = if_commands($3,$6);
  }
  |
  IF OPENPARENTHESIS expr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS ELSE cmd {
    $$ = if_commands_else_command($3, $6, $9);
  }
  |
  IF OPENPARENTHESIS expr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS ELSE OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = if_commands_else_commands($3, $6, $10);
  }
  |
  IF OPENPARENTHESIS expr CLOSEPARENTHESIS cmd ELSE OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = if_command_else_commands($3, $5, $8);
  }
  ;

while_expr:
  WHILE OPENPARENTHESIS expr CLOSEPARENTHESIS cmd{
    $$ = while_command($3, $5);
  }
  |
  WHILE OPENPARENTHESIS expr CLOSEPARENTHESIS OPENCURLYBRACKETS list CLOSECURLYBRACKETS {
    $$ = while_commands($3, $6);
  } 
  ;

list_scan_var:
  '&' VAR COMMA list_scan_var {
    $$ = ast_scanlist($2,$4);
  }
  |
  '&' VAR {
    $$ = ast_scanlist($2,NULL);
  }
;

var_dec: 
  INTD list_var SEMICOLON{
    $$ = ast_varlist(INTD, $2);
  }
  |
  FLOATD list_var SEMICOLON{
    $$ = ast_varlist(FLOATD, $2);
  }
;

list_var:
  VAR {
    $$ = ast_declaration($1,NULL);
  }
  |
  VAR COMMA list_var {
    $$ = ast_declaration($1,$3);
  }
  |
  VAR EQUAL expr COMMA list_var{
    $$ = ast_assignment($1, $3, $5);
  }
  |
  VAR EQUAL expr {
    $$ = ast_assignment($1, $3, NULL);
  }
;

list_asg: 
  VAR EQUAL expr COMMA list_asg{
    $$ = ast_assignmentList($1, $3, $5);
  }
  |
  VAR EQUAL expr {
    $$ = ast_assignmentList($1,$3, NULL);
  }
;

expr: 
  num {
    $$ = ast_number($1);
  }
  |
  VAR {
    $$ = ast_variable($1);
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
  }
  |
  expr OR expr {
    $$ = ast_operation(OR, $1, $3);
  }
  |
  expr AND expr {
    $$ = ast_operation(AND, $1, $3);
  }
  |
  NOTOP expr {
    $$ = ast_operation(NOTOP,$2, NULL);
  }
  |
  expr IGU expr {
    $$ = ast_operation(IGU, $1, $3);
  }
  |
  expr DIF expr {
    $$ = ast_operation(DIF, $1, $3);
  }
  |
  expr LES expr {
    $$ = ast_operation(LES, $1, $3);
  }
  |
  expr LOQ expr {
    $$ = ast_operation(LOQ, $1, $3);
  }
  |
  expr GRE expr {
    $$ = ast_operation(GRE, $1, $3);
  }
  |
  expr GOQ expr {
    $$ = ast_operation(GOQ, $1, $3);
  };

num: 
  INT {
    $$ = ast_integer($1);
  }
  |
  PLUS INT {
    $$ = ast_integer($2);
  }
  |
  SUB INT {
    $$ = ast_integer(-$2);
  }
  |
  FLOAT {
    $$ = ast_float($1);
  }
  |
  PLUS FLOAT {
    $$ = ast_float($2);
  }
  |
  SUB FLOAT {
    $$ = ast_float(-$2);
  }
;
%%

int check_var(char* name, int type) {
  int vtype = checkExistence(name, list);

  if(vtype == -1) yyerror("Variable is not defined");
  else if(type != -1 && vtype != type) yyerror("Not the correct type");

  return vtype;
}

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

