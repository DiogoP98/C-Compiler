#include "MIPS.h"
#include <stdlib.h> // for malloc
#include <stdio.h>
#include "parser.h"

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

MipsInstr* mkMipsInstrE_M(char op[6], char *r1) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_M;
    strcpy(node->Op, op);
    strcpy(node->vars.addrs[0], r1);

    return node;
}

MipsInstr* mkMipsInstrE_T(char op[6], char r1[5], char r2[5]) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_T;
    strcpy(node->Op, op);
    strcpy(node->vars.IntInstr.addrs[0], r1);
    strcpy(node->vars.IntInstr.addrs[1], r2);

    return node;
}

MipsInstr* mkMipsInstrE_R(char op[6], char *r1, char *r2, char *r3) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_R;
    strcpy(node->Op, op);
    strcpy(node->vars.addrs[0], r1);
    strcpy(node->vars.addrs[1], r2);
    strcpy(node->vars.addrs[2], r3);

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

MipsInstr* mkMipsInstrE_BEQZ(char op[6], char r1[3], char r2[3]) {
    MipsInstr* node = (MipsInstr*) malloc(sizeof(MipsInstr));

    node->kind = E_BEQZ;
    strcpy(node->Op, op);
    strcpy(node->vars.IntInstr.addrs[0], r1);
    strcpy(node->vars.IntInstr.addrs[1], r2);

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

    l1 = mkMipsList(mkMipsInstrE_I("li", "a0", "", vali), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 0), NULL));
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

    return l1;
}

MipsInstr_list* compileLDCFloat(float valf){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_FI("l.s", "f0", "", valf), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_FI("s.s", "f0", "sp", 0), NULL));
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

    return l1;
}

MipsInstr_list* compileADI(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("add", "a0", "t0", "a0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

    return l1;
}

MipsInstr_list* compileSBI(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sub", "a0", "t0", "a0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

    return l1;
}

MipsInstr_list* compileMPI(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("mul", "a0", "t0", "a0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

    return l1;
}

MipsInstr_list* compileDVI() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("div", "a0", "t0", "a0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

    return l1;
}

MipsInstr_list* compileMOD() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("div", "a0", "t0", "a0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_M("mfhi", "a0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

    return l1;
}

MipsInstr_list* compileEQUc() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("seq", "a0", "a0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

    return l1;
}

MipsInstr_list* compileNEQc() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sne", "a0", "a0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));
    
    return l1;
}

MipsInstr_list* compileLESc() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("slt", "a0", "a0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));
    
    return l1;
}

MipsInstr_list* compileLEQc() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sle", "a0", "a0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));
    
    return l1;
}

MipsInstr_list* compileGETc() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sgt", "a0", "a0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));
    
    return l1;
}

MipsInstr_list* compileGEQc() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    l1 = mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sge", "a0", "a0", "t1"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));
    
    return l1;
}

MipsInstr_list* compileBEQZ(int label) {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    char* str1 = "L";
    char* str2 = (char*) malloc(10 * sizeof(char));

    sprintf(str2, "%d", label);

    char* str3 = (char*) malloc(1 + strlen(str1) + strlen(str2));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 0), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_BEQZ("beqz", "t0", str3), NULL));
    
    return l1;
}

MipsInstr_list* compileIOR(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sne", "t0", "t0", "zero"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sne", "a0", "a0", "zero"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("or", "a0", "a0", "t0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

    return l1;
}

MipsInstr_list* compileAND() {
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sne", "t0", "t0", "zero"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("sne", "a0", "a0", "zero"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_R("and", "a0", "a0", "t0"), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 4), NULL));

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

MipsInstr_list* compileLOD(char *name){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));
     
    l1 = mkMipsList(mkMipsInstrE_T("la", "t0", name), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t1", "t0", 0), NULL));
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

    return l1;
}

MipsInstr_list* compileLDA(char *name){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(mkMipsInstrE_T("la", "a0", name), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "sp", 0), NULL));
    l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(-4), NULL));

    return l1;
}

MipsInstr_list* compileSTO(){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    l1 = mkMipsList(compileAlocateStack(4), NULL);
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("lw", "t0", "sp", 4), NULL));
    l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("sw", "a0", "t0", 0), NULL));

    return l1;
}

MipsInstr_list* compileUJP(int label){
    return mkMipsList(mkMipsInstrE_J("j", label), NULL);
}

MipsInstr_list* compileLABEL(int label){
    return mkMipsList(mkMipsInstrE_J("L", label), NULL);
}

