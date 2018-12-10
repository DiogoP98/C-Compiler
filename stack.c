#include <stdlib.h> // for malloc
#include "stack.h"
#include <stdio.h>
#include "parser.h"
#include <limits.h>
#include "MIPS.h"

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
    node->arg.name = strdup(name);

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
            switch(instr->type){
                case E_INT2:
                    printf("LDC %d\n", instr->arg.argi);
                    break;
                case E_FLOAT2:
                    printf("LDC %f\n", instr->arg.argf);
                    break;
            }
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
        case LDA:
            printf("LDA %s\n", instr->arg.name);
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
        case WRI:
            printf("WRI %s\n", instr->arg.name);
            break;
        case SCANF:
            printf("SCANF %s\n", instr->arg.name);
            break;
        default:
            printf("Undefined instruction kind %d\n", instr->kind);
    }
}

void printListIntrs(Instr_List* list) {
    if(head(list) == NULL)
        return;

    printInstr(head(list));
    
    if(tail(list) != NULL)
        printListIntrs(tail(list));
}

Instr_List* compileExpression(Expr* expr){
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    if (expr == 0) {
        yyerror("Null expression!!");
        return NULL;
    }

    if (expr->kind == E_NUM) {
        if(expr->type == E_EXPR_INT)
            return mkList(mkInstr(LDC, expr->attr.numberint), NULL);
        else
            return mkList(mkInstr3(LDC, expr->attr.numberfloat), NULL);
    }

    else if(expr->kind == E_VARIABLE) {
        char* variable = expr->attr.variable;

        return mkList(mkInstr2(LOD, variable), NULL);
    }
        
    else if (expr->kind == E_OPERATION) {
        switch (expr->attr.op.operator) {
            case PLUS: // +
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(ADI,0),NULL));
                break;
            case SUB:// -
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(SBI,0),NULL));
                break;
            case MUL: // *              
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(MPI,0),NULL));
                break;
            case DIV:// /
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(MPI,0),NULL));
                break;
            case MOD: // %
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(MODULE,0),NULL));
                break;
            case IGU: // ==
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(EQUc,0),NULL));
                break;
            case DIF: // !=
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(NEQc,0),NULL));
                break;
            case LES: // <
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(LESc,0),NULL));
                break;
            case LOQ: // <=
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(LEQc,0),NULL));
                break;
            case GRE: // >
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(GETc,0),NULL));
                break;
            case GOQ: // >=
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(GEQc,0),NULL));
                break;
            case OR: // ||
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(IOR,0),NULL));
                break;
            case AND: // &&
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(AND,0),NULL));
                break;
            case NOTOP: // !
                l1 = compileExpression(expr->attr.op.left);
                l1 = append(l1, mkList(mkInstr(NOT,0),NULL));
                break;
            default:
                printf("Undefined operation\n");
        }
    }

    return l1;
}

Instr_List* compileDeclaration(char* name) {
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    l1 = mkList(mkInstr2(LDA, name),NULL);

    return NULL;
}

Instr_List* compileAssignment(char* name, Expr* expression) {    
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    l1 = mkList(mkInstr2(LDA, name),NULL);
    l1 = append(l1, compileExpression(expression));
    l1 = append(l1, mkList(mkInstr(STO, 0),NULL));

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

    if(assignmentList != NULL) {
        l1 = compileAssignment(assignmentList->name, assignmentList->expression);
    }
    assignmentList = assignmentList->next;
    while(assignmentList != NULL) {
        l1 = append(l1,compileAssignment(assignmentList->name, assignmentList->expression));
        assignmentList = assignmentList->next;
    }

    return l1;
}

Instr_List* compileDeclarationList(DeclarationList* decl_list) {
    DeclarationList* declList = decl_list;

    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    switch(declList->type) {
            case E_ASSIGNMENT:
                l1 = compileAssignment(declList->name, declList->asg.expression);
                break;
            case E_DECLARATION:
                l1 = compileDeclaration(declList->name);
                break;
    }

    declList = declList->next;

    while(declList != NULL) {
        switch(declList->type) {
            case E_ASSIGNMENT:
                l1 = append(l1,compileAssignment(declList->name, declList->asg.expression));
                break;
            case E_DECLARATION:
                l1 = append(l1,compileDeclaration(declList->name));
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

    printfString[printCounts] = printf_expr->string_of_types->types;

    char *name = (char *)malloc(sizeof(char)*6);
    strcpy(name, "str");
    sprintf(name+3, "%d\0", printCounts+1);

    l1 = mkList(mkInstr2(WRI, name), NULL);
    
    PrintVarsList* listPrint = printf_expr->vars;

    while(listPrint != NULL) {
        variablesPrint[printCounts][variablesPerPrint] = listPrint->name;
        strcpy(name, listPrint->name);
        l1 = append(l1, mkList(mkInstr2(WRI, name), NULL));
        listPrint = listPrint->next;
        variablesPerPrint++;
    }

    printCounts++;
    variablesPerPrint = 0;

    return l1;
}

Instr_List* compileScanf(SCANF_EXP* scanf_expr){
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    ScanDeclarationList *scanList = scanf_expr->vars;

    if(scanList != NULL)
        l1 = mkList(mkInstr2(SCANF, scanList->declaration), NULL);

    scanList = scanList->next;

    while(scanList != NULL){
        l1 = append(l1, mkList(mkInstr2(SCANF, scanList->declaration), NULL));
        scanList = scanList->next;
    }

    return l1;
}

Instr_List* compileCmd(Command* cmd) {
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    if(cmd == NULL) {
        printf("compiling null\n");
        return NULL;
    }

    switch(cmd->kind) {
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
    FILE *f = fopen("MIPS.asm", "w");
    yyparse();

    LABEL_COUNT = 0;
    printCounts = 0;
    variablesPerPrint = 0;

    printfString = (char**) malloc(MAXPRINTS * MAXPRINTS * sizeof(char));
    variablesPrint = (char***) malloc(MAXPRINTS * sizeof(char**));

    for(int i = 0; i < MAXPRINTS; i++) variablesPrint[i] = (char**) malloc(MAXPRINTS * MAXPRINTS * sizeof(char));

    Instr_List* l = compile(root);
    printListIntrs(l);
    
    mipsLabel = 0;
    MipsInstr_list* ml = compileInstrList(l);

    printfData(f);

    printMipsInstrList(ml,f);

    fclose(f);

    return 0;
}
