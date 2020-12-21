%{ 
    #include <stdio.h>
    int tokens = 0;
%}


%%

 /* remove white spaces*/
[ ]+    {fprintf(yyout," ");}

 /*count identifiers and keywords*/
[a-zA-Z_][a-zA-Z0-9_]*   {tokens++;fprintf(yyout,"%s",yytext);}


 /*count operators*/
"<="|"=="|"="|"++"|"-"|"*"|"+"|"&"|">"|"<"|"|"|"/"|"%"    {tokens++;fprintf(yyout,"%s",yytext);}

 /*count and adding space before and after puncutations*/
[,;:]    {tokens++;fprintf(yyout," %s ",yytext);}
[,;:][\n]    {tokens++;fprintf(yyout," %s",yytext);}

 /*count and adding space after opening brackets */
[({\[]    {tokens++;fprintf(yyout,"%s ",yytext);}
[({\[][\n]    {tokens++;fprintf(yyout,"%s ",yytext);}

 /*count and adding space before closing brackets*/
[)}\]]    {tokens++;fprintf(yyout," %s",yytext);}
[)}\]][\n]    {tokens++;fprintf(yyout," %s",yytext);}

 /*count float literal*/
[0-9]*"."[0-9]+    {tokens++;fprintf(yyout,"%s",yytext);}

 /*count int literal*/
[0-9]+   {tokens++;fprintf(yyout,"%s",yytext);}

 /*count string literal*/
\"(\\.|[^"\\])*\"    {tokens++;fprintf(yyout,"%s",yytext);} 

 /*count character literal*/
\'(\\.|[^'\\])*\'    {tokens++;fprintf(yyout,"%s",yytext);}

 /*skip pre-processor */
#[a-zA-Z]* ;
"<"+([a-zA-Z]*"."[a-zA-Z]*)+">" ;

 /*skip comments*/
\/\/(.*)    ;

 /*skip newlines*/
[\n]    ;
.\n    {fprintf(yyout, "%s",yytext);}
%%

int yywrap(){} 

int main() 
{
    extern FILE *yyin, *yyout; 

    yyin = fopen("input.txt", "r"); 
    yyout = fopen("output1c.txt", "w"); 

    yylex(); 

    fclose(yyin);
    fclose(yyout);
    printf("number of tokens : %d\n",tokens);
    
    return 0; 
}