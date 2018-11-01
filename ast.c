// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

CommandList* ast_commandList(Command* cmd, CommandList* next) {
  CommandList* node = (CommandList*) malloc(sizeof(CommandList));
  node->expr = cmd;
  node->next = next;
  return node;
}

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

Command* atribution_declaration() {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_ATR; 
  return node;
}

Command* declaration_declaration() {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_DECL;
  return node; 
}

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

WHILEexpression* while_command(BoolExpr* bexpr, struct CommandList* list) {
  WHILEexpression* node = (WHILEexpression*) malloc(sizeof(WHILEexpression));
  node->bexpr = bexpr;
  node->list = list;
  return node;
}

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


