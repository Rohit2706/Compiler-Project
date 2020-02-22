#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mappingTable.h"

#define GRAMMAR_SIZE 104

hashtable* ht;

typedef struct Node{
    Symbol data;
    struct Node* next;
    struct Node* prev;
    int tag;
}node;

typedef struct LinkedList{
    node* head;
    node* tail;
}linkedList;

linkedList* createLinkedList(){
    linkedList* lhsNode=(linkedList* )malloc(sizeof(linkedList));
    return lhsNode;
}

void addLhs(linkedList* inpLinkedList, Symbol inpData, int inpTag){
    node* lhs=(node*)malloc(sizeof(node));
    lhs->data=inpData;
    lhs->tag=inpTag;
    lhs->next=NULL;
    lhs->prev=NULL;
    inpLinkedList->head=lhs;
    inpLinkedList->tail=lhs;
}

void addRhs(linkedList* inpLinkedList, Symbol inpData, int inpTag){
    node* rhs=(node*)malloc(sizeof(node));
    rhs->data=inpData;
    rhs->tag=inpTag;
    rhs->next=NULL;
    rhs->prev=inpLinkedList->tail;
    inpLinkedList->tail->next=rhs;
    inpLinkedList->tail=rhs;

}

void readIntoArr(FILE* grammarRules, linkedList* arrLinkedList[]){
    
    char line[1000]={'#'};
    char token[50];
    int flag=0;
    int currRow=0;
    int beg=0;
    int end=0;
    
    while(fgets(line,sizeof(line),grammarRules) != NULL){
        beg=0;
        end=0;
        while(line[end]!='\0' || line[end]!='\n'){
            if(line[end]==' ' || line[end]=='\0' || line[end]=='\n'){
                char* insert=(char*)malloc((end-beg)*sizeof(char));
                
                for(int i=beg;i<end;i++){
                    insert[i-beg]=line[i];    
                }
                tagged_union T = get_value(ht,insert);
                if(flag==0){
                    addLhs(arrLinkedList[currRow], T.value,T.tag);
                    flag=1;
                }
                
                else{
                    addRhs(arrLinkedList[currRow], T.value,T.tag);
                }
                
                end++;
                beg=end;
                
                if(line[end]=='\0' || line[end]=='\n'){
                    break;
                }
                
            }
            
            else{
                end++;
            }

        }
        
        currRow++;
        flag=0;
    }

}


const char* convert2(Symbol sym, int tag){
    if(tag==2)
        return "NT";

    switch(sym.t_val)
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
        case EPSILON: return "EPSILON"; break;
        default: return "UNRECOGNIZED TOKEN"; break;
    }
}

int main(){
	ht = hashtable_create(HASH_SIZE);
	add_terminals(ht);   
    add_nonterminals(ht);

	FILE* grammarFile= fopen("grammar.txt","r");

	if (grammarFile == NULL) {
	    printf("Grammar File Not Found \n");
	    return 0;
	}

	linkedList* arrLinkedList[GRAMMAR_SIZE];
	for(int i=0;i<GRAMMAR_SIZE;i++){
	    arrLinkedList[i] = createLinkedList();
	}

  readIntoArr(grammarFile, arrLinkedList);

  for(int i=0;i<GRAMMAR_SIZE;i++){
        node* curr = arrLinkedList[i]->head;
        printf("%s-> ", convert2(curr->data,curr->tag));
        curr = curr->next;
        while(curr!=NULL){
            printf("%s ", convert2(curr->data,curr->tag));
            curr = curr->next;
        }

        printf("\n\n");
    }

	for(int i=0;i<HASH_SIZE;i++)
      free(ht->table[i]);
  free(ht->table);
  free(ht);
}