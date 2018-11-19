#include <stdlib.h> // for malloc
#include "stack.h"
#include <stdio.h>
#include "parser.h"

Instr* mkInstr(IKind kind, int n) {
    Instr* node = (Instr*) malloc(sizeof(Instr)); 
    node->kind = kind;
    node->arg = n;
    return node;
}

Instr* head(Instr_List* l) {
    return l->instruction;
}

Instr_List* tail(Instr_List* l) {
    return l->next;
}

Instr_List* append(Instr_List* l1, Instr_List* l2) {
    Instr_List* node = (Instr_List*) malloc(sizeof(Instr_List));
    node->instruction =  head(l1);
    if(tail(l1) != NULL) 
        node -> next = append(tail(l1), l2);
    else
        node = append(l2,node);
    return node;
}

Instr_List* mkList(Instr* code, Instr_List* l) {
    Instr_List* node = (Instr_List*) malloc(sizeof(Instr_List));
    node->instruction = code;
    node->next = l;
    return node;
}

void printInstr(Instr* instr) {
    if (instr == NULL) {
        yyerror("Null instruction!!");
        return;
    }
    
    switch(instr->kind){
        case LDC:
            printf("LDC %d\n", instr->arg);
            break;
        case ADI:
            printf("ADI\n");
            break;
        case SBI:
            printf("SBI\n");
            break;
        case MPI:
            printf("MPI\n");
            break;
        default:
            printf("Undefined instruction kind\n");
    }
}

void printListIntrs(Instr_List* list) {
    printInstr(head(list));
    if(tail(list) != NULL) printListIntrs(tail(list));
}

Instr_List* compile(Expr* expr){
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));
    Instr_List* l2 = (Instr_List*)malloc(sizeof(Instr_List));

    if (expr == 0) {
        yyerror("Null expression!!");
        return NULL;
    }
    
    if (expr->kind == E_INTEGER) return mkList(mkInstr(LDC, expr->attr.value), NULL);
        
    else if (expr->kind == E_OPERATION) {
        switch (expr->attr.op.operator) {
            case PLUS:
                l1 = append(compile(expr->attr.op.left), compile(expr->attr.op.right));
                l2 = append(l1, mkList(mkInstr(ADI,0),NULL));
                break;
            case SUB:
                l1 = append(compile(expr->attr.op.left), compile(expr->attr.op.right));
                l2 = append(l1, mkList(mkInstr(SBI,0),NULL));
                break;
            case MUL:                
                l1 = append(compile(expr->attr.op.left), compile(expr->attr.op.right));
                l2 = append(l1, mkList(mkInstr(MPI,0),NULL));
                break;
            default:
                printf("Undefined operation\n");
        }
    }

    return l2;
}

int main(int argc, char** argv) {
    printf("here2\n");
    yyparse();
    printf("here");
    Instr_List* l = compile(root);
    printListIntrs(l);
    return 0;
}
