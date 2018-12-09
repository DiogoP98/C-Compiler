
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
  int type;

  enum {
    E_ASSIGNMENT,
    E_DECLARATION
  } op;

  char* name;

  union {
    struct _Expr* expression;
  } asg;

  
  struct _DeclarationList* next;
};

struct _AsgList {
  char* name;
  struct _Expr* expression;
  struct _AsgList* next;
};

struct _VarList {
  int type;
  struct _DeclarationList* list;
};

struct _PRINTF_EXP {
  struct _TYPES* string_of_types;
  struct _PrintVarsList* vars;
};

struct _PrintVarsList {
  char* name;
  struct _PrintVarsList* next;
};

struct _SCANF_EXP {
  struct _TYPES* string_of_types;
  struct _ScanDeclarationList* vars;
};

struct _ScanDeclarationList {
  char* declaration;
  struct _ScanDeclarationList* next;
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
    E_EXPR_FLOAT,
    E_EXPR_INT
  } type;

  union {
    int numberint;
    float numberfloat;
    char* variable;

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
typedef struct _PRINTF_EXP PRINTF_EXP;
typedef struct _PrintVarsList PrintVarsList;
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
PRINTF_EXP* ast_printf(TYPES_STR* types, PrintVarsList* vars);
SCANF_EXP* ast_scanf(TYPES_STR* type, ScanDeclarationList* vars);
ScanDeclarationList* ast_scanlist(char* var, ScanDeclarationList* next);
PrintVarsList* ast_printlist(char* var, PrintVarsList* next);

//------- Declarations/Assignments expressions ----------------
varList* ast_varlist(int type, DeclarationList* next);
DeclarationList* ast_declaration(char* name, DeclarationList* next);
DeclarationList* ast_assignment(char* name, Expr* expression, DeclarationList* next);
AsgList* ast_assignmentList(char* name, Expr* expression, AsgList* next);

//------- Expressions functions -------------
Expr* ast_integer(int v);
Expr* ast_float(float v);
Expr* ast_variable_float(char* v);
Expr* ast_variable_int(char* v);
Expr* ast_operation(int operator, Expr* left, Expr* right);

#endif
