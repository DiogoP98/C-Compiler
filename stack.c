#include <stdlib.h> // for malloc
#include "stack.h"
#include <stdio.h>
#include "parser.h"

Instr* mkInstr(IKind kind, int n) {
    Instr* node = (Instr*) malloc(sizeof(Instr)); 
    node->type = E_INT2;
    node->kind = kind;
    node->arg.argi = n;
    return node;
}

Instr* mkInstr2(IKind kind, char* name) {
    Instr* node = (Instr*) malloc(sizeof(Instr)); 
    node->type = E_NAME;
    node->kind = kind;
    node->arg.name = name;
    return node;
}

Instr* mkInstr3(IKind kind, float n) {
    Instr* node = (Instr*) malloc(sizeof(Instr)); 
    node->type = E_FLOAT2;
    node->kind = kind;
    node->arg.argf = n;
    return node;
}

Instr* head(Instr_List* l) {
    return l->instruction;
}

Instr_List* tail(Instr_List* l) {
    return l->next;
}

Instr_List* append(Instr_List* l1, Instr_List* l2) {
    if(l1 == NULL)
        return l2; 
    
    return mkList(head(l1), append(tail(l1),l2));
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
            if(instr->type == E_NAME)
                printf("LDC %s\n", instr->arg.name);
            else
               printf("LDC %d\n", instr->arg.argi); 
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

Instr_List* compileExpression(Expr* expr){
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));
    Instr_List* l2 = (Instr_List*)malloc(sizeof(Instr_List));

    if (expr == 0) {
        yyerror("Null expression!!");
        return NULL;
    }
    
    if (expr->kind == E_NUM) {
        NUMBER* n = expr->attr.number;
        if(n->type == E_INTEGER)
            return mkList(mkInstr(LDC, n->content.valuei), NULL);
        else
            return mkList(mkInstr3(LDC, n->content.valuef), NULL);
        
    }
        
    else if (expr->kind == E_OPERATION) {
        switch (expr->attr.op.operator) {
            case PLUS:
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l2 = append(l1, mkList(mkInstr(ADI,0),NULL));
                break;
            case SUB:
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l2 = append(l1, mkList(mkInstr(SBI,0),NULL));
                break;
            case MUL:                
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l2 = append(l1, mkList(mkInstr(MPI,0),NULL));
                break;
            default:
                printf("Undefined operation\n");
        }
    }

    return l2;
}

Instr* compileDeclaration(DECL* declaration) {
    if (declaration == NULL) 
        return NULL;

    Instr* l1 = (Instr*)malloc(sizeof(Instr));
    l1 = mkInstr2(LOD, declaration->name);

    return l1;
}

Instr_List* compileAssignment(ASG* asg) {
    if (asg == NULL)
        return NULL;

    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));
    l1->instruction = compileDeclaration(asg->name);
    l1 = append(l1, compileExpression(asg->value));
    l1 = append(l1, mkList(mkInstr(STO, NULL),NULL));

    return l1;
} 

Instr_List* compileAssignmentList(AsgList* asg_list) {
    AsgList* assignmentList = asg_list;

    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    while(assignmentList != NULL) {
        append(l1, compileAssignment(assignmentList->assignment));
        assignmentList = assignmentList->next;
    }

    return l1;
}

Instr_List* compileCmd(Command* cmd) {
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    if(cmd == NULL) return NULL;

    switch (cmd->kind) {
      case E_IF:
        //l1 = cmdIf(cmd->content.ifnext);
        break;
      case E_WHILE:
        //l1 = cmdWhile(cmd->content.whilenext);
        break;
      case E_VAR:
        //l1 = cmdVarList(cmd->content.list);
        break;
      case E_ASG:
        l1 = compileAssignmentList(cmd->content.asg_list);
        break;
      case E_PRINT:
        //l1 = cmdPrintf(cmd->content.printnext);
        break;
      case E_SCAN:
        //l1 = cmdScanf(cmd->content.scannext);
        break;
    }

    return l1;
}

Instr_List* compile(CommandList* list) {
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    if(list->cmd == NULL) 
        return NULL;

    l1 = compileCmd(list->cmd);

    while(list->next != NULL) { 
        list = list->next;
        append(l1, compileCmd(list->cmd));
    }

    return l1;
}

int main(int argc, char** argv) {
    yyparse();
    Instr_List* l = compile(root);
    printListIntrs(l);
    return 0;
}
