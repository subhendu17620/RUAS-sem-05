/*Definition Section*/

%{
#include <stdio.h>
int n = 0 ;   
%}

/*Rule Section*/

%%

auto|double|int|struct|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|continue|for|signed|void|do|if|static|while|default|goto|sizeof|volatile|const|float|short {n++;printf("\t keyword:%s", yytext);}

[{};,()] {n++;printf("\t seperator:%s", yytext);}
   
[+-/=*%]  {n++;printf("\t operator:%s", yytext);}

([a-zA-Z][0-9])+|[a-zA-Z]* {n++; printf("\t identifier:%s", yytext); }
                                             
.|\n ;
%%

    
    int yywrap()
{
    return 1;
}

int main(void)
{
    
    extern FILE* yyin; 
    yyin = fopen("input.c", "r"); 
    yylex(); 
      
    printf("\n total no. of token = %d\n", n);    
    return 0;
}
