%{ 
    #include <stdio.h>
    int lctr=0;
%}


%%
  /*count number of newline*/
[\n]    {lctr++;}
.\n {fprintf(yyout, "%s",yytext); lctr++;}
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
    printf("the number of newlines in this file are: %d\n",lctr);
	return 0; 
}