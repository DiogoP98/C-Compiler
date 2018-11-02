#include <stdio.h>
#include "parser.h"

void printExpr(Expr* expr, int spaces) {
for(int i = 0; i < spaces; i++)
    printf(" ");
  if (expr == 0) {
    yyerror("Null expression!!");
  }

  else if (expr->kind == E_INTEGER) 
    printf ("INT %d\n", expr->attr.value); 

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
        printf("%c:\n", 37);
        break;
    }
    printExpr(expr->attr.op.left, spaces+1);
    printExpr(expr->attr.op.right, spaces+1);
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
      printf("\n\n\n\n\n\n\n\n\n");
      root = root->next;
    }
  }
  return 0;
}
