#ifndef __stack_h__
#define __stack_h__

#include "ast.h"

typedef enum {LDC, ADI, SBI, MPI, LOD, STO, RDI, FJP, GRT, WRI, UJP, LABEL, EQU, NEQ, LDA} IKind;

typedef struct _Instr{
    IKind kind;
    union {
        char name[64];
        int arg;
    } arg;
} Instr;

typedef struct _Instr_List{
    struct _Instr* instruction;
    struct _Instr_List* next;
} Instr_List;

Instr* mkInstr(IKind kind, int n);
Instr* head(Instr_List* l);
Instr* compileDeclaration(DECL* declaration)
Instr_List* tail(Instr_List* l);
Instr_List* append(Instr_List* l1, Instr_List* l2);
Instr_List* mkList(Instr* code, Instr_List* l2);
Instr_List* compileExpression(Expr* expr);
Instr_list* compileAssignment(ASG* asg)
Instr_List* compileCmd(Command* cmd);
Instr_List* compile(CommandList* list);

void printInstr(Instr* instr);
void printListIntrs(Instr_List* list);

#endif
