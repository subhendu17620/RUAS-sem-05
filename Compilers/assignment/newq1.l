
%{ 
    #include <stdio.h>
    int lctr=0, sctr=0;
%}


%%
("( ")    {fprintf(yyout,"%s",yytext);sctr++;}
[\(]    {fprintf(yyout,"( ");sctr++;}
(") ")    {fprintf(yyout,"%s",yytext);sctr++;}
[\)]    {fprintf(yyout," )");sctr++;}
[ ]+    {fprintf(yyout," ");sctr++;}
[\n]+    {fprintf(yyout,"");lctr++;}
(" :")    {fprintf(yyout,"%s\n",yytext);sctr++;}
;$    {fprintf(yyout," ;\n");sctr++;}
[/*]    {fprintf(yyout," %s ", yytext);sctr++; sctr++;}
.\n    {fprintf(yyout, "%s",yytext); lctr++;}
%%

int yywrap(){}

int main() 
{
    extern FILE *yyin, *yyout;

    yyin = fopen("Input.txt", "r");
    yyout = fopen("Output.txt", "w");

    yylex(); 
    fclose(yyin);
    fclose(yyout);
    return 0;
} 
