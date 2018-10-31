
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
  enum {
    E_IF,
    E_WHILE,
    E_ATR,
    E_DECL,
    E_PRINT,
    E_SCAN
  }kind;
  struct _IFexpression if_expression;
  struct _WHILEexpression while_expr; 
};

struct _IFexpression {
  struct _BoolExpr* bexpr;
  struct _Command* cmd;
  struct _ELSEexpression* else_expr;
};

struct _ELSEexpression {
  struct _Command* cmd;
};

struct _WHILEexpression {
  struct _BoolExpr* bexpr;
  struct _Command* cmd;
};

struct _ATR {

};

struct _DECL {

};

struct _PRINT {

};

struct _SCAN {

};

struct _BoolExpr {
  enum { 
    E_BOOL,
    E_RELOP
  } kind;
  union {
    int value; // for boolean values
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
typedef struct _IFexpression IFexpression;
typedef struct _ELSEexprssion ELSEexpression;
typedef struct _WHILEexpression WHILEexpression;
typedef struct _ATR ATR;
typedef struct _DECL DECL;
typedef struct _PRINT PRINT;
typedef struct _SCAN SCAN;
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

#endif
