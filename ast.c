// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

ExprList* ast_exprlist
(Expr* expr, ExprList* next) {
  ExprList* node = (ExprList*) malloc(sizeof(ExprList));
  node->expr = expr;
  node->next = next;
  return node;
}

ExprList* ast_boolExprlist
(BoolExpr* expr, ExprList* next) {
  ExprList* node = (ExprList*) malloc(sizeof(ExprList));
  node->expr = expr;
  node->next = next;
  return node;
}

BoolExpr* ast_bool(Expr* v) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOL;
  node->attr.value = (v->attr.value==0)? 0:1;
  return node;
}

BoolExpr* ast_boolOperation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_RELOP;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}
