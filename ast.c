// AST constructor functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc
#include "ast.h" // AST header

//------- Command list -----------------
CommandList* ast_commandList(Command* cmd, CommandList* next) {
  CommandList* node = (CommandList*) malloc(sizeof(CommandList));
  node->expr = cmd;
  node->next = next;
  return node;
}


//------- Command functions -------------
Command* if_declaration(IFexpression* ifnext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_IF; 
  node->ifnext = ifnext;
  return node;
}

Command* while_declaration(WHILEexpression* whilenext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_WHILE;
  node->whilenext = whilenext;
  return node; 
}

Command* printf_declaration(PRINTF_EXP* printnext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_PRINT;
  node->printnext = printnext;
  return node; 
}

Command* scanf_declaration(SCANF_EXP* scannext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_SCAN;
  node->scannext = scannext;
  return node; 
}

Command* variable_declaration(varList* list) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_VAR; 
  node->list = list;
  return node;
}

//------- IF expressions ----------------

IFexpression* if_command(BoolExpr* bexpr, Command* cmd) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  list->expr = cmd;
  list->next = NULL;
  node->kind = E_IF_EXPR;
  node->if_type.list = list;
  node->if_type.bexpr = bexpr;
  return node;
}

IFexpression* if_command_else_command(BoolExpr* bexpr, Command* cmd, Command* else_cmd) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  CommandList* list2 = (CommandList*) malloc(sizeof(CommandList));
  list->expr = cmd;
  list->next = NULL;
  list2->expr = else_cmd;
  list2->next = NULL;
  node->kind = E_IF_ELSE;
  node->if_else_type.bexpr = bexpr;
  node->if_else_type.list = list;
  node->if_else_type.else_list = list2;
  return node;
}

IFexpression* if_commands(BoolExpr* bexpr, CommandList* list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF_EXPR;
  node->if_type.list = list;
  node->if_type.bexpr = bexpr;
  return node;
}

IFexpression* if_commands_else_command(BoolExpr* bexpr, CommandList* list, Command* else_cmd) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list2 = (CommandList*) malloc(sizeof(CommandList));
  list2->expr = else_cmd;
  list2->next = NULL;
  node->kind = E_IF_ELSE;
  node->if_else_type.bexpr = bexpr;
  node->if_else_type.list = list;
  node->if_else_type.else_list = list2;
  return node;
}

IFexpression* if_commands_else_commands(BoolExpr* bexpr, CommandList* list, CommandList* else_list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF_ELSE;
  node->if_else_type.bexpr = bexpr;
  node->if_else_type.list = list;
  node->if_else_type.else_list = else_list;
  return node;
}

IFexpression* if_command_else_commands(BoolExpr* bexpr, Command* cmd, CommandList* else_list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  list->expr = cmd;
  list->next = NULL;
  node->kind = E_IF_ELSE;
  node->if_else_type.bexpr = bexpr;
  node->if_else_type.list = list;
  node->if_else_type.else_list = else_list;
  return node;
}

//------- WHILE expressions ----------------
WHILEexpression* while_command(BoolExpr* bexpr, Command* cmd) {
  WHILEexpression* node = (WHILEexpression*) malloc(sizeof(WHILEexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  list->expr = cmd;
  list->next = NULL;
  node->bexpr = bexpr;
  node->list = list;
  return node;
}

WHILEexpression* while_commands(BoolExpr* bexpr, CommandList* list) {
  WHILEexpression* node = (WHILEexpression*) malloc(sizeof(WHILEexpression));
  node->bexpr = bexpr;
  node->list = list;
  return node;
}

//------- INPUT/OUTPUT expressions ----------------

TYPES_STR* ast_string_of_types(char* type) {
  TYPES_STR* node = (TYPES_STR*) malloc(sizeof(TYPES_STR));
  node->types = strdup(type);
  return node;
}

PRINTF_EXP* ast_printf(TYPES_STR* types, DeclarationList* vars) {
  PRINTF_EXP* node = (PRINTF_EXP*) malloc(sizeof(PRINTF_EXP));
  node->string_of_types = types;
  node->vars = vars;
  return node;
}

SCANF_EXP* ast_scanf(TYPES_STR* types, ScanDeclarationList* vars) {
  SCANF_EXP* node = (SCANF_EXP*) malloc(sizeof(SCANF_EXP));
  node->string_of_types = types;
  node->vars = vars;
  return node;
}

ScanDeclarationList* ast_scanlist(DECL* var, ScanDeclarationList* next) {
  ScanDeclarationList* node = (ScanDeclarationList*) malloc(sizeof(ScanDeclarationList));
  node->declaration = var;
  node->next = next;
  return node;
}

//--------- Declaration List -------------
varList* ast_varlist(int type, DeclarationList* next) {
  varList* node = (varList*) malloc(sizeof(varList));
  node->type = type;
  node->list = next;
  return node;
}


DeclarationList* ast_declaration(DECL* decl, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->type = E_DECLARATION;
  node->declaration = decl;
  node->next = next;
  return node;
}

DeclarationList* ast_assignment(ASG* asg, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->type = E_ASSIGNMENT;
  node->assignment = asg;
  node->next = next;
  return node;
}

DECL* var_declaration(char* s) {
  DECL* node = (DECL*) malloc(sizeof(DECL));
  node->name = strdup(s);
  return node;
}

ASG* var_assignment(DECL* s, Expr* expr) {
  ASG* node = (ASG*) malloc(sizeof(ASG));
  node->name = s;
  node->value = expr;
  return node;
}

//------- Expressions functions -------------
NUMBER* ast_integer(int v) {
  NUMBER* node = (NUMBER*) malloc(sizeof(NUMBER));
  node->valuei = v;
  node->type = E_INTEGER;
  return node;
}

NUMBER* ast_float(float v) {
  NUMBER* node = (NUMBER*) malloc(sizeof(NUMBER));
  node->valuef = v;
  node->type = E_FLOAT;
  return node;
}

Expr* ast_number(NUMBER* m) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->attr.number = m;
  node->kind = E_NUM;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->parenthesis = E_HASNOT;
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr* ast_pexpr(Expr* expr) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node = expr;
  node->parenthesis = E_HAS;
  return node;
}

//------- Bool Expressions functions -------------
BoolExpr* ast_bool(int v) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOL;
  node->attr_bool.value = (v==0)? 0:1;
  return node;
}

BoolExpr* ast_boolOperation(int operator, BoolExpr* bleft, BoolExpr* bright) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_RELOP;
  node->attr_bool.relop.operator = operator;
  node->attr_bool.relop.bleft = bleft;
  node->attr_bool.relop.bright = bright;
  return node;
}

BoolExpr* ast_boolOperation2(int operator, Expr* left, Expr* right) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_RELOP;
  node->attr_bool.relop.operator = operator;
  node->attr_bool.relop.left = left;
  node->attr_bool.relop.right = right;
  return node;
}

BoolExpr* ast_singleExpr(Expr* expr) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->attr_bool.relop.left = expr;
  return node;
}


