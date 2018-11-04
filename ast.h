
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
    E_VAR,
    E_ASG,
    E_PRINT,
    E_SCAN
  } kind;

  struct _VarList* list;
  struct _AsgList* asg_list;
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

struct _AsgList {
  struct _ASG* assignment;
  struct _AsgList* next;
};

struct _VarList {
  int type;
  struct _DeclarationList* list;
};

struct _ScanDeclarationList {
  struct _DECL* declaration;
  struct _ScanDeclarationList* next;
};

struct _DECL {
  char* name;
};

struct _ASG {
  struct _DECL* name;
  struct _Expr* value;
};

struct _PRINTF_EXP {
  struct _TYPES* string_of_types;
  struct _DeclarationList* vars;
};

struct _SCANF_EXP {
  struct _TYPES* string_of_types;
  struct _ScanDeclarationList* vars;
};

struct _TYPES {
  char* types;
};

// AST for expressions
struct _Expr {
  enum { 
    E_OPERATION,
    E_NUM,
  } kind;

  enum {
    E_HAS,
    E_HASNOT
  } parenthesis;

  union {
    struct _NUMBER* number;
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
    struct _NUMBER* value; // for boolean values
    struct { 
      int operator;
      struct _BoolExpr* bleft;
      struct _BoolExpr* bright;
      struct _Expr* right;
      struct _Expr* left;
    } relop; // for binary expressions
  } attr_bool;
};

struct _NUMBER {
  enum { 
    E_INTEGER,
    E_FLOAT,
  } type;

  int valuei;
  float valuef;
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
typedef struct _VarList varList;
typedef struct _TYPES TYPES_STR;
typedef struct _NUMBER NUMBER;
typedef struct _AsgList AsgList;

//------- Command list -----------------
CommandList* ast_commandList(Command* cmd, CommandList* next);

//------- Command functions -------------
Command* if_declaration(IFexpression* ifnext);
Command* while_declaration(WHILEexpression* whilenext);
Command* variable_declaration(varList* list);
Command* printf_declaration(PRINTF_EXP* printnext);
Command* scanf_declaration(SCANF_EXP* scannext);
Command* assignment_declaration(AsgList* asg_list);

//------- IF expressions ----------------
IFexpression* if_command(BoolExpr* bexpr, Command* cmd);
IFexpression* if_command_else_command(BoolExpr* bexpr, Command* cmd, Command* else_cmd);
IFexpression* if_commands(BoolExpr* bexpr, CommandList* list);
IFexpression* if_commands_else_command(BoolExpr* bexpr, CommandList* list, Command* else_cmd);
IFexpression* if_commands_else_commands(BoolExpr* bexpr, CommandList* list, CommandList* else_list);
IFexpression* if_command_else_commands(BoolExpr* bexpr, Command* cmd, CommandList* else_list);

//------- WHILE expressions ----------------
WHILEexpression* while_command(BoolExpr* bexpr, Command* cmd);
WHILEexpression* while_commands(BoolExpr* bexpr, CommandList* list);

//------- INPUT/OUTPUT expressions ----------------
TYPES_STR* ast_string_of_types(char* type);
PRINTF_EXP* ast_printf(TYPES_STR* types, DeclarationList* vars);
SCANF_EXP* ast_scanf(TYPES_STR* type, ScanDeclarationList* vars);
ScanDeclarationList* ast_scanlist(DECL* var, ScanDeclarationList* next);

//------- Declarations/Assignments expressions ----------------
varList* ast_varlist(int type, DeclarationList* next);
DeclarationList* ast_declaration(DECL* decl, DeclarationList* next);
DeclarationList* ast_assignment(ASG* asg, DeclarationList* next);
AsgList* ast_assignmentList(ASG* asg, AsgList* next);
DECL* var_declaration(char* s);
ASG* var_assignment(DECL* s, Expr* expr);

//------- Expressions functions -------------
NUMBER* ast_integer(int v);
NUMBER* ast_float(float v);
Expr* ast_number(NUMBER* m);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_pexpr(Expr* expr);

//------- Bool Expressions functions -------------
BoolExpr* ast_bool(NUMBER* v);
BoolExpr* ast_pbexpr(BoolExpr* bexpr);
BoolExpr* ast_boolOperation(int operator, BoolExpr* left, BoolExpr* right);
BoolExpr* ast_boolOperation2(int operator, Expr* left, Expr* right);
BoolExpr* ast_singleExpr(Expr* expr);

#endif
