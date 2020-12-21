%{  
%}

%%
[ \r\n\t]+ {fprintf(yyout, "");} 
.       { fprintf(yyout, "%s", yytext); } 
%%

int yywrap(){}

int main() 
{
    extern FILE *yyin, *yyout; 
    yyin = fopen("input.txt", "r");
    yyout = fopen("Output.txt", "w");
    yylex(); 
    return 0; 
}