MipsInstr_list* compileWRI(char *name){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    if(checkExistence(name, SYMBOL_LIST) == 0){
        l1 = mkMipsList(mkMipsInstrE_T("lw", "a0", name), NULL);
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "v0", "", 2), NULL));
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_SYSCALL(), NULL));

        l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    }
    else if(checkExistence(name, SYMBOL_LIST) == 1){
        l1 = mkMipsList(mkMipsInstrE_T("lw", "a0", name), NULL);
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "v0", "", 1), NULL));

        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_SYSCALL(), NULL));

        l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    }
    else {
        l1 = mkMipsList(mkMipsInstrE_T("la", "a0", name), NULL);
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_I("li", "v0", "", 4), NULL));
        l1 = appendMipsList(l1, mkMipsList(mkMipsInstrE_SYSCALL(), NULL));

        l1 = appendMipsList(l1, mkMipsList(compileAlocateStack(4), NULL));
    }

    return l1;
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

    //l1 = appendMipsList(l1, compileLDA(name));
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
                default:
                    l1 = NULL;
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
        case DIVOP:
            l1 = compileDVI();
            break;
        case MODULE: // %
            l1 = compileMOD();
            break;
        case EQUJ: // ==
            l1 = compileEQUc();
            break;
        case NEQc: // !=
            l1 = compileNEQc();
            break;
        case LESc: // <
            l1 = compileLESc();    
            break;
        case LEQc: // <=
            l1 = compileLEQc();
            break;
        case GETc: // >
            l1 = compileGETc();
            break;
        case GEQc: // >=
            l1 = compileGEQc();
            break;
        case BEQZ:
            l1 = compileBEQZ(instr->arg.argi);
        case IOR: // ||
            l1 = compileIOR();
            break;
        case ANDOP: // &&
            l1 = compileAND();
            break;
        case NOT: // !
            l1 = compileNOT();
            break;
        case LOD:
            l1 = compileLOD(instr->arg.name);
            break;
        case STO:
            l1 = compileSTO();
            break;
        case UJP:
            l1 = compileUJP(instr->arg.argi);
            break;
        case LABEL:
            l1 = compileLABEL(instr->arg.argi);
            break;
        case LDA:
            l1 = compileLDA(instr->arg.name);
            break;
        case WRI:
            l1 = compileWRI(instr->arg.name);
            break;
        case SCANF:
            l1 = compileSCANF(instr->arg.name);
            break;
        default:
            l1 = NULL;
    }

    return l1;
}


MipsInstr_list* compileInstrList(Instr_List* instrList){
    MipsInstr_list* l1 = (MipsInstr_list*)malloc(sizeof(MipsInstr_list));

    if(head(instrList) == NULL) {
        return l1 = NULL;
    }

    l1 = compilePCode(instrList->instruction);

    while(instrList->next != NULL) { 
        instrList = instrList->next;
        l1 = appendMipsList(l1, compilePCode(instrList->instruction));
    }

    return l1;
}

void printMipsInstr(MipsInstr* instr, FILE* file) {
    if (instr == NULL) {
        yyerror("Null mips instruction!!");
        return;
    }

    switch(instr->kind){
        case E_R:
            if(instr->Op[0] == 's')
                fprintf(file,"%s $%s, $%s, %s\n", instr->Op, instr->vars.addrs[0], instr->vars.addrs[1], instr->vars.addrs[2]);
            else
                fprintf(file,"%s $%s, $%s, $%s\n", instr->Op, instr->vars.addrs[0], instr->vars.addrs[1], instr->vars.addrs[2]);
            break;
        case E_I:
            if (!strcmp(instr->Op, "li"))
                fprintf(file,"%s $%s, %d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.val);
            else if(!strcmp(instr->Op, "sw") || !strcmp(instr->Op, "lw"))
                fprintf(file,"%s $%s, %d($%s)\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.val, instr->vars.IntInstr.addrs[1]);
            else if(!strcmp(instr->Op, "beq"))
                fprintf(file,"%s $%s, $%s, L%d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1], instr->vars.IntInstr.val);
            else
                fprintf(file,"%s $%s, $%s, %d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1], instr->vars.IntInstr.val);
            break;
        case E_T:
            fprintf(file,"%s $%s, %s\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1]);
            break;
        case E_J:
            if(!strcmp(instr->Op, "L"))
                fprintf(file,"L%d:\n", instr->vars.label);
            else
                fprintf(file,"%s L%d\n", instr->Op, instr->vars.label);
            break;
        case E_BEQZ:
            fprintf(file,"%s $%s, $%s\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[0]);
            break;
        case E_FR:
            fprintf(file,"%s $%s, $%s, $%s\n", instr->Op, instr->vars.addrs[0], instr->vars.addrs[1], instr->vars.addrs[2]);
            break;
        case E_FI:
            fprintf(file,"%s $%s, $%s, %f\n", instr->Op, instr->vars.FloatInstr.addrs[0], instr->vars.FloatInstr.addrs[1], instr->vars.FloatInstr.val);
            break;
        case E_SYSCALL:
            fprintf(file,"syscall\n");
            break;
        default:
            fprintf(file,"Undefined mips instruction kind %d\n", instr->kind);
    }
}

void printMipsInstrList(MipsInstr_list* list, FILE* file){
    if(headMipsList(list) == NULL)
        return;

    printMipsInstr(headMipsList(list), file);
    
    if(tailMipsList(list) != NULL)
        printMipsInstrList(tailMipsList(list), file);
}

void printfData(FILE* file){
    fprintf(file,".data\n");
    ItemsList* vars = SYMBOL_LIST;
    
    while(vars != NULL) {
        fprintf(file,"%s: .word 0\n", vars->item->key);
        vars = vars->next;
    }

    for(int i = 0; i < printCounts; i++) {
        fprintf(file,"str%d: .asciiz %s\n", i+1, printfString[i]);
    }

    fprintf(file, "newline: .asciiz \"\\n\" \n");

    fprintf(file,"\n\n"); 

    fprintf(file, ".text\n");
}
