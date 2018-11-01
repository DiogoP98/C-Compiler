// AST constructor functions

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
Command* if_declaration() {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_IF; 
  return node;
}

Command* while_declaration() {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_WHILE;
  return node; 
}

Command* assignment_declaration() {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_ASG; 
  return node;
}

Command* declaration_declaration() {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_DECL;
  return node; 
}

//------- IF expressions ----------------
IFexpression* if_command(BoolExpr* bexpr, struct CommandList* list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF;
  node->if_type.bexpr = bexpr;
  node->if_type.list = list;
  return node;
}

IFexpression* if_else_command(BoolExpr* bexpr, struct CommandList* list, struct CommandList* else_list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF_ELSE;
  node->if_type.bexpr = bexpr;
  node->if_type.list = list;
  node->if_else_type.else_list = else_list;
  return node;
}

//------- WHILE expressions ----------------
WHILEexpression* while_command(BoolExpr* bexpr, struct CommandList* list) {
  WHILEexpression* node = (WHILEexpression*) malloc(sizeof(WHILEexpression));
  node->bexpr = bexpr;
  node->list = list;
  return node;
}

//--------- Declaration List -------------
DeclarationList* declaration(DECL* decl, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->declaration = decl;
  node->next = next;
  return node;
}

DeclarationList* assignment(DECL* decl, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->assignemt = decl;
  node->next = next;
  return node;
}

DECL* int_variable(char* s, int type, int value) {
  DECL* node = (DECL*) malloc(sizeof(DECL));
  node->name = s;
  node->type = type;
  return node;
}

DECL* float_variable(char* s, int type, float value) {
  DECL* node = (DECL*) malloc(sizeof(DECL));
  node->name = s;
  node->type = type;
  return node;
}


//------- Expressions functions -------------
Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_float(float v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_FLOAT;
  node->attr.valuef = v;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

//------- Bool Expressions functions -------------
BoolExpr* ast_bool(int v) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOL;
  node->attr_bool.value = (v==0)? 0:1;
  return node;
}

BoolExpr* ast_boolNot(int operator, BoolExpr* bexpr) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOL;
  node->attr_bool.relop.operator = operator;
  node->attr_bool.relop.bleft = bexpr;
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
  //node->attr_bool.relop.left = left;
  //node->attr_bool.relop.right = right;
  return node;
}

BoolExpr* ast_singleExpr(Expr* expr) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  //node->attr_bool.relop.left = expr;
  return node;
}


