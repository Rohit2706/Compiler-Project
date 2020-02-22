// This file implements the hash table data structure

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Hash_table.h"

// Function definations

// 1. To create hash table
hashtable* hashtable_create(int size){

    hashtable *newtable = (hashtable *)malloc(sizeof(hashtable));
    newtable->table = (Datapair **)malloc(sizeof(Datapair*) * size);

    for(int i=0;i<size;i++)
        newtable->table[i]=NULL;

    newtable->size = size;

    return newtable;

}

// 2. To design hash function.
// About the hash function:
// If key is c1c2c3 where c1, c2, c3 are characters
// Then the hash value is decimal equivalent of
// [bit(c1) bit(c2) bit(c3)] % (size of hash table)
// where bit(c) is the bit representation of the ASCII value of c

int hash_func(hashtable *ht, char* key ){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    return (hashvalue%(ht->size));
}


// 3. to create the key-value Datapair
Datapair* create_pair(char* key, TOKEN val){

    Datapair *newpair = malloc(sizeof(Datapair));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

// 4. To insert an entry in the hashtable
void insert_entry(hashtable *ht, char* key, TOKEN val){

    
    int hashval =hash_func(ht,key);

    Datapair *end=NULL;
    Datapair *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair *newpair = create_pair(key,val);

    if(next == ht->table[hashval]){
        newpair->next = next;
        ht->table[hashval] = newpair;
        }
        else if(next == NULL){
            end->next = newpair; 
        }   else{
                newpair->next = next;
                end->next = newpair;
        }

}

// 5. To get the value given a key
TOKEN get_value(hashtable *ht,char* key){

    Datapair* pair = NULL;
    int hashvalue =hash_func(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

    if( pair == NULL||pair->key == NULL||strcmp( key, pair->key ) != 0 ) {
		return ID;
    }
    return pair->value;
    
}

// 6. To populate our hash table with keywords
void add_keywords(hashtable *ht){

    insert_entry(ht,"integer",INTEGER);
    insert_entry(ht,"real",REAL);
    insert_entry(ht,"boolean",BOOLEAN);
    insert_entry(ht,"of",OF);
    insert_entry(ht,"array",ARRAY);
    insert_entry(ht,"start",START);
    insert_entry(ht,"end",END);
    insert_entry(ht,"declare",DECLARE);
    insert_entry(ht,"module",MODULE);
    insert_entry(ht,"driver",DRIVER);
    insert_entry(ht,"program",PROGRAM);
    insert_entry(ht,"get_value",GET_VALUE);
    insert_entry(ht,"print",PRINT);
    insert_entry(ht,"use",USE);
    insert_entry(ht,"with",WITH);
    insert_entry(ht,"parameters",PARAMETERS);
    insert_entry(ht,"true",TRUE);
    insert_entry(ht,"false",FALSE);
    insert_entry(ht,"takes",TAKES);
    insert_entry(ht,"input",INPUT);
    insert_entry(ht,"returns",RETURNS);
    insert_entry(ht,"AND",AND);
    insert_entry(ht,"OR",OR);
    insert_entry(ht,"for",FOR);
    insert_entry(ht,"in",IN);
    insert_entry(ht,"switch",SWITCH);
    insert_entry(ht,"case",CASE);
    insert_entry(ht,"break",BREAK);
    insert_entry(ht,"default",DEFAULT);
    insert_entry(ht,"while",WHILE);
}

// UNCOMMENT the following while testing

/*
const char* convert(TOKEN sym){
    switch(sym)
    {
        case PLUS: return "PLUS" ; break;
        case MINUS: return "MINUS" ; break;
        case MUL: return "MUL" ; break;
        case DIV: return "DIV" ; break;
        case LT: return "LT" ; break;
        case LE: return "LE" ; break;
        case GE: return "GE" ; break;
        case GT: return "GT" ; break;
        case EQ: return "EQ" ; break;
        case NE: return "NE" ; break;
        case DEF: return "DEF" ; break;
        case ENDDEF: return "ENDDEF" ; break;
        case DRIVERDEF: return "DRIVERDEF" ; break;
        case DRIVERENDDEF: return "DRIVERENDDEF" ; break;
        case COLON: return "COLON" ; break;
        case RANGEOP: return "RANGEOP" ; break;
        case SEMICOL: return "SEMICOL" ; break;
        case COMMA: return "COMMA" ; break;
        case ASSIGNOP: return "ASSIGNOP" ; break;
        case SQBO: return "SQBO" ; break;
        case SQBC: return "SQBC" ; break;
        case BO: return "BO" ; break;
        case BC: return "BC" ; break;
        case ID: return "ID" ; break;
        case NUM: return "NUM" ; break;
        case RNUM: return "RNUM" ; break;
        case INTEGER: return "INTEGER" ; break;
        case REAL: return "REAL" ; break;
        case BOOLEAN: return "BOOLEAN" ; break;
        case OF: return "OF" ; break;
        case ARRAY: return "ARRAY" ; break;
        case START: return "START" ; break;
        case END: return "END" ; break;
        case DECLARE: return "DECLARE" ; break;
        case MODULE: return "MODULE" ; break;
        case DRIVER: return "DRIVER" ; break;
        case PROGRAM: return "PROGRAM" ; break;
        case GET_VALUE: return "GET_VALUE" ; break;
        case PRINT: return "PRINT" ; break;
        case USE: return "USE" ; break;
        case WITH: return "WITH" ; break;
        case PARAMETERS: return "PARAMETERS" ; break;
        case TRUE: return "TRUE" ; break;
        case FALSE: return "FALSE" ; break;
        case TAKES: return "TAKES" ; break;
        case INPUT: return "INPUT" ; break;
        case RETURNS: return "RETURNS" ; break;
        case AND: return "AND" ; break;
        case OR: return "OR" ; break;
        case FOR: return "FOR" ; break;
        case IN: return "IN" ; break;
        case WHILE: return "WHILE"; break;
        case SWITCH: return "SWITCH" ; break;
        case CASE: return "CASE" ; break;
        case BREAK: return "BREAK" ; break;
        case DEFAULT: return "DEFAULT" ; break;
        default: return "UNRECOGNIZED TOKEN"; break;
    }
}
*/

// UNCOMMENT THE MAIN FUNCTION TO TEST THE HASH TABLE FOR KEYWORDS 
// NOTE: 1. RUN THIS FILE INDEPENDENTLY IF UNCOMMENTING OR ELSE THERE MIGHT BE CONFLICTING HASH TABLES WITH SAME NAME
//       2. UNCOMMENT utility function convert for user friendly output
//          Function protoype: const char* convert(TOKEN sym);

/*
int main(){

    hashtable *ht = hashtable_create(HASH_SIZE);
    add_keywords(ht);   

    // Some Test Cases (Note that it will print ID for the keys that are not keywords)
    printf("\n");
    printf("Input: integer  \tTOKEN: %s\n",convert(get_value(ht,"integer")));
    printf("Input: switch   \tTOKEN: %s\n",convert(get_value(ht,"switch")));
    printf("Input: SWITCH   \tTOKEN: %s\n",convert(get_value(ht,"SWITCH")));
    printf("Input: compiler \tTOKEN: %s\n",convert(get_value(ht,"compiler_project")));
    printf("Input: get_value\tTOKEN: %s\n",convert(get_value(ht,"get_value")));
    printf("Input: abc123   \tTOKEN: %s\n",convert(get_value(ht,"abc123")));
    printf("\n");

    // Free memory

    for(int i=0;i<HASH_SIZE;i++)
        free(ht->table[i]);
    free(ht->table);
    free(ht);
    
}*/