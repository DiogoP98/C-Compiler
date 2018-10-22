
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION
  } kind;
  union {
    int value; // for integer values
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

struct _ExprList {
    struct _Expr* expr;
    struct _ExprList* next;
};

struct _BoolExpr {
  enum { 
    E_BOOL,
    E_RELOP
  } kind;
  union {
    int value; // for bollean values
    struct { 
      int operator;
      struct _Expr* left;
      struct _Expr* right;
    } relop; // for binary expressions
  } atr_bool;
};

struct _BoolExprList {
    struct _BoolExpr* expr;
    struct _BoolExprList* next;
};

typedef struct _Expr Expr; // Convenience typedef
typedef struct _ExprList ExprList;
typedef struct _BoolExpr BoolExpr;
typedef struct _BoolExprList BoolExprList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
ExprList* ast_exprlist(Expr* expr, ExprList* next);
BoolExprList* ast_boolExprlist(BoolExpr* expr, BoolExprList* next);
BoolExpr* ast_bool(Expr* v);
BoolExpr* ast_boolOperation(int operator, BoolExpr* left, BoolExpr* right);


#endif
