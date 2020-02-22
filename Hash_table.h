// This file implements the hash table data structure

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HASH_SIZE 33
#define INT_MAX 2147483647

#ifndef tokens
#define tokens
typedef enum{INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
			 WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM, EPSILON, DOLLAR
             } TOKEN;

#endif

// Datapair is a structure that stores the key-value pair
typedef struct Datapair {
   char* key;   
   TOKEN value;
   struct Datapair *next;
}Datapair;

// Hashtable is a data structure containing all the Datapairs 
typedef struct {
    int size;
    Datapair **table;
}hashtable;

// Function prototypes

hashtable* hashtable_create(int size);
int hash_func(hashtable *ht, char* key );
Datapair* create_pair(char* key, TOKEN val);
void insert_entry(hashtable *ht, char* key, TOKEN val);
TOKEN get_value(hashtable *ht,char* key);
void add_keywords(hashtable *ht);