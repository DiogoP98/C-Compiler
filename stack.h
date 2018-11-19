#ifndef __stack_h__
#define __stack_h__

#include "ast.h"

typedef enum {LDC, ADI, SBI, MPI} IKind;

typedef struct _Instr{
    IKind kind;
    int arg;
} Instr;

typedef struct _Instr_List{
    struct _Instr* instruction;
    struct _Instr_List* next;
} Instr_List;

Instr* mkInstr(IKind kind, int n);
Instr* head(Instr_List* l);
Instr_List* tail(Instr_List* l);
Instr_List* append(Instr_List* l1, Instr_List* l2);
Instr_List* mkList(Instr* code, Instr_List* l2);
Instr_List* compile(Expr* expr);

void printInstr(Instr* instr);
void printListIntrs(Instr_List* list);

#endif
