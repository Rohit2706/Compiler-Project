
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HASH_SIZE 57

#ifndef tokens
#define tokens

typedef enum {PROGRAM,MODULEDECLARATIONS,MODULEDECLARATION,OTHERMODULES,DRIVERMODULE,MODULE,RET,INPUT_PLIST,INPUT_PLIST_1,OUTPUT_PLIST,OUTPUT_PLIST_1,DATATYPE,TYPE,MODULEDEF,STATEMENTS,STATEMENT,IOSTMT,VAR,VAR_ID_NUM,BOOLCONSTT,WHICHID,SIMPLESTMT,ASSIGNMENTSTMT,WHICHSTMT,LVALUEIDSTMT,LVALUEARRSTMT,INDEX,MODULEREUSESTMT,OPTIONAL,IDLIST,IDLIST_1,EXPRESSION,U,U_1,ARMORBOOL,N7,ANYTERM,N8,ARITHMETICEXPR,ARITHMETICEXPR_1,TERM,TERM_1,FACTOR,OP1,OP2,LOGICALOP,RELATIONALOP,DECLARESTMT,CONDITIONALSTMT,CASESTMT,CASESTMT_1,VALUE,DEFAULT,ITERATIVESTMT,RANGE_ARRAYS,RANGE} NON_TERMINAL;

#endif

// Datapair is a structure that stores the key-value pair
typedef struct Datapair {
   char* key;   
   NON_TERMINAL value;
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
Datapair* create_pair(char* key, NON_TERMINAL val);
void insert_entry(hashtable *ht, char* key, NON_TERMINAL val);
NON_TERMINAL get_value(hashtable *ht,char* key);
void add_keywords(hashtable *ht);



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
Datapair* create_pair(char* key, NON_TERMINAL val){

    Datapair *newpair = malloc(sizeof(Datapair));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

// 4. To insert an entry in the hashtable
void insert_entry(hashtable *ht, char* key, NON_TERMINAL val){

    
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
NON_TERMINAL get_value(hashtable *ht,char* key){

    Datapair* pair = NULL;
    int hashvalue =hash_func(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

  //   if( pair == NULL||pair->key == NULL||strcmp( key, pair->key ) != 0 ) {
		// return ID;
  //   }
    return pair->value;
    
}


void add_keywords(hashtable *ht){

	 insert_entry(ht,"program",PROGRAM);
	 insert_entry(ht,"moduleDeclarations",MODULEDECLARATIONS);
	 insert_entry(ht,"moduleDeclaration",MODULEDECLARATION);
	 insert_entry(ht,"otherModules",OTHERMODULES);
	 insert_entry(ht,"driverModule",DRIVERMODULE);
	 insert_entry(ht,"module",MODULE);
	 insert_entry(ht,"ret",RET);
	 insert_entry(ht,"input_plist",INPUT_PLIST);
	 insert_entry(ht,"input_plist_1",INPUT_PLIST_1);
	 insert_entry(ht,"output_plist",OUTPUT_PLIST);
	 insert_entry(ht,"output_plist_1",OUTPUT_PLIST_1);
	 insert_entry(ht,"dataType",DATATYPE);
	 insert_entry(ht,"type",TYPE);
	 insert_entry(ht,"moduleDef",MODULEDEF);
	 insert_entry(ht,"statements",STATEMENTS);
	 insert_entry(ht,"statement",STATEMENT);
	 insert_entry(ht,"ioStmt",IOSTMT);
	 insert_entry(ht,"var",VAR);
	 insert_entry(ht,"var_id_num",VAR_ID_NUM);
	 insert_entry(ht,"boolConstt",BOOLCONSTT);
	 insert_entry(ht,"whichId",WHICHID);
	 insert_entry(ht,"simpleStmt",SIMPLESTMT);
	 insert_entry(ht,"assignmentStmt",ASSIGNMENTSTMT);
	 insert_entry(ht,"whichStmt",WHICHSTMT);
	 insert_entry(ht,"lvalueIDStmt",LVALUEIDSTMT);
	 insert_entry(ht,"lvalueARRStmt",LVALUEARRSTMT);
	 insert_entry(ht,"index",INDEX);
	 insert_entry(ht,"moduleReuseStmt",MODULEREUSESTMT);
	 insert_entry(ht,"optional",OPTIONAL);
	 insert_entry(ht,"idList",IDLIST);
	 insert_entry(ht,"idList_1",IDLIST_1);
	 insert_entry(ht,"expression",EXPRESSION);
	 insert_entry(ht,"U",U);
	 insert_entry(ht,"U_1",U_1);
	 insert_entry(ht,"armOrbool",ARMORBOOL);
	 insert_entry(ht,"N7",N7);
	 insert_entry(ht,"AnyTerm",ANYTERM);
	 insert_entry(ht,"N8",N8);
	 insert_entry(ht,"arithmeticExpr",ARITHMETICEXPR);
	 insert_entry(ht,"arithmeticExpr_1",ARITHMETICEXPR_1);
	 insert_entry(ht,"term",TERM);
	 insert_entry(ht,"term_1",TERM_1);
	 insert_entry(ht,"factor",FACTOR);
	 insert_entry(ht,"op1",OP1);
	 insert_entry(ht,"op2",OP2);
	 insert_entry(ht,"logicalOp",LOGICALOP);
	 insert_entry(ht,"relationalOp",RELATIONALOP);
	 insert_entry(ht,"declareStmt",DECLARESTMT);
	 insert_entry(ht,"conditionalStmt",CONDITIONALSTMT);
	 insert_entry(ht,"caseStmt",CASESTMT);
	 insert_entry(ht,"caseStmt_1",CASESTMT_1);
	 insert_entry(ht,"value",VALUE);
	 insert_entry(ht,"default",DEFAULT);
	 insert_entry(ht,"iterativeStmt",ITERATIVESTMT);
	 insert_entry(ht,"range_arrays",RANGE_ARRAYS);
	 insert_entry(ht,"range",RANGE);

}

NON_TERMINAL enumToString(char* inpString,hashtable* ht){
	//use hash table from hashNonTerminal.c
	return get_value(ht,inpString);
}

int main(){

	hashtable* ht=hashtable_create(57);
	add_keywords(ht);
	NON_TERMINAL nt=enumToString("range",ht);
	printf("result is %d\n", nt);
}
