#include<stdlib.h>
#include<stdio.h>

typedef enum{PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM, ERROR} TOKEN;

typedef union{
	uint num_value;
	float rnum_value;
}VALUE;

typedef struct{
	TOKEN token;
	char lexeme[25];
	uint length;
	uint line_no;
	VALUE value;
	int tag;
}TokenInfo;
