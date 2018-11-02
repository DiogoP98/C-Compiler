
// AST definitions
#ifndef __ast_h__
#define __ast_h__

struct _CommandList {
    struct _Command* expr;
    struct _CommandList* next;
};

struct _Command {
  enum {
    E_IF,
    E_WHILE,
    E_ASG,
    E_DECL,
    E_PRINT,
    E_SCAN
  }kind;
};

struct _IFexpression {
  enum {
    E_IF,
    E_IF_ELSE
  } kind;

  struct {
    struct _BoolExpr* bexpr;
    struct _CommandList* list;
  } if_type;
  
  struct {
    struct _BoolExpr* bexpr;
    struct _CommandList* list;
    struct _CommandList* else_list;
  } if_else_type;
};

struct _WHILEexpression {
  struct _BoolExpr* bexpr;
  struct _CommandList* list;
};

struct _DeclarationList {
  enum {
    E_assignment,
    E_declaration
  } type;
  struct _ASG* assignemt;
  struct _DECL* declaration;
  struct _DeclarationList* next;
};

struct _DECL {
  enum {
    E_array,
    E_single
  } type;
  char* name;
  int size;
};

struct _ASG {
  enum {
    E_array,
    E_single
  } type;
  char* name;
  int position;
  struct _Expr* value;
};

struct _PRINT {

};

struct _SCAN {

};

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_FLOAT
  } kind;
  union {
    int value;
    float valuef;
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
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
typedef struct _DeclarationList DeclarationList;
typedef struct _ASG ASG;
typedef struct _DECL DECL;
typedef struct _PRINT PRINT;
typedef struct _SCAN SCAN;
typedef struct _Expr Expr; 
typedef struct _BoolExpr BoolExpr;
typedef struct _BoolExprList BoolExprList;


//------- Command list -----------------
CommandList* ast_commandList(Command* cmd, CommandList* next);

//------- Command functions -------------
Command* if_declaration();
Command* while_declaration();
Command* assignment_declaration();
Command* declaration_declaration();

//------- IF expressions ----------------
IFexpression* if_command(BoolExpr* bexpr, CommandList* list);
IFexpression* if_else_command(BoolExpr* bexpr, CommandList* list, CommandList* else_list);

//------- WHILE expressions ----------------
WHILEexpression* while_command(BoolExpr* bexpr, CommandList* list);

//------- Declarations expressions ----------------
DeclarationList* declaration(DECL* decl, DeclarationList* next);
DeclarationList* assignment(ASG* asg, DeclarationList* next);
DECL* var_declaration(char* s);
DECL* array_declaration(char* s, int size);
ASG* var_assignment(char*s, Expr* expr);
ASG* array_assignment(char* s, int position, Expr* expr);

//------- Expressions functions -------------
Expr* ast_integer(int v);
Expr* ast_float(float v);
Expr* ast_operation(int operator, Expr* left, Expr* right);

//------- Bool Expressions functions -------------
BoolExpr* ast_bool(int v);
BoolExpr* ast_boolNot(int operator, BoolExpr* bexpr);
BoolExpr* ast_boolOperation(int operator, BoolExpr* left, BoolExpr* right);
BoolExpr* ast_boolOperation2(int operator, Expr* left, Expr* right);
BoolExpr* ast_singleExpr(Expr* expr);

#endif
