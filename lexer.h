// This file implements the lexical analyser

#include<stdlib.h>
#include<stdio.h>

// TOKEN is an enum variable for possible tokens in the ERPLAG language
#ifndef tokens
#define tokens
typedef enum{EPSILON, DOLLAR,INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
             WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM
             } TOKEN;
             
#endif
             
// VALUE is a tagged union that stores the numeric value for lexemes of type NUM(tag=1) and RNUM(tage=2). For others VALUE is displayed as none(tag=0)
typedef union{
	uint num_value;
	float rnum_value;
}VALUE;

// TokenInfo contains all the required information about the tokenized lexeme, to be returned to the parser on demand.
typedef struct{
	TOKEN token;
	char lexeme[25];
	uint line_no;
	int length;
	VALUE value;
	int tag;
}TokenInfo;

// Functions declarations for lexer
TokenInfo getNextToken();
TokenInfo tokenGen(TokenInfo newToken, TOKEN token_name);
void getStream(char* buffer);
TokenInfo failure(TokenInfo newToken, char ch);
char getNextChar(char* lexeme, int* length);
void retract(char* lexeme, int* length);
TOKEN search_keyword(char* lexeme, int* length);
void enddriver();
void driver();
//const char* convert(TOKEN sym);