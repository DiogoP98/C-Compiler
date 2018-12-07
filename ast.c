// AST constructor functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc
#include "ast.h" // AST header

//------- Command list -----------------
CommandList* ast_commandList(Command* cmd, CommandList* next) {
  CommandList* node = (CommandList*) malloc(sizeof(CommandList));
  node->cmd = cmd;
  node->next = next;
  return node;
}


//------- Command functions -------------
Command* if_declaration(IFexpression* ifnext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_IF; 
  node->content.ifnext = ifnext;
  return node;
}

Command* while_declaration(WHILEexpression* whilenext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_WHILE;
  node->content.whilenext = whilenext;
  return node; 
}

Command* printf_declaration(PRINTF_EXP* printnext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_PRINT;
  node->content.printnext = printnext;
  return node; 
}

Command* scanf_declaration(SCANF_EXP* scannext) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_SCAN;
  node->content.scannext = scannext;
  return node; 
}

Command* variable_declaration(varList* list) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_VAR; 
  node->content.list = list;
  return node;
}

Command* assignment_declaration(AsgList* asg_list) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_ASG; 
  node->content.asg_list = asg_list;
  return node;
}

//------- IF expressions ----------------

IFexpression* if_command(Expr* expr, Command* cmd) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  list->cmd = cmd;
  list->next = NULL;
  node->kind = E_IF_EXPR;
  node->content.if_type.list = list;
  node->content.if_type.expr = expr;
  return node;
}

IFexpression* if_command_else_command(Expr* expr, Command* cmd, Command* else_cmd) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  CommandList* list2 = (CommandList*) malloc(sizeof(CommandList));
  list->cmd = cmd;
  list->next = NULL;
  list2->cmd = else_cmd;
  list2->next = NULL;
  node->kind = E_IF_ELSE;
  node->content.if_else_type.expr = expr;
  node->content.if_else_type.list = list;
  node->content.if_else_type.else_list = list2;
  return node;
}

IFexpression* if_commands(Expr* expr, CommandList* list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF_EXPR;
  node->content.if_type.list = list;
  node->content.if_type.expr = expr;
  return node;
}

IFexpression* if_commands_else_command(Expr* expr, CommandList* list, Command* else_cmd) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list2 = (CommandList*) malloc(sizeof(CommandList));
  list2->cmd = else_cmd;
  list2->next = NULL;
  node->kind = E_IF_ELSE;
  node->content.if_else_type.expr = expr;
  node->content.if_else_type.list = list;
  node->content.if_else_type.else_list = list2;
  return node;
}

IFexpression* if_commands_else_commands(Expr* expr, CommandList* list, CommandList* else_list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF_ELSE;
  node->content.if_else_type.expr = expr;
  node->content.if_else_type.list = list;
  node->content.if_else_type.else_list = else_list;
  return node;
}

IFexpression* if_command_else_commands(Expr* expr, Command* cmd, CommandList* else_list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  list->cmd = cmd;
  list->next = NULL;
  node->kind = E_IF_ELSE;
  node->content.if_else_type.expr = expr;
  node->content.if_else_type.list = list;
  node->content.if_else_type.else_list = else_list;
  return node;
}

//------- WHILE expressions ----------------
WHILEexpression* while_command(Expr* expr, Command* cmd) {
  WHILEexpression* node = (WHILEexpression*) malloc(sizeof(WHILEexpression));
  CommandList* list = (CommandList*) malloc(sizeof(CommandList));
  list->cmd = cmd;
  list->next = NULL;
  node->expr = expr;
  node->list = list;
  return node;
}

WHILEexpression* while_commands(Expr* expr, CommandList* list) {
  WHILEexpression* node = (WHILEexpression*) malloc(sizeof(WHILEexpression));
  node->expr = expr;
  node->list = list;
  return node;
}

//------- INPUT/OUTPUT expressions ----------------

TYPES_STR* ast_string_of_types(char* type) {
  TYPES_STR* node = (TYPES_STR*) malloc(sizeof(TYPES_STR));
  node->types = strdup(type);
  return node;
}

PRINTF_EXP* ast_printf(TYPES_STR* types, PrintVarsList* vars) {
  PRINTF_EXP* node = (PRINTF_EXP*) malloc(sizeof(PRINTF_EXP));
  node->string_of_types = types;
  node->vars = vars;
  return node;
}

PrintVarsList* ast_printlist(char* var, PrintVarsList* next) {
  PrintVarsList* node = (PrintVarsList*) malloc(sizeof(PrintVarsList));
  node->name = strdup(var);
  node->next = next;
  return node;
}

SCANF_EXP* ast_scanf(TYPES_STR* types, ScanDeclarationList* vars) {
  SCANF_EXP* node = (SCANF_EXP*) malloc(sizeof(SCANF_EXP));
  node->string_of_types = types;
  node->vars = vars;
  return node;
}

ScanDeclarationList* ast_scanlist(char* var, ScanDeclarationList* next) {
  ScanDeclarationList* node = (ScanDeclarationList*) malloc(sizeof(ScanDeclarationList));
  node->declaration = strdup(var);
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


DeclarationList* ast_declaration(char* name, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->type = E_DECLARATION;
  node->content.name = strdup(name);
  node->next = next;
  return node;
}

DeclarationList* ast_assignment(char* name, Expr* expression, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->type = E_ASSIGNMENT;
  node->content.name = strdup(name);
  node->content.asg.expression = expression;
  node->next = next;
  return node;
}

AsgList* ast_assignmentList(char* name, Expr* expression, AsgList* next) {
  AsgList* node = (AsgList*) malloc(sizeof(AsgList));
  node->name = strdup(name);
  node->expression = expression;
  node->next = next;
  return node;
}

//------- Expressions functions -------------
NUMBER* ast_integer(int v) {
  NUMBER* node = (NUMBER*) malloc(sizeof(NUMBER));
  node->content.valuei = v;
  node->type = E_INTEGER;
  return node;
}

NUMBER* ast_float(float v) {
  NUMBER* node = (NUMBER*) malloc(sizeof(NUMBER));
  node->content.valuef = v;
  node->type = E_FLOAT;
  return node;
}

Expr* ast_number(NUMBER* m) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->attr.arguments.number = m;
  node->kind = E_NUM;
  return node;
}

Expr* ast_variable(char* v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->attr.arguments.variable = strdup(v);
  node->kind = E_VARIABLE;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->parenthesis = E_HAS_NOT;
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


