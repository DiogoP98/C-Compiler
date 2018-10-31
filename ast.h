
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_FLOAT
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

struct _CommandList {
    struct _Command* expr;
    struct _CommandList* next;
};

struct _Command {
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
      struct _BoolExpr* bleft;
      struct _BoolExpr* bright;
    } relop; // for binary expressions
  } attr_bool;
};


typedef struct _CommandList CommandList;
typedef struct _Command Command;
typedef struct _Expr Expr; // Convenience typedef
typedef struct _BoolExpr BoolExpr;
typedef struct _BoolExprList BoolExprList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_float(float v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
CommandList* ast_commandList(Command* cmd, CommandList* next);
BoolExprList* ast_boolExprlist(BoolExpr* expr, BoolExprList* next);
BoolExpr* ast_bool(int v);
BoolExpr* ast_boolNot(int operator, BoolExpr* bexpr);
BoolExpr* ast_boolOperation(int operator, BoolExpr* left, BoolExpr* right);
BoolExpr* ast_boolOperation2(int operator, Expr* left, Expr* right);
BoolExpr* ast_singleExpr(Expr* expr);

// The expression can be int or float
Expr* ast_number(Expr* expr);
Command* if_command(BoolExpr* bexpr);

#endif
