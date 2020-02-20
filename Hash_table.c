#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HASH_SIZE 33
#define INT_MAX 2147483647

typedef enum
{
    INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,RECORD,TAGGED,UNION,GET_VALUE,
    PRINT,USE,WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
    
    ID
    // Check to see if there are additinal keywords.

} KEYWORD;

typedef struct  {
   char* key;   
   KEYWORD value;
   struct Datapair *next;
}Datapair;

typedef struct {
    int size;
    struct Datapair **table;
}hashtable;

hashtable* hashtable_create(int size){

    hashtable *newtable = (hashtable *)malloc(sizeof(hashtable));
    newtable->table = (Datapair **)malloc(sizeof(Datapair*) * size);

    for(int i=0;i<size;i++)
        newtable->table[i]=NULL;

    newtable->size = size;

    return newtable;

}

int hash_func(hashtable *ht, char* key ){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    printf("   %d   \n",(hashvalue%(ht->size)));        // Remove Post testing

    return (hashvalue%(ht->size));
}


Datapair* create_pair(char* key, KEYWORD val){

    Datapair *newpair = malloc(sizeof(Datapair));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

void insert_entry(hashtable *ht, char* key, KEYWORD val){

    printf("Trying to enter %s",key);           // Remove Post testing
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

KEYWORD get_value(hashtable *ht,char* key){

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
    insert_entry(ht,"record",RECORD);
    insert_entry(ht,"tagged",TAGGED);
    insert_entry(ht,"union",UNION);
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

int main(){

    hashtable *ht = hashtable_create(HASH_SIZE);
    
    add_keywords(ht);   
    
    // For testing 
    // Remove print statements from ~68 and ~51 after testing 
    printf("\nValues  :  %d  %d \n",hash_func(ht,"asdfasf"),get_value(ht,"ascsef"));
    
}