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
        case STO:
            printf("STO\n");
            break;
        case LOD:
            printf("LOD %s\n", instr->arg.name);
            break;
        case LABEL:
            printf("LABEL L%d\n", instr->arg.argi);
            break;
        case FJP: 
            printf("FJP L%d\n", instr->arg.argi);
            break;
        case UJP:
            printf("UJP L%d\n", instr->arg.argi);
            break;
        case MST:
            printf("MST %d\n", instr->arg.argi);
            break;
        case CUP:
            printf("CUP 0 L %s\n", instr->arg.name);
            break;
        default:
            printf("Undefined instruction kind %d\n", instr->kind);
    }
}

void printListIntrs(Instr_List* list) {
    if(head(list) == NULL){
        return;
    }

    printInstr(head(list));
    
    if(tail(list) != NULL)
        printListIntrs(tail(list));
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
            //TODO ver como tratar de operadores logicos
            case DIV:
                printf("/:\n");
                break;
            case MOD:
                printf("%%:\n");
                break;
                case EQUAL:
                printf("==:\n");
                break;
            case DIF:
                printf("!=:\n");
                break;
            case LES:
                printf("<:\n");
                break;
            case LOQ:
                printf("<=:\n");
                break;
            case GRE:
                printf(">:\n");
                break;
            case GOQ:
                printf(">=:\n");
                break;
            case OR:
                printf("||:\n");
                break;
            case AND:
                printf("&&:\n");
                break;
            case NOTOP:
                printf("!:\n");
                break;
            default:
                printf("Undefined operation\n");
        }
    }

    return l2;
}

Instr_List* compileDeclaration(DECL* declaration) {
    if (declaration == NULL) 
        return NULL;

    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));
    l1 = mkList(mkInstr2(LOD, declaration->name),NULL);

    return l1;
}

Instr_List* compileAssignment(ASG* asg) {
    if (asg == NULL)
        return NULL;
    
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));
    l1 = compileDeclaration(asg->name);
    l1 = append(l1, compileExpression(asg->value));
    l1 = append(l1, mkList(mkInstr(STO, NULL),NULL));

    return l1;
} 

Instr_List* compileVarList(varList* list) {
    varList* varList = list;

    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    l1 = compileDeclarationList(list->list);

    return l1;
}

Instr_List* compileAssignmentList(AsgList* asg_list) {
    AsgList* assignmentList = asg_list;

    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    while(assignmentList != NULL) {
        l1 = append(l1, compileAssignment(assignmentList->assignment));
        assignmentList = assignmentList->next;
    }

    return l1;
}

Instr_List* compileDeclarationList(DeclarationList* decl_list) {
    DeclarationList* declList = decl_list;

    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    while(declList != NULL) {
        switch(declList->type) {
            case E_ASSIGNMENT:
                l1 = compileAssignment(declList->content.assignment);
                break;
            case E_DECLARATION:
                l1 = compileDeclaration(declList->content.declaration);
                break;
        } 

        declList = declList->next;
    }

    return l1;
}

Instr_List* compileIf(IFexpression* if_expr) {
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    if(if_expr->kind == E_IF_EXPR) {
        l1 = compileExpression(if_expr->content.if_type.expr);
        l1 = append(l1, mkList(mkInstr(FJP, LABEL_COUNT), NULL));
        l1 = append(l1, compile(if_expr->content.if_type.list));
        l1 = append(l1, mkList(mkInstr(LABEL, LABEL_COUNT), NULL));
    }
    else {
        l1 = compileExpression(if_expr->content.if_else_type.expr);
        l1 = append(l1, mkList(mkInstr(FJP, LABEL_COUNT), NULL));
        l1 = append(l1, compile(if_expr->content.if_else_type.list));
        l1 = append(l1, mkList(mkInstr(UJP, LABEL_COUNT+1), NULL)); 
        l1 = append(l1, mkList(mkInstr(LABEL,LABEL_COUNT), NULL));
        LABEL_COUNT++;
        l1 = append(l1, compile(if_expr->content.if_else_type.else_list));
        l1 = append(l1, mkList(mkInstr(LABEL,LABEL_COUNT), NULL));
        LABEL_COUNT++;
    }

    return l1;
}

Instr_List* compileWhile(WHILEexpression* while_expr){
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    l1 = mkList(mkInstr(LABEL, LABEL_COUNT), NULL);
    LABEL_COUNT++;
    l1 = append(l1, compileExpression(while_expr->expr));
    l1 = append(l1, mkList(mkInstr(FJP, LABEL_COUNT), NULL));
    l1 = append(l1, compile(while_expr->list));
    l1 = append(l1, mkList(mkInstr(UJP, LABEL_COUNT-1), NULL));
    l1 = append(l1, mkList(mkInstr(LABEL, LABEL_COUNT), NULL));

    return l1;
}

Instr_List* compilePrintf(PRINTF_EXP* printf_expr){
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    l1 = mkList(mkInstr(MST, 0), NULL);
    l1 = append(l1, mkList(mkInstr2(LOD, printf_expr->string_of_types->types), NULL));
    l1 = append(l1, compileDeclarationList(printf_expr->vars));
    l1 = append(l1, mkList(mkInstr2(CUP, "PRINTF"), NULL));

    return l1;
}

Instr_List* compileScanf(SCANF_EXP* scanf_expr){
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    l1 = mkList(mkInstr(MST, 0), NULL);
    l1 = append(l1, mkList(mkInstr2(LOD, scanf_expr->string_of_types->types), NULL));
    ScanDeclarationList *scanDecList = scanf_expr->vars;
    while(scanDecList != NULL){
        l1 = append(l1, compileDeclaration(scanDecList->declaration));
        scanDecList = scanDecList->next;
    }
    l1 = append(l1, mkList(mkInstr2(CUP, "SCANF"), NULL));

    return l1;
}

Instr_List* compileCmd(Command* cmd) {
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    if(cmd == NULL) {
        printf("compiling null\n");
        return NULL;
    }

    switch (cmd->kind) {
        case E_IF:
            l1 = compileIf(cmd->content.ifnext);
            break;
        case E_WHILE:
            l1 = compileWhile(cmd->content.whilenext);
            break;
        case E_VAR:
            l1 = compileVarList(cmd->content.list);
            break;
        case E_ASG:
            l1 = compileAssignmentList(cmd->content.asg_list);
            break;
        case E_PRINT:
            l1 = compilePrintf(cmd->content.printnext);
            break;
        case E_SCAN:
            l1 = compileScanf(cmd->content.scannext);
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
        l1 = append(l1, compileCmd(list->cmd));
    }

    return l1;
}

int main(int argc, char** argv) {
    yyparse();
    LABEL_COUNT = 0;
    Instr_List* l = compile(root);
    printListIntrs(l);
    return 0;
}
