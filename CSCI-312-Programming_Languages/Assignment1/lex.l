%{
/* Ref: K&R Appendix A */
#include <stdio.h>
%}

%option yylineno
%x comment string_literal character_literal

identifier              {letter}({letter}|{digit})*
constant                (0[xX][0-9a-fA-F]+)|{digit}+(\.{digit}+)?(E[+-]?{digit}+)?
digit                   [0-9]
keyword                 auto|break|do|enum|goto|short|signed|sizeof|union|volatile|case|char|const|continue|default|double|else|extern|double|float|for|goto|if|int|long|register|return|static|struct|switch|typedef|union|unsigned|void|while
letter                  [a-zA-Z_]
bitwise_operator        (&|\||^|~|<<|>>)
logical_operator        (\|\||&&|!)
comparison_operator     (<|>|<=|>=|!=|\?|==)
operator                (->|[+\-*/%])
separator               [()\[\]{};,\.:`$i@#]
white_space             [ \n\r\t\f\\]+
assignment              [+\-*/]?=
preprocessor_directive  #{letter}+({white_space}+.*)?

%%

 /* Blanks, horizontal and vertical tabs, newlines, formfeeds, and comments are ignored. */
{white_space}                   ;
"/*"                            BEGIN(comment);
<comment>(.|\n)                 ; /* multi-line comments */
<comment>"*/"                   BEGIN(INITIAL);
"//".*                          ; /* single-line comments */
 /* Preprocessor directives are ignored. */
{preprocessor_directive}        ;
 /* There are six classes of tokens: identifiers, keywords, constants, string literals, operators, and other separators. */
{keyword}                       printf("KEYWORD\t%s\n", yytext); /* keywords */
{constant}                      printf("CONSTANT\t%s\n", yytext); /* constants */
"\""                            BEGIN(string_literal);
<string_literal>([^\"\\]|\\.)*       { printf("STRING_LITERAL\t\"%s\"\n", yytext); } /* string literals */
<string_literal>"\""            { BEGIN(INITIAL); }
"\'"                            BEGIN(character_literal);
<character_literal>([^\\']|\\.)        { printf("CHARACTER_LITERAL\t\'%s\'\n", yytext); } /* string literals */
<character_literal>"\'"         { BEGIN(INITIAL); }
{operator}                      printf("OPERATOR\t%s\n", yytext); /* operators */
{comparison_operator}           printf("COMPARISON_OPERATOR\t%s\n", yytext);
{logical_operator}              printf("LOGICAL_OPERATOR\t%s\n", yytext);
{bitwise_operator}              printf("BITWISE_OPERATOR\t%s\n", yytext);
{separator}                     printf("SEPARATOR\t%s\n", yytext); /* other separators */
{identifier}                    printf("IDENTIFIER\t%s\n", yytext); /* identifiers */
{assignment}                    printf("ASSIGNMENT\t%s\n", yytext); /* assignments */
[^\x00-\x7F]                    printf("NON_ASCII\t%s\n", yytext);
.                               printf("UNRECOGNIZED\t%s\n", yytext);

%%

int yywrap(){}

int main(int argc, char *argv[])
{
    yylex();
    return 0;
}
