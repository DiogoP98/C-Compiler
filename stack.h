#ifndef __stack_h__
#define __stack_h__

#include "ast.h"

typedef enum {LDC, ADI, SBI, MPI, LOD, STO, RDI, FJP, GRT, WRI, UJP, LABEL, EQU, NEQ, LDA} IKind;

typedef struct _Instr{
    enum {
        E_NAME,
        E_INT2,
        E_FLOAT2
    } type;
    IKind kind;
    union {
        char* name;
        float argf;
        int argi;
    } arg;
} Instr;

typedef struct _Instr_List{
    struct _Instr* instruction;
    struct _Instr_List* next;
} Instr_List;

Instr* mkInstr(IKind kind, int n);
Instr* mkInstr2(IKind kind, char* name);
Instr* mkInstr3(IKind kind, float n);
Instr* head(Instr_List* l);
Instr* compileDeclaration(DECL* declaration);
Instr_List* tail(Instr_List* l);
Instr_List* append(Instr_List* l1, Instr_List* l2);
Instr_List* mkList(Instr* code, Instr_List* l2);
Instr_List* compileExpression(Expr* expr);
Instr_List* compileAssignment(ASG* asg);
Instr_List* compileCmd(Command* cmd);
Instr_List* compile(CommandList* list);

void printInstr(Instr* instr);
void printListIntrs(Instr_List* list);

#endif