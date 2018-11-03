
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
  } kind;
  struct _DeclarationList* declnext;
  struct _IFexpression* ifnext;
  struct _WHILEexpression* whilenext;
  struct _PRINTF_EXP* printnext;
  struct _SCANF_EXP* scannext;
};

struct _IFexpression {
  enum {
    E_IF_EXPR,
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
    E_ASSIGNMENT,
    E_DECLARATION
  } type;
  struct _ASG* assignment;
  struct _DECL* declaration;
  struct _DeclarationList* next;
};

struct _ScanDeclarationList {
  struct _DECL* declaration;
  struct _ScanDeclarationList* next;
};

struct _DECL {
  enum {
    E_ARRAY,
    E_SINGLE
  } type;
  char* name;
  int size;
};

struct _ASG {
  enum {
    E_ARRAY_ASG,
    E_SINGLE_ASG
  } type;
  char* name;
  int position;
  struct _Expr* value;
};

struct _PRINTF_EXP {
  char* string_of_types;
  struct _DeclarationList* vars;
};

struct _SCANF_EXP {
  char* string_of_types;
  struct _ScanDeclarationList* vars;
};

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_FLOAT
  } kind;
  union {
    int valuei;
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
typedef struct _WHILEexpression WHILEexpression;
typedef struct _DeclarationList DeclarationList;
typedef struct _ASG ASG;
typedef struct _DECL DECL;
typedef struct _PRINTF_EXP PRINTF_EXP;
typedef struct _SCANF_EXP SCANF_EXP;
typedef struct _Expr Expr; 
typedef struct _BoolExpr BoolExpr;
typedef struct _BoolExprList BoolExprList;
typedef struct _ScanDeclarationList ScanDeclarationList;


//------- Command list -----------------
CommandList* ast_commandList(Command* cmd, CommandList* next);

//------- Command functions -------------
Command* if_declaration(IFexpression* ifnext);
Command* while_declaration(WHILEexpression* whilenext);
Command* assignment_declaration(DeclarationList* next);
Command* declaration_declaration(DeclarationList* next);
Command* printf_declaration(PRINTF_EXP* printnext);
Command* scanf_declaration(SCANF_EXP* scannext);

//------- IF expressions ----------------
IFexpression* if_command(BoolExpr* bexpr, CommandList* list);
IFexpression* if_else_command(BoolExpr* bexpr, CommandList* list, CommandList* else_list);

//------- WHILE expressions ----------------
WHILEexpression* while_command(BoolExpr* bexpr, CommandList* list);

//------- INPUT/OUTPUT expressions ----------------
PRINTF_EXP* ast_printf(char* types, DeclarationList* vars);
SCANF_EXP* ast_scanf(char* type, ScanDeclarationList* vars);
ScanDeclarationList* ast_scanlist(DECL* var, ScanDeclarationList* next);

//------- Declarations/Assignments expressions ----------------
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
