#ifndef __mips_h__
#define __mips_h__

#include "ast.h"
#include "symbol_table.h"
#include "stack.h"

struct _MipsInstr {
    enum {
        E_R,
        E_I,
        E_J,
        E_FR,
        E_FI,
        E_SYSCALL
    } kind;
    
    char Op[12];

    union {
        char addrs[3][3];
        
        struct {
            char addrs[2][50];
            int val;
        } IntInstr;
        
        int label;

        struct {
            char addrs[2][50];
            float val;
        } FloatInstr;
    } vars;
};

struct _MipsInstr_list {
    struct _MipsInstr* instruction;
    struct _MipsInstr_list* next;
};

typedef struct _MipsInstr MipsInstr;
typedef struct _MipsInstr_list MipsInstr_list;

MipsInstr* headMipsList(MipsInstr_list* l);
MipsInstr_list* tailMipsList(MipsInstr_list* l);
MipsInstr_list* mkMipsList(MipsInstr* code, MipsInstr_list* l);
MipsInstr_list* appendMipsList(MipsInstr_list* l1, MipsInstr_list* l2);
MipsInstr* mkMipsInstrE_R(char op[6], char r1[3], char r2[3], char r3[3]);
MipsInstr* mkMipsInstrE_I(char op[6], char r1[3], char r2[3], int val);
MipsInstr* mkMipsInstrE_J(char op[6], int label);
MipsInstr* mkMipsInstrE_FR(char op[6], char r1[3], char r2[3], char r3[3]);
MipsInstr* mkMipsInstrE_FI(char op[6], char r1[3], char r2[3], float val);
MipsInstr* mkMipsInstrE_SYSCALL();
MipsInstr* compileAlocateStack(int space);
MipsInstr_list* compileLDCInt(int vali);
MipsInstr_list* compileLDCFloat(float valf);
MipsInstr_list* compileADI();
MipsInstr_list* compileSBI();
MipsInstr_list* compileMPI();
MipsInstr_list* compileDVI();
MipsInstr_list* compileMOD();
MipsInstr_list* compileEQUc();
MipsInstr_list* compileNEQc();
MipsInstr_list* compileLESc();
MipsInstr_list* compileLEQc();
MipsInstr_list* compileGETc();
MipsInstr_list* compileGEQc();
MipsInstr_list* compileIOR();
MipsInstr_list* compileAND();
MipsInstr_list* compileNOT();
MipsInstr_list* compileLOD(char *name);
MipsInstr_list* compileSTO();
MipsInstr_list* compileFJP(int label);
MipsInstr_list* compileUJP(int label);
MipsInstr_list* compileLABEL(int label);
MipsInstr_list* compileLDA(char *name);
MipsInstr_list* compileWRI(char *name); //ESTE TAMBEM
MipsInstr_list* compileSCANF(char *name);
MipsInstr_list* compilePCode(Instr* instr);
MipsInstr_list* compileInstrList(Instr_List* instrList);
void printMipsInstr(MipsInstr* instr, FILE* file);
void printMipsInstrList(MipsInstr_list* list, FILE* file);
void printfData(FILE* file);

#endif
