#include <stdlib.h> // for malloc
#include "stack.h"
#include <stdio.h>
#include "parser.h"
#include <limits.h>


int mipsLabel;


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
            case PLUS:
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(ADI,0),NULL));
                break;
            case SUB:
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(SBI,0),NULL));
                break;
            case MUL:                
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(MPI,0),NULL));
                break;
            case DIV:
                l1 = append(compileExpression(expr->attr.op.left), compileExpression(expr->attr.op.right));
                l1 = append(l1, mkList(mkInstr(MPI,0),NULL));
                break;
            case MOD:
                printf("%%:\n");
                break;
            case IGU:
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

    return l1;
}

Instr_List* compileDeclaration(char* name) {
    Instr_List* l1 = (Instr_List*)malloc(sizeof(Instr_List));

    l1 = mkList(mkInstr2(LDA, name),NULL);

    return l1;
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
            /*case E_DECLARATION:
                l1 = compileDeclaration(declList->name);
                break;*/
    }

    declList = declList->next;

    while(declList != NULL) {
        switch(declList->type) {
            case E_ASSIGNMENT:
                l1 = append(l1,compileAssignment(declList->name, declList->asg.expression));
                break;
            /*case E_DECLARATION:
                l1 = append(l1,compileDeclaration(declList->name));
                break;*/
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

    l1 = mkList(mkInstr2(WRI, printf_expr->string_of_types->types), NULL);

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



MipsInstr* headMipsList(MipsInstr_list* l) {
    return l->instruction;
}

MipsInstr_list* tailMipsList(MipsInstr_list* l) {
    return l->next;
}

MipsInstr_list* mkMipsList(MipsInstr* code, MipsInstr_list* l) {
    MipsInstr_list* node = (MipsInstr_list*) malloc(sizeof(MipsInstr_list));
    node->instruction = code;
    node->next = l;
    return node;
}

MipsInstr_list* appendMipsList(MipsInstr_list* l1, MipsInstr_list* l2) {
    if(l1 == NULL)
        return l2;
    
    return mkMipsList(headMipsList(l1), appendMipsList(tailMipsList(l1),l2));
}

MipsInstr* mkMipsInstrE_R(char op[6], char r1[3], char r2[3], char r3[3]) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_R;
    strcpy(node->Op, op);
    strcpy(node->vars.IntInstr.addrs[0], r1);
    strcpy(node->vars.IntInstr.addrs[1], r2);
    strcpy(node->vars.IntInstr.addrs[2], r3);

    return node;
}

MipsInstr* mkMipsInstrE_I(char op[6], char r1[3], char r2[3], int val) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_I;
    strcpy(node->Op, op);
    strcpy(node->vars.IntInstr.addrs[0], r1);
    strcpy(node->vars.IntInstr.addrs[1], r2);
    node->vars.IntInstr.val = val;

    return node;
}

MipsInstr* mkMipsInstrE_J(char op[6], int label) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_J;
    strcpy(node->Op, op);
    node->vars.label = label;

    return node;
}

MipsInstr* mkMipsInstrE_FR(char op[6], char r1[3], char r2[3], char r3[3]) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_FR;
    strcpy(node->Op, op);
    strcpy(node->vars.FloatInstr.addrs[0], r1);
    strcpy(node->vars.FloatInstr.addrs[1], r2);
    strcpy(node->vars.FloatInstr.addrs[2], r3);

    return node;
}

MipsInstr* mkMipsInstrE_FI(char op[6], char r1[3], char r2[3], float val) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_FI;
    strcpy(node->Op, op);
    strcpy(node->vars.FloatInstr.addrs[0], r1);
    strcpy(node->vars.FloatInstr.addrs[1], r2);
    node->vars.FloatInstr.val = val;

    return node;
}

MipsInstr* mkMipsInstrE_SYSCALL() {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_SYSCALL;
    strcpy(node->Op, "syscall");

    return node;
}

MipsInstr* compileAlocateStack(int space){
    return mkMipsInstrE_I("addi", "sp", "sp", space);
}

MipsInstr_list* compileLDCInt(int vali){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(-4), NULL);

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "t0", "", vali), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t0", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileLDCFloat(float valf){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(-4), NULL);

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_FI("l.s", "f0", "", valf), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_FI("s.s", "f0", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileADI(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "sp", 4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("add", "t2", "t0", "t1"), NULL));

    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t2", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileSBI(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "sp", 4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sub", "t2", "t0", "t1"), NULL));

    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t2", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileMPI(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "sp", 4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("mul", "t2", "t0", "t1"), NULL));

    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t2", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileLOD(char *name){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("la", "t0", name, 0), NULL);
    l1 = mkMipsList(mkMipsInstrE_I("lw", "t1", "t0", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t1", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileSTO(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t0", "t1", 0), NULL));
    
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(8), NULL));

    return l1;
}

MipsInstr_list* compileFJP(int label){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "t1", "", 0), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("beq", "t0", "t1", label), NULL));

    return l1;
}

MipsInstr_list* compileGRT(){

}

MipsInstr_list* compileUJP(int label){
    return mkMipsList(mkMipsInstrE_J("j", label), NULL);
}

MipsInstr_list* compileLABEL(int label){
    return mkMipsList(mkMipsInstrE_J("L", label), NULL);
}

MipsInstr_list* compileEQU(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "sp", 4), NULL));

    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("addu", "t2", "t0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("addui", "t2", "t2", 1), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t2", "sp", 0), NULL));

    return l1;
}


