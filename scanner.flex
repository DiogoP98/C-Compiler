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

[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) {
	yylval.floatValue = atof(yytext);
	return FLOAT;
}

"int main() {" { return STARTOFPROGRAM; }

"if" { return IF; }

"else" { return ELSE; }

"int" { return INTD; }

"float" { return FLOATD; }

"printf" { return PRINT; }

"scanf" { return SCAN; }

"while" { return WHILE; }

";" { return SEMICOLON; }

"=" { return EQUAL; }

"(" { return OPENPARENTHESIS; }

")" { return CLOSEPARENTHESIS; }

"{" { return OPENCURLYBRACKETS; }

"}" { return CLOSECURLYBRACKETS; }

"[" { return OPENSQUAREBRACKETS; }

"]" { return CLOSESQUAREBRACKETS; }

"," { return COMMA; }

" " { return SPACE; }


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

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.stringValue = yytext;
    return VAR;
}

.  { yyerror("unexpected character"); }
%%
