%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

"true" {
	yylval.intValue = 1;
	return BOOL;
}

"false" {
	yylval.intValue = 0;
	return BOOL;
}

"+"  { return PLUS; }
"-"  { return SUB;  }
"*"  { return MUL;  }
"/"  { return DIV;  }
"%"  { return MOD;  }
"||" { return OR;   }
"&&" { return AND;  }
"!"  { return NOT;  }
"==" { return EQU;  }
"!=" { return DIF;  }
"<"  { return LES;	}
"<=" { return LOQ;	}
">"  { return GRE;  }
">=" { return GOQ;  }

.  { yyerror("unexpected character"); }
%%
