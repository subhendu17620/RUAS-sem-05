%{ 
    #include <stdio.h>
    int space_count=0;
%}

 // defining regex

space [ ]+

%%
{space}    {space_count++;fprintf(yyout," ");}
. {fprintf(yyout, "%s",yytext);}
%%

int yywrap(){} 

int main() 
{
    extern FILE *yyin, *yyout; 

    yyin = fopen("input.txt", "r"); 
    yyout = fopen("output1b.txt", "w"); 

    yylex(); 
    fclose(yyin);
    fclose(yyout);
    printf("compressed count of spaces : %d\n",space_count);
    return 0; 
}



