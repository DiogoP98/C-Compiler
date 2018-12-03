
// AST definitions
#ifndef __ast_h__
#define __ast_h__

struct _CommandList {
    struct _Command* cmd;
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

  union {
    struct _VarList* list;
    struct _AsgList* asg_list;
    struct _IFexpression* ifnext;
    struct _WHILEexpression* whilenext;
    struct _PRINTF_EXP* printnext;
    struct _SCANF_EXP* scannext;
  } content;
};

struct _IFexpression {
  enum {
    E_IF_EXPR,
    E_IF_ELSE
  } kind;

  union {
    struct {
      struct _Expr* expr;
      struct _CommandList* list;
    } if_type;
    
    struct {
      struct _Expr* expr;
      struct _CommandList* list;
      struct _CommandList* else_list;
    } if_else_type;
  } content;
};

struct _WHILEexpression {
  struct _Expr* expr;
  struct _CommandList* list;
};

struct _DeclarationList {
  enum {
    E_ASSIGNMENT,
    E_DECLARATION
  } type;

  union {
    struct _ASG* assignment;
    struct _DECL* declaration;
  } content;
  
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
    E_VARIABLE,
    E_NUM,
  } kind;

  enum {
    E_HAS,
    E_HAS_NOT
  } parenthesis;

  union {

    union{
      struct _NUMBER* number;
      char* variable;
    } arguments;

    struct { 
      int operator;
      struct _Expr* left;
      struct _Expr* right;
    } op;
  } attr;
};

struct _NUMBER {
  enum { 
    E_INTEGER,
    E_FLOAT,
  } type;

  union {
    int valuei;
    float valuef;
  } content;
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
IFexpression* if_command(Expr* expr, Command* cmd);
IFexpression* if_command_else_command(Expr* expr, Command* cmd, Command* else_cmd);
IFexpression* if_commands(Expr* expr, CommandList* list);
IFexpression* if_commands_else_command(Expr* expr, CommandList* list, Command* else_cmd);
IFexpression* if_commands_else_commands(Expr* expr, CommandList* list, CommandList* else_list);
IFexpression* if_command_else_commands(Expr* expr, Command* cmd, CommandList* else_list);

//------- WHILE expressions ----------------
WHILEexpression* while_command(Expr* expr, Command* cmd);
WHILEexpression* while_commands(Expr* expr, CommandList* list);

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
Expr* ast_variable(char* v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_pexpr(Expr* expr);

#endif
