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
            printf("here3\n");
            l1 = compileSCANF(instr->arg.name);
            break;
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
            fprintf(file,"%s $%s, $%s, $%s\n", instr->Op, instr->vars.addrs[0], instr->vars.addrs[1], instr->vars.addrs[2]);
            break;
        case E_I:
            if(!strcmp(instr->Op, "la"))
                fprintf(file,"%s $%s, %s\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1]);
            else if(!strcmp(instr->Op, "li"))
                fprintf(file,"%s $%s, %d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.val);
            else if(!strcmp(instr->Op, "sw") || !strcmp(instr->Op, "lw"))
                fprintf(file,"%s $%s, %d($%s)\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.val, instr->vars.IntInstr.addrs[1]);
            else if(!strcmp(instr->Op, "beq"))
                fprintf(file,"%s $%s, $%s, L%d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1], instr->vars.IntInstr.val);
            else
                fprintf(file,"%s $%s, $%s, %d\n", instr->Op, instr->vars.IntInstr.addrs[0], instr->vars.IntInstr.addrs[1], instr->vars.IntInstr.val);
            break;
        case E_J:
            if(!strcmp(instr->Op, "L"))
                fprintf(file,"L%d:\n", instr->vars.label);
            else
                fprintf(file,"%s L%d\n", instr->Op, instr->vars.label);
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
        fprintf(file,"%s: .word\n", vars->item->key);
        vars = vars->next;
    }

    for(int i = 0; i < printCounts; i++) {
        fprintf(file,"str%d: .asciiz %s\n", i+1, printfString[i]);
    }

    fprintf(file,"\n\n"); 

    fprintf(file, ".text\n");
}