MipsInstr_list* compileNEQ(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "sp", 4), NULL));

    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("addu", "t2", "t0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("addui", "t2", "t2", 1), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t2", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileLDA(char *name){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("la", "t0", name, 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t0", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileIOR(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "sp", 4), NULL));

    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("xor", "t2", "t0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t2", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileNOT(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "t1", "", 0), NULL));
    
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("nor", "t2", "t0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "t2", "sp", 0), NULL));

    return l1;
}

MipsInstr_list* compileWRI(char *name){

}

MipsInstr_list* compileSCANF(char *name){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = compileLDA(name);

    if(checkExistence(name, SYMBOL_LIST) == 0){
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "v0", "", 6), NULL));
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_SYSCALL(), NULL));

        l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "f0", "sp", 0), NULL));
    }
    else if(checkExistence(name, SYMBOL_LIST) == 1){
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "v0", "", 5), NULL));
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_SYSCALL(), NULL));

        l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "v0", "sp", 0), NULL));
    }

    l1 = appendMipsList(l1, compileLDA(name));
    l1 = appendMipsList(l1, compileSTO());
    
    return l1;
}


MipsInstr_list* compilePCode(Instr* instr){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    if(instr == NULL) {
        printf("compiling null p-code instruction\n");
        return NULL;
    }

    switch(instr->kind) {
        case LDC:
            switch(instr->type) {
                case E_INT2:
                    l1 = compileLDCInt(instr->arg.argi);
                    break;
                case E_FLOAT2:
                    l1 = compileLDCFloat(instr->arg.argf);
                    break;
            }
            break;
        case ADI:
            l1 = compileADI();
            break;
        case SBI:
            l1 = compileSBI();
            break;
        case MPI:
            l1 = compileMPI();
            break;
        case LOD:
            l1 = compileLOD(instr->arg.name);
            break;
        case STO:
            l1 = compileSTO();
            break;
        case FJP:
            l1 = compileFJP(instr->arg.argi);
            break;
        case GRT:
            l1 = compileGRT();
            break;
        case UJP:
            l1 = compileUJP(instr->arg.argi);
            break;
        case LABEL:
            l1 = compileLABEL(instr->arg.argi);
            break;
        case EQU:
            l1 = compileEQU();
            break;
        case NEQ:
            l1 = compileNEQ();
            break;
        case LDA:
            l1 = compileLDA(instr->arg.name);
            break;
        case IOR:
            l1 = compileIOR();
            break;
        case NOT:
            l1 = compileNOT();
            break;
        case WRI:
            l1 = compileWRI(instr->arg.name);
            break;
        case SCANF:
            l1 = compileSCANF(instr->arg.name);
            break;
    }

    return l1;
}


MipsInstr_list* compileInstrList(Instr_List* instrList){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    if(instrList->instruction == NULL) 
        return NULL;

    l1 = compilePCode(instrList->instruction);

    while(instrList->next != NULL) { 
        instrList = instrList->next;
        l1 = appendMipsList(l1, compilePCode(instrList->instruction));
    }

    return l1;
}

void printMipsInstr(MipsInstr* instr) {
    if (instr == NULL) {
        yyerror("Null mips instruction!!");
        return;
    }

    switch(instr->kind){
        case E_R:
            printf("%s $%s, $%s, $%s\n", instr->Op, instr->vars.addrs[0], instr->vars.addrs[1], instr->vars.addrs[2]);
            break;
        case E_I:
            if(!strcmp(instr->Op, "la"))
                printf("%s $%s, %s\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1]);
            else if(!strcmp(instr->Op, "li"))
                printf("%s $%s, %d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.val);
            else if(!strcmp(instr->Op, "sw") || !strcmp(instr->Op, "lw"))
                printf("%s $%s, %d($%s)\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.val, instr->vars.IntInstr.addrs[1]);
            else if(!strcmp(instr->Op, "beq"))
                printf("%s $%s, $%s, L%d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1], instr->vars.IntInstr.val);
            else
                printf("%s $%s, $%s, %d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1], instr->vars.IntInstr.val);
            break;
        case E_J:
            if(!strcmp(instr->Op, "L"))
                printf("L%d:\n", instr->vars.label);
            else
                printf("%s L%d\n", instr->Op, instr->vars.label);
            break;
        case E_FR:
            printf("%s $%s, $%s, $%s\n", instr->Op, instr->vars.addrs[0], instr->vars.addrs[1], instr->vars.addrs[2]);
            break;
        case E_FI:
            printf("%s $%s, $%s, %f\n", instr->Op, instr->vars.FloatInstr.addrs[0], instr->vars.FloatInstr.addrs[1], instr->vars.FloatInstr.val);
            break;
        case E_SYSCALL:
            printf("syscall\n");
            break;
        default:
            printf("Undefined mips instruction kind %d\n", instr->kind);
    }
}

void printMipsInstrList(MipsInstr_list* list){
    if(headMipsList(list) == NULL)
        return;

    printMipsInstr(headMipsList(list));
    
    if(tailMipsList(list) != NULL)
        printMipsInstrList(tailMipsList(list));
}


int main(int argc, char** argv) {
    yyparse();

    LABEL_COUNT = 0;
    Instr_List* l = compile(root);
    //printListIntrs(l);
    
    mipsLabel = 0;
    MipsInstr_list* ml = compileInstrList(l);
    printMipsInstrList(ml);

    return 0;
}
