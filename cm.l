%{
#include "globals.h"
#include "util.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
%}

%option noyywrap

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"else"          {return ELSE;}
"if"            {return IF;}
"int"          {return INT;}
"return"          {return RETURN;}
"void"          {return VOID;}
"while"          {return WHILE;}
"+"             {return PLUS;}
"-"            {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"<="             {return LE;}
"<"             {return LT;}
">="             {return GE;}
">"             {return GT;}
"=="             {return EQ;}
"="             {return ASSIGN;}
"!="             {return NE;}
";"             {return SEMI;}
","             {return COMMA;}
"("             {return LPAREN;}
")"             {return RPAREN;}
"["             {return LBRACK;}
"]"             {return RBRACK;}
"{"             {return LBRACE;}
"}"             {return RBRACE;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"/*"            {char c;
                 for( ; ; )
                 {
                     while((c = input()) != '*' && c != EOF)
                     {
                         if(c == '\n') lineno++;
                     }
                     if(c == '*')
                     {
                         while((c = input()) == '*');
                         if(c == '\n') lineno++;
                         if(c == '/') break;
                     }
                     if(c == EOF) return COMMENT_ERROR;
                 }
                }
<<EOF>>         {return ENDFILE;}
.               {return ERROR;}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    printToken(currentToken,tokenString);
  }
  return currentToken;
}