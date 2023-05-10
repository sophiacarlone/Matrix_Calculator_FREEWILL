%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "list.h"
#include "y.tab.h"
%}

number      [0-9]+
whitespace  [ \t]

%%

"+"             { fprintf( stderr, "[ADDOP:%c]", yylval.opval = yytext[0] ); return ADDOP; }
"-"             { fprintf( stderr, "[ADDOP:%c]", yylval.opval = yytext[0] ); return ADDOP; }
"*"             { fprintf( stderr, "[MULOP:%c]", yylval.opval = yytext[0] ); return MULOP; }
"/"             { fprintf( stderr, "[MULOP:%c]", yylval.opval = yytext[0] ); return MULOP; }
"("             { fprintf( stderr, "{%c}", yytext[0] ); return yytext[0]; }
")"             { fprintf( stderr, "{%c}", yytext[0] ); return yytext[0]; }
"["             { fprintf( stderr, "{%c}", yytext[0] ); return yytext[0]; }
"]"             { fprintf( stderr, "{%c}", yytext[0] ); return yytext[0]; }
","             { fprintf( stderr, "[COMMA:%c]", yytext[0] ); return yytext[0]; }
";"             { fprintf( stderr, "[SEMICOLON:%c]", yytext[0] ); return yytext[0]; }
{number}        { fprintf( stderr, "[%d]", yylval.ival = (int)atoi( yytext )); return NUM; }
{whitespace}    { ; }
\n              { fprintf(stderr, "\n"); }
.               { return yytext[0]; }

%%

int yyerror( char *message )
{
    fprintf( stderr, "Error: %s\n", message );
    exit(1);
}