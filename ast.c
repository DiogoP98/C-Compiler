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

Command* assignment_declaration(DeclarationList* next) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_ASG; 
  node->declnext = next;
  return node;
}

Command* declaration_declaration(DeclarationList* next) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->kind = E_DECL;
  node->declnext = next;
  return node; 
}

//------- IF expressions ----------------
IFexpression* if_command(BoolExpr* bexpr, CommandList* list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF_EXPR;
  node->if_type.bexpr = bexpr;
  node->if_type.list = list;
  return node;
}

IFexpression* if_else_command(BoolExpr* bexpr, CommandList* list, CommandList* else_list) {
  IFexpression* node = (IFexpression*) malloc(sizeof(IFexpression));
  node->kind = E_IF_ELSE;
  node->if_type.bexpr = bexpr;
  node->if_type.list = list;
  node->if_else_type.else_list = else_list;
  return node;
}

//------- WHILE expressions ----------------
WHILEexpression* while_command(BoolExpr* bexpr, CommandList* list) {
  WHILEexpression* node = (WHILEexpression*) malloc(sizeof(WHILEexpression));
  node->bexpr = bexpr;
  node->list = list;
  return node;
}

//------- INPUT/OUTPUT expressions ----------------
PRINTF_EXP* ast_printf(char* types, DeclarationList* vars) {
  PRINTF_EXP* node = (PRINTF_EXP*) malloc(sizeof(PRINTF_EXP));
  node->string_of_types = types;
  node->vars = vars;
  return node;
}

SCANF_EXP* ast_scanf(char* type, ScanDeclarationList* vars) {
  SCANF_EXP* node = (SCANF_EXP*) malloc(sizeof(SCANF_EXP));
  node->string_of_types = type;
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
DeclarationList* declaration(DECL* decl, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->type = E_DECLARATION;
  node->declaration = decl;
  node->next = next;
  return node;
}

DeclarationList* assignment(ASG* asg, DeclarationList* next) {
  DeclarationList* node = (DeclarationList*) malloc(sizeof(DeclarationList));
  node->type = E_ASSIGNMENT;
  node->assignment = asg;
  node->next = next;
  return node;
}

DECL* var_declaration(char* s) {
  DECL* node = (DECL*) malloc(sizeof(DECL));
  node ->type = E_SINGLE;
  node->name = s;
  return node;
}

DECL* array_declaration(char* s, int size) {
  DECL* node = (DECL*) malloc(sizeof(DECL));
  node -> type = E_ARRAY;
  node -> size = size;
  node -> name = s;
  return node;
}

ASG* var_assignment(char* s, Expr* expr) {
  ASG* node = (ASG*) malloc(sizeof(ASG));
  node->type = E_SINGLE_ASG;
  node->name = s;
  node->value = expr;
  return node;
}

ASG* array_assignment(char* s, int position, Expr* expr) {
  ASG* node = (ASG*) malloc(sizeof(ASG));
  node->type = E_ARRAY_ASG;
  node->position = position;
  node->name = s;
  node->value = expr;
  return node;
}

//------- Expressions functions -------------
Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.valuei = v;
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
  node->parenthesis = E_HASNOT;
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


