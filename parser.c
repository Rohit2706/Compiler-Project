#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mappingTable.h"

#define GRAMMAR_SIZE 104
#define NT_SIZE 57
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

void readIntoArr(FILE* grammarRules, linkedList* grammar[]){
    
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
                    addLhs(grammar[currRow], T.value,T.tag);
                    flag=1;
                }
                
                else{
                    addRhs(grammar[currRow], T.value,T.tag);
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
    if(tag==2){
    	switch(sym.nt_val){
	    	case PROGRAM_NT: return "program" ; break;
        case MODULEDECLARATIONS: return "moduledeclarations" ; break;
        case MODULEDECLARATION: return "moduledeclaration" ; break;
        case OTHERMODULES: return "othermodules" ; break;
        case DRIVERMODULE: return "drivermodule" ; break;
        case MODULE_NT: return "module" ; break;
        case RET: return "ret" ; break;
        case INPUT_PLIST: return "input_plist" ; break;
        case INPUT_PLIST_1: return "input_plist_1" ; break;
        case OUTPUT_PLIST: return "output_plist" ; break;
        case OUTPUT_PLIST_1: return "output_plist_1" ; break;
        case DATATYPE: return "datatype" ; break;
        case TYPE: return "type" ; break;
        case MODULEDEF: return "moduledef" ; break;
        case STATEMENTS: return "statements" ; break;
        case STATEMENT: return "statement" ; break;
        case IOSTMT: return "iostmt" ; break;
        case VAR: return "var" ; break;
        case VAR_ID_NUM: return "var_id_num" ; break;
        case BOOLCONSTT: return "boolconstt" ; break;
        case WHICHID: return "whichid" ; break;
        case SIMPLESTMT: return "simplestmt" ; break;
        case ASSIGNMENTSTMT: return "assignmentstmt" ; break;
        case WHICHSTMT: return "whichstmt" ; break;
        case LVALUEIDSTMT: return "lvalueidstmt" ; break;
        case LVALUEARRSTMT: return "lvaluearrstmt" ; break;
        case INDEX: return "index" ; break;
        case MODULEREUSESTMT: return "modulereusestmt" ; break;
        case OPTIONAL: return "optional" ; break;
        case IDLIST: return "idlist" ; break;
        case IDLIST_1: return "idlist_1" ; break;
        case EXPRESSION: return "expression" ; break;
        case U: return "u" ; break;
        case U_1: return "u_1" ; break;
        case ARMORBOOL: return "armorbool" ; break;
        case N7: return "n7" ; break;
        case ANYTERM: return "anyterm" ; break;
        case N8: return "n8" ; break;
        case ARITHMETICEXPR: return "arithmeticexpr" ; break;
        case ARITHMETICEXPR_1: return "arithmeticexpr_1" ; break;
        case TERM: return "term" ; break;
        case TERM_1: return "term_1" ; break;
        case FACTOR: return "factor" ; break;
        case OP1: return "op1" ; break;
        case OP2: return "op2" ; break;
        case LOGICALOP: return "logicalop" ; break;
        case RELATIONALOP: return "relationalop" ; break;
        case DECLARESTMT: return "declarestmt" ; break;
        case CONDITIONALSTMT: return "conditionalstmt" ; break;
        case CASESTMT: return "casestmt" ; break;
        case CASESTMT_1: return "casestmt_1" ; break;
        case VALUE: return "value" ; break;
        case DEFAULT_NT: return "default" ; break;
        case ITERATIVESTMT: return "iterativestmt" ; break;
        case RANGE_ARRAYS: return "range_arrays" ; break;
        case RANGE: return "range" ; break;
       	default: return "Unrecognized NT"; break;
    	}
    }

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
int first[NT_SIZE] = {0};

typedef struct Rule_node{
	int rule;
	struct Rule_node* next;
}Rule_node;

typedef struct{
	Rule_node* head;
	Rule_node* tail;
}Rule;

Rule map[NT_SIZE];
/*
int calculateFirst(NON_TERMINAL nt){
  	if(first[nt])
    	return first[nt];

	Rule_node* curr = map[nt]->head;
	while(curr!=NULL){
    node* symbol_node = Grammar[curr->rule]->head->next ; //Symbol is union of NT and T
    int val = 0;
    while(symbol_node!=NULL) //Add isTerminal
    {
			if(isTerminal(s)){
      	first[nt] = first[nt] | locate(symbol_node->symbol);
        break;
      }
    	else{
        val = calculateFirst(symbol_node->symbol);
      	first[nt] = first[nt] | ((val&1)?(val-1):val);
      }
      if(first[symbol_node->symbol]&1){
      	symbol_node = symbol_node->next;
      }
      else
        break;
    }
    
    if(symbol_node==NULL)
      first[nt] = first[nt] | 1;
    
    curr = curr->next;
	}
  
  return first[nt];
}
*/


int main(){
	ht = hashtable_create(HASH_SIZE);
	add_terminals(ht);   
    add_nonterminals(ht);

	FILE* grammarFile= fopen("grammar.txt","r");

	if (grammarFile == NULL) {
	    printf("Grammar File Not Found \n");
	    return 0;
	}

	linkedList* grammar[GRAMMAR_SIZE];
	for(int i=0;i<GRAMMAR_SIZE;i++){
	    grammar[i] = createLinkedList();
	}

  readIntoArr(grammarFile, grammar);
  /*
  for(int i=0;i<GRAMMAR_SIZE;i++){
		NON_TERMINAL index = arr[i]->head->data;
		if(map[index]->head==NULL){
			map[index]->head = malloc(sizeof(Rule_node));
			map[index]->head->rule = i;
			map[index]->head->next = NULL;
			map[index]->tail = map[index]->head;
		}
		else{
			map[index]->tail->next = malloc(sizeof(Rule_node));
			map[index]->tail = map[index]->tail->next;
			map[index]->tail->rule = i;
			map[index]->tail->next = NULL;
		}
	}*/

  FILE* fp = fopen("testGrammar.txt","w");
  for(int i=0;i<GRAMMAR_SIZE;i++){
        node* curr = grammar[i]->head;
        fprintf(fp,"%s ", convert2(curr->data,curr->tag));
        curr = curr->next;
        while(curr!=NULL){
            fprintf(fp,"%s ", convert2(curr->data,curr->tag));
            curr = curr->next;
        }

        fprintf(fp,"\n");
    }
   
  NON_TERMINAL nt = PROGRAM_NT;
  //calculateFirst(nt);

	for(int i=0;i<HASH_SIZE;i++)
      free(ht->table[i]);
  free(ht->table);
  free(ht);
}