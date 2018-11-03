#include <stdio.h>
#include "parser.h"

void printExpr(Expr* expr, int spaces);
void printBoolExpr(BoolExpr* expr, int spaces);
void printDeclaration(DECL* decl, int spaces);
void printAssignment(ASG* asg, int spaces);
void printDeclarationList(DeclarationList* declList, int spaces);
void printCommand(Command* cmd, int spaces);
void printIf(IFexpression* ifExpr, int spaces);
void printWhile(WHILEexpression* whileExpr, int spaces);

void printExpr(Expr* expr, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (expr == NULL)
    yyerror("Null expression!!");
  
  else if (expr->kind == E_INTEGER)
    printf("INT %d\n", expr->attr.valuei);
  
  else if (expr->kind == E_INTEGER)
    printf("FLOAT %f\n", expr->attr.valuef);

  else if (expr->kind == E_OPERATION) {
    switch (expr->attr.op.operator) {
      case PLUS:
        printf("+:\n");
        break;
      case SUB:
        printf("-:\n");
        break;
      case MUL:
        printf("*:\n");
        break;
      case DIV:
        printf("/:\n");
        break;
      case MOD:
        printf("%%:\n");
        break;
    }
    printExpr(expr->attr.op.left, spaces+1);
    printExpr(expr->attr.op.right, spaces+1);
  }
}

void printBoolExpr(BoolExpr* expr, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (expr == NULL)
    yyerror("Null bool expression!!");
  
  else if (expr->kind == E_BOOL)
    printf("BOOL %d\n", expr->attr_bool.value);

  else if (expr->kind == E_RELOP) {
    switch (expr->attr_bool.relop.operator) {
      case OR:
        printf("||:\n");
        break;
      case AND:
        printf("&&:\n");
        break;
      case NOT:
        printf("!:\n");
        break;
      case EQU:
        printf("==:\n");
        break;
      case DIF:
        printf("!=:\n", 37);
        break;
      case LES:
        printf("<:\n", 37);
        break;
      case LOQ:
        printf("<=:\n", 37);
        break;
      case GRE:
        printf(">:\n", 37);
        break;
      case GOQ:
        printf(">=:\n", 37);
        break;
      default:
        printf("Undefined\n");
    }
    printBoolExpr(expr->attr_bool.relop.bleft, spaces+1);
    printBoolExpr(expr->attr_bool.relop.bright, spaces+1);
  }
}

void printDeclaration(DECL* decl, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (decl == NULL)
    yyerror("Null declaration!!");
  
  else if (decl->type == E_SINGLE)
    printf("SINGLE %s\n", decl->name);
}

void printAssignment(ASG* asg, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (asg == NULL)
    yyerror("Null assignment!!");
  
  else if (asg->type == E_SINGLE_ASG)
    printf("SINGLE %s = \n", asg->name);

  printExpr(asg->value, spaces + 1);
}

void printCommand(Command* cmd, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (cmd == NULL)
    yyerror("Null command!!");
  
  else {
    switch (cmd->kind) {
      case E_IF:
        printIf(cmd->ifnext, spaces+1);
        break;
      case E_WHILE:
        printWhile(cmd->whilenext, spaces+1);
        break;
      case E_ASG:
        printDeclarationList(cmd->declnext, spaces+1);
        break;
      case E_DECL:
        printDeclarationList(cmd->declnext, spaces+1);
        break;
      case E_PRINT:
        //printPrintf("!=:\n", 37);
        break;
      case E_SCAN:
        //printfScanf("<:\n", 37);
        break;
      default:
        printf("Undefined\n");
    }
  }
}

void printDeclarationList(DeclarationList* declList, int spaces){
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (declList == NULL)
    yyerror("Null command!!");

  else{
    switch (declList->type) {
      case E_ASSIGNMENT:
        printAssignment(declList->assignment, spaces+1);
        break;
      case E_DECLARATION:
        printDeclaration(declList->declaration, spaces+1);
        break;
      default:
        printf("Undefined\n");
    }

    printDeclarationList(declList->next, spaces+1);
  }
}


void printIf(IFexpression* ifExpr, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (ifExpr == NULL)
    yyerror("Null command!!");
  
  else {
    CommandList* cmdList;
    switch (ifExpr->kind) {
      case E_IF_EXPR:
        printBoolExpr(ifExpr->if_type.bexpr, spaces+1);
        cmdList = ifExpr->if_type.list;
        while(cmdList != NULL){
          printCommand(cmdList->expr, spaces + 1);
          cmdList = cmdList->next;
        }
        break;
      case E_IF_ELSE:
        printBoolExpr(ifExpr->if_type.bexpr, spaces+1);
        cmdList = ifExpr->if_type.list;
        while(cmdList != NULL){
          printCommand(cmdList->expr, spaces + 1);
          cmdList = cmdList->next;
        }
        
        cmdList = ifExpr->if_else_type.list;
        while(cmdList != NULL){
          printCommand(cmdList->expr, spaces + 1);
          cmdList = cmdList->next;
        }
        break;
      default:
        printf("Undefined\n");
    }
  }
}

void printWhile(WHILEexpression* whileExpr, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (whileExpr == NULL)
    yyerror("Null command!!");

  printBoolExpr(whileExpr->bexpr, spaces + 1);

  CommandList* cmdList = whileExpr->list;
  while(cmdList != NULL){
    printCommand(cmdList->expr, spaces + 1);
    cmdList = cmdList->next;
  }
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
    while(root != NULL) {
      printCommand(root->expr, 0);

      root = root->next;
    }
  }
  return 0;
}
