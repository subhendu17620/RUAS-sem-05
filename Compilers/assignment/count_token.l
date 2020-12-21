%{
    int count=0;
%}

 // defining regex

 // literals
int_num -?[0-9]+
float_num -?([0-9]+\.[0-9]+)([eE][-+]?[0-9]+)?
string_literal \"[^\"]*\"
char_literal \'[^\']*\'

 // variable
identifier [a-zA-Z_][a-zA-Z0-9_]*

 // special symbols
block_start \{
block_end \}
open_brac \(
close_brac \)
semicolon \;
comma \,
colon \:

 
 // operators
plus \+
minus \-
mul \*
div \/
mod %
inc \+\+
dec \-\-
neq !=
assignment =
eq ==
lt <
leq <=
gt >
geq >=
and &&
or \|\|
not !
bitand &


 //single line comment
comment \/\/(.*)


 // preprocessors
preprocessor "#include <stdio.h>"

%%

auto|double|int|struct|break|else|long|switch|case|typedef|char|extern|return|continue|for|signed|void|do|if|static|while|default|goto|sizeof|const|float|short    %{count++; fprintf(yyout, "%s\n",yytext);%}

{identifier}    %{count++;fprintf(yyout, "%s\n", yytext);%}

{int_num}|{float_num}|{string_literal}|{char_literal}   %{count++; fprintf(yyout, "%s\n",yytext);%}

{block_start}|{block_end}|{open_brac}|{close_brac}|{semicolon}|{comma}|{colon}    %{count++; fprintf(yyout, "%s\n", yytext);%}

{plus}|{minus}|{mul}|{div}|{mod}|{inc}|{dec}|{neq}|{assignment}|{eq}|{lt}|{leq}|{gt}|{geq}|{and}|{or}|{not}|{bitand}    %{count++; fprintf(yyout, "%s\n",yytext);%}

{comment}    ;

{preprocessor}     ;

.    ;

%%

int yywrap() {
    return 1;
}


int main()
{
    extern FILE* yyin; 
    yyin = fopen("input.c", "r"); 
    yyout = fopen("output.txt", "w");

    yylex(); 
    
    fclose(yyin);
    fclose(yyout);

    printf("\n Total no of token = %d\n", count);
    
}  