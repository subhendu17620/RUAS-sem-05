%{ 
    #include <stdio.h>
    int lctr=0;
%}

new_line [\r\n]

%%
[\n]    {lctr++;}
.\n    {fprintf(yyout, "%s",yytext);lctr++;}
%%

int yywrap(){} 

int main() 
{
    extern FILE *yyin, *yyout; 

	yyin = fopen("input.txt", "r"); 
	yyout = fopen("output1a.txt", "w"); 

	yylex(); 

    fclose(yyin);
    fclose(yyout);
    printf("number of newlines : %d\n",lctr);
	return 0; 
}