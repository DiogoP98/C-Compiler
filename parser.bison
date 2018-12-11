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
%left AND OR NOTOP
%left IGU DIF LES LOQ GRE GOQ
%left PLUS SUB
%left MUL DIV MOD
%left OPENPARENTHESIS CLOSEPARENTHESIS
%left INT FLOAT
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
  PrintVarsList* printList;
  SCANF_EXP* scan_expr;
  TYPES_STR* string_types;
  varList* varList;
  DeclarationList* list_decl;
  AsgList* asg_list;
  ScanDeclarationList* scan_list;
  Expr* exprValue;
}

%type <intValue> INT
%type <floatValue> FLOAT
%type <stringValue> VAR
%type <typesValue> TYPES
%type <cmdType> cmd
%type <commandList> list
%type <exprValue> expr
%type <exprValue> num
%type <ifExpression> if_expr
%type <whileExpression> while_expr
%type <list_decl> list_var_int
%type <list_decl> list_var_float
%type <scan_list> list_scan_var
%type <printf_exp> printf
%type <printList> list_print
%type <scan_expr> scanf
%type <varList> var_dec
%type <string_types> string
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
ItemsList* SYMBOL_LIST;

int checkExistence(char* name, ItemsList* list);
ItemsList* createItem(ItemsList* list, char* name, int type);

void validate_expression_types(Expr* expr1, Expr* expr2);
void validate_var(char* name, Expr* expr);
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
  PRINT OPENPARENTHESIS string COMMA list_print CLOSEPARENTHESIS SEMICOLON{
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
    if(checkExistence(strdup($2), SYMBOL_LIST) == -1) yyerror("Variable not declared!");

    $$ = ast_scanlist($2,$4);
  }
  |
  '&' VAR {
    if(checkExistence(strdup($2), SYMBOL_LIST) == -1) yyerror("Variable not declared!");

    $$ = ast_scanlist($2, NULL);
  }
;

var_dec: 
  INTD list_var_int SEMICOLON{
    $$ = ast_varlist(INTD, $2);
  }
  |
  FLOATD list_var_float SEMICOLON{
    $$ = ast_varlist(FLOATD, $2);
  }
;

list_var_int:
  VAR {
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");
    
    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 1);
    $$ = ast_declaration($1,NULL);
  }
  |
  VAR COMMA list_var_int {
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");
    
    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 1);
    $$ = ast_declaration($1,$3);
  }
  |
  VAR EQUAL expr COMMA list_var_int{
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");

    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 1);

    if($3->type != 1) yyerror("Expression with wrong type!");

    $$ = ast_assignment($1, $3, $5);
  }
  |
  VAR EQUAL expr {
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");
    
    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 1);

    if($3->type != 1) yyerror("Expression with wrong type!");

    $$ = ast_assignment($1, $3, NULL);
  }
;

list_var_float:
  VAR {
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");
    
    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 0);
    $$ = ast_declaration($1,NULL);
  }
  |
  VAR COMMA list_var_float {
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");
    
    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 0);
    $$ = ast_declaration($1, $3);
  }
  |
  VAR EQUAL expr COMMA list_var_float{
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");
    
    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 0);

    if($3->type != 0) yyerror("Expression with wrong type!");

    $$ = ast_assignment($1, $3, $5);
  }
  |
  VAR EQUAL expr {
    if(checkExistence($1, SYMBOL_LIST) != -1) yyerror("Variable already declared!");
    
    SYMBOL_LIST = createItem(SYMBOL_LIST, $1, 0);

    if($3->type != 0) yyerror("Expression with wrong type!");

    $$ = ast_assignment($1, $3, NULL);
  }
;

list_asg: 
  VAR EQUAL expr COMMA list_asg{
    validate_var($1,$3);
    $$ = ast_assignmentList($1, $3, $5);
  }
  |
  VAR EQUAL expr {
    validate_var($1,$3);
    $$ = ast_assignmentList($1,$3, NULL);
  }
;

list_print:
  VAR COMMA list_print {
    if(checkExistence($1, SYMBOL_LIST) == -1) yyerror("Variable not declared!");

    $$ = ast_printlist($1, $3);
  }
  |
  VAR {
    if(checkExistence($1, SYMBOL_LIST) == -1) yyerror("Variable not declared!");

    $$ = ast_printlist($1, NULL);
  }
;

expr: 
  num {
    $$ = $1;
  }
  |
  OPENPARENTHESIS expr CLOSEPARENTHESIS {
    $$ = $2;
  }
  |
  expr PLUS expr { 
    validate_expression_types($1,$3);
    $$ = ast_operation(PLUS, $1, $3);
  }
  |
  expr SUB expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(SUB, $1, $3);
  }
  |
  expr MUL expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(MUL, $1, $3);
  } 
  |
  expr DIV expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr MOD expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(MOD, $1, $3);
  }
  |
  expr OR expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(OR, $1, $3);
  }
  |
  expr AND expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(AND, $1, $3);
  }
  |
  NOTOP expr {
    $$ = ast_operation(NOTOP,$2, NULL);
  }
  |
  expr IGU expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(IGU, $1, $3);
  }
  |
  expr DIF expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(DIF, $1, $3);
  }
  |
  expr LES expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(LES, $1, $3);
  }
  |
  expr LOQ expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(LOQ, $1, $3);
  }
  |
  expr GRE expr {
    validate_expression_types($1,$3);
    $$ = ast_operation(GRE, $1, $3);
  }
  |
  expr GOQ expr {
    validate_expression_types($1,$3);
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
  |
  VAR {
    int type = checkExistence($1, SYMBOL_LIST);

    if(type == -1) yyerror("Variable not declared!");
    else if(type == 0) $$ = ast_variable_float($1);
    else $$ = ast_variable_int($1);

  }
;
%%

void yyerror(const char* err) {
  fprintf(stderr, "Line %d: error: %s\n", yyline, err);
  exit(1);
}

void validate_expression_types(Expr* expr1, Expr* expr2) {
  int type1 = expr1->type;
  int type2 = expr2->type;

  if(type1 != type2) yyerror("Operation between expression with different types!");
}

void validate_var(char* name, Expr* expr) {
  int type = checkExistence(name, SYMBOL_LIST);

  if (type == -1) yyerror("Variable not declared!");
  else if(type != -1 && type != expr->type) yyerror("Expression with wrong type!");
}
