#include <stdio.h>
#include "parser.h"

void printExpr(Expr* expr, int spaces);
void printNumber(NUMBER* n, int spaces);
void printBoolExpr(BoolExpr* expr, int spaces);
void printDeclaration(DECL* decl, int spaces);
void printAssignment(ASG* asg, int spaces);
void printvarList (varList* list, int spaces);
void printDeclarationList(DeclarationList* declList, int spaces);
void printCommand(Command* cmd, int spaces);
void printIf(IFexpression* ifExpr, int spaces);
void printWhile(WHILEexpression* whileExpr, int spaces);
void printPrintf(PRINTF_EXP* printf, int spaces);
void printScanf(SCANF_EXP* scanf, int spaces);
void printStrOfTypes(TYPES_STR* str, int spaces);
void printScanDeclarationList(ScanDeclarationList* list, int spaces);
void printAssignmentList(AsgList* asg_list, int spaces);

void printExpr(Expr* expr, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (expr == NULL){
    yyerror("Null expression!!");
    return;
  }
  
  else if (expr->kind == E_NUM)
    printNumber(expr->attr.number, spaces+1);

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

void printNumber(NUMBER* n, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (n == NULL){
    yyerror("Null number!!");
    return;
  }

  if(n->type == E_INTEGER)
    printf ("%d\n", n->valuei);
  
  else 
    printf("%f\n", n->valuef);
}

void printBoolExpr(BoolExpr* expr, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (expr == NULL){
    yyerror("Null bool expression!!");
    return;
  }
  
  else if (expr->kind == E_BOOL)
    printNumber(expr->attr_bool.value, spaces+1);

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
      default:
        printf("Undefined\n");
    }
    if(expr->attr_bool.relop.bleft != NULL)
      printBoolExpr(expr->attr_bool.relop.bleft, spaces+1);
    if(expr->attr_bool.relop.bright != NULL)
      printBoolExpr(expr->attr_bool.relop.bright, spaces+1);
    if(expr->attr_bool.relop.left != NULL)
      printExpr(expr->attr_bool.relop.left, spaces+1);
    if(expr->attr_bool.relop.right != NULL)
      printExpr(expr->attr_bool.relop.right, spaces+1);
  }
}

void printDeclaration(DECL* decl, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (decl == NULL){
    yyerror("Null declaration!!");
    return;
  }
  
  printf("%s\n", decl->name);
}

void printAssignmentList(AsgList* asg_list, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (asg_list == NULL){
    yyerror("Null var list!!");
    return;
  }
  printAssignment(asg_list->assignment, spaces+1);
  AsgList* asg_list_copy = asg_list;
  if(asg_list_copy->next != NULL) {
    asg_list_copy = asg_list_copy->next;
    printAssignmentList(asg_list_copy, spaces);
  }
}

void printAssignment(ASG* asg, int spaces) {
  if (asg == NULL){
    yyerror("Null assignment!!");
    return;
  }

  printDeclaration(asg->name, spaces);
  for(int i = 0; i < spaces+2; i++)
    printf(" ");

  printf("=:\n");
  printExpr(asg->value, spaces+2);
}

void printCommand(Command* cmd, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (cmd == NULL) {
    yyerror("Null command!!");
    return;
  }
  
  else {
    switch (cmd->kind) {
      case E_IF:
        printIf(cmd->ifnext, spaces+1);
        break;
      case E_WHILE:
        printWhile(cmd->whilenext, spaces+1);
        break;
      case E_VAR:
        printvarList(cmd->list, spaces+1);
        break;
      case E_ASG:
        printf("Assignment:\n");
        printAssignmentList(cmd->asg_list, spaces+1);
        break;
      case E_PRINT:
        printPrintf(cmd->printnext, spaces+1);
        break;
      case E_SCAN:
        printScanf(cmd->scannext, spaces+1);
        break;
      default:
        printf("Undefined\n");
    }
  }
}

void printvarList (varList* list, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (list == NULL){
    yyerror("Null var list!!");
    return;
  }

  if(list->type == FLOATD)
    printf("FLOAT:\n");
  else
    printf("INT:\n");

  printDeclarationList(list->list, spaces + 1);
}

void printDeclarationList(DeclarationList* declList, int spaces){
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (declList == NULL){
    yyerror("Null declaration list!!");
    return;
  }

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

  DeclarationList* declList_copy = declList;
  if(declList_copy->next != NULL) {
    declList_copy = declList_copy->next;
    printDeclarationList(declList_copy, spaces);
  }

}


void printIf(IFexpression* ifExpr, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (ifExpr == NULL){
    yyerror("Null if expression!!");
    return;
  }
  
  else {
    CommandList* cmdList;
    switch (ifExpr->kind) {
      case E_IF_EXPR:
        printf("IF:\n");
        printBoolExpr(ifExpr->if_type.bexpr, spaces+1);
        cmdList = ifExpr->if_type.list;
        while(cmdList != NULL){
          printCommand(cmdList->expr, spaces + 1);
          cmdList = cmdList->next;
        }
        break;
      case E_IF_ELSE:
        printf("IF:\n");
        printBoolExpr(ifExpr->if_else_type.bexpr, spaces+1);
        cmdList = ifExpr->if_else_type.list;
        while(cmdList != NULL){
          printCommand(cmdList->expr, spaces + 1);
          cmdList = cmdList->next;
        }
        for(int i = 0; i < spaces; i++)
          printf(" ");
        printf("ELSE:\n");
        cmdList = ifExpr->if_else_type.else_list;
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
  
  if (whileExpr == NULL){
    yyerror("Null while expression!!");
    return;
  }

  printf("WHILE:\n");

  printBoolExpr(whileExpr->bexpr, spaces + 1);

  CommandList* cmdList = whileExpr->list;
  while(cmdList != NULL){
    printCommand(cmdList->expr, spaces + 1);
    cmdList = cmdList->next;
  }
}

void printPrintf(PRINTF_EXP* printfExp, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");
  
  if (printfExp == NULL){
    yyerror("Null printf!!");
    return;
  }

  printf("PRINTF:\n");

  printStrOfTypes(printfExp->string_of_types, spaces+2);

  if(printfExp->vars)
    printDeclarationList(printfExp->vars, spaces+2);
}

void printScanf(SCANF_EXP* scanfExp, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (scanfExp == NULL){
    yyerror("Null scanf!!");
    return;
  }

  printf("SCANF:\n");
  printStrOfTypes(scanfExp->string_of_types, spaces+2);
  printScanDeclarationList(scanfExp->vars, spaces+2);
}

void printStrOfTypes(TYPES_STR* str, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (str == NULL){
    yyerror("Null types!!");
    return;
  }

  printf("%s\n", str->types);
}

void printScanDeclarationList(ScanDeclarationList* list, int spaces) {
  for(int i = 0; i < spaces; i++)
    printf(" ");

  if (list == NULL){
    yyerror("Null scan declaration list!!");
    return;
  }

  printDeclaration(list->declaration, spaces);
  while(list->next != NULL) {
    list = list->next;
    for(int i = 0; i < spaces; i++)
      printf(" ");
    printDeclaration(list->declaration, spaces);
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
