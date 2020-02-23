#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "mappingTable.h"

#define GRAMMAR_SIZE 104
#define NT_SIZE 56
#define TOKEN_SIZE 58

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

linkedList* grammar[GRAMMAR_SIZE];

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
        case DOLLAR: return "$"; break;
        default: return "UNRECOGNIZED TOKEN"; break;
    }
}
unsigned long int first[NT_SIZE] = {0};

typedef struct Rule_node{
	int rule;
	struct Rule_node* next;
}Rule_node;

typedef struct{
	Rule_node* head;
	Rule_node* tail;
}Rule;

Rule map[NT_SIZE];

unsigned long int calculateFirst(NON_TERMINAL nt){
  	if(first[nt])
    	return first[nt];

	Rule_node* curr = map[nt].head;
	while(curr!=NULL){
    node* symbol_node = grammar[curr->rule]->head->next ; //Symbol is union of NT and T
    unsigned long val = 0;
    while(symbol_node!=NULL) 
    {
			if(symbol_node->tag==1){
      	first[nt] = first[nt] | (1lu<<(symbol_node->data).t_val);
        break;
      }
    	else{
        val = calculateFirst((symbol_node->data).nt_val);
      	first[nt] = first[nt] | ((val&1)?(val-1):val);
      }
      if(first[(symbol_node->data).nt_val]&1){
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

void convertfirst(unsigned long int val){
	int pos = 0;
	Symbol s;
	while(val){
		if(val&1){
			s.t_val = (TOKEN)pos;
			printf("%s, ",convert2(s,1));
		}
		val >>=1;
		pos++;
	}
}

typedef struct iterateNode{
	node* position;
	int rule;
	struct iterateNode* next;
}iterateNode;

typedef struct{
	iterateNode* head;
	iterateNode* tail;
}iterateRule;

iterateRule followMap[NT_SIZE];

void populateArray(){
	
	for(int i=0;i<NT_SIZE;i++){
	  	followMap[i].head=NULL;
	  	followMap[i].tail=NULL;
    }

    for(int i=0;i<GRAMMAR_SIZE;i++){
  		node* temp=grammar[i]->head->next;
  		int compareTag;
		NON_TERMINAL index;

		while(temp!=NULL){
			compareTag = temp->tag;
			if(compareTag==2){
				index = (temp->data).nt_val;
				if(followMap[index].head==NULL){
					followMap[index].head = malloc(sizeof(iterateNode));
					followMap[index].head->rule = i;
					followMap[index].head->position = temp;
					followMap[index].head->next = NULL;
					followMap[index].tail = followMap[index].head;
				}

				else{
					followMap[index].tail->next = malloc(sizeof(iterateNode));
					followMap[index].tail = followMap[index].tail->next;
					followMap[index].tail->rule = i;
					followMap[index].tail->position = temp;
					followMap[index].tail->next = NULL;
				}
			}

			temp=temp->next;
		}
			
		
	}
}

unsigned long int follow[NT_SIZE];

unsigned long int calculateFollow(NON_TERMINAL nt){
	if(follow[nt])
    	return follow[nt];

	iterateNode* curr = followMap[nt].head;
	if(map[nt].head->rule==0)
		follow[nt] = 2;

	while(curr!=NULL){
	    node* symbol_node = curr->position->next;
	    unsigned long val = 0;
	    while(symbol_node!=NULL) 
	    {
		  if(symbol_node->tag==1){
	        follow[nt] = follow[nt] | (1lu<<(symbol_node->data).t_val);
	        break;
	      }
          val = first[(symbol_node->data).nt_val];
      	  follow[nt] = follow[nt] | ((val&1)?(val-1):val);
      	  if(first[(symbol_node->data).nt_val]&1){
      	 	symbol_node = symbol_node->next;
      	  }
      	  else
      	  	break;
	    }

	    if(symbol_node==NULL){
	      NON_TERMINAL temp_nt = (grammar[curr->rule]->head->data).nt_val;
	      if(nt != temp_nt){
	      	if(follow[temp_nt])
	      		follow[nt] = follow[nt] | follow[temp_nt];
	      	else
	      		follow[nt] = follow[nt] | calculateFollow(temp_nt);
	      }
		}
	    
	    curr = curr->next;
	}
  
  return follow[nt];
}

// int isKthBitSet(unsigned long int n, int k) 
// { 
//     if (n & (1lu << k)) 
//         return 1; 
    
//     return 0; 
// } 

// int parseTable[NT_SIZE][TOKEN_SIZE];

// for(int i=0;i<NT_SIZE;i++){
//     for(int j=0;j<TOKEN_SIZE;j++){
//         parseTable[i][j]=-1;
//     }
// }

// void makeParseTable(){
//     for(int i=0;i<GRAMMAR_SIZE;i++){
//         node* temp=grammar[i]->head;
//         NON_TERMINAL term=(temp->data).nt_val;
//         temp=temp->next;

//         while(temp!=NULL)
//     }
// }



int ParseTable[NT_SIZE][TOKEN_SIZE]; // NT vs T , declare constants


//  ASSUMPTIONS
// 1. arrLinkedList is the global grammar
// 2. FIRST is the integer array with the encoded firsts of indexes
// 3. FOLLOW ""
// 4. ParseTable is global variable


void populate_row(int val, NON_TERMINAL nt, int rule_no,int pop){

    int top=0;
    while((1<<top) < val) top++;

    while(top--){
        if((1<<top) <= pop){
            pop = pop - (1<<top);
            ParseTable[nt][top] = rule_no;
        }
    }
}

int is_epsilon_present(unsigned long int num){
    return ((num&1)?1:0);
}

void populate_parse_table(){

    for(int i = 0;i<NT_SIZE;i++)
        for(int j=0;j<TOKEN_SIZE;j++)
            ParseTable[i][j]=-1;

    for(int i=0;i<GRAMMAR_SIZE;i++){

        // printf("Rule noumber %d \n",i);
        node* temp = grammar[i]->head->next;
        int pop=0;

        while(temp){

            if(temp->tag==1){
                pop= pop | (1<<(temp->data).t_val);
                break;
            }

            pop = pop|first[(temp->data).t_val];

            if(! is_epsilon_present(first[(temp->data).t_val]))
                break;
            else{
                if(temp->next==NULL)
                    pop = pop|follow[(grammar[i]->head->data).nt_val];
                else
                    temp = temp->next;
                
            }

        }

        populate_row(pop,(grammar[i]->head->data).nt_val,i,pop);

    }

    for(int j=0;j<7;j++){
            Symbol s;
            s.t_val  = (TOKEN)j;
            printf("%-15s ",convert2(s,1));
    }
    printf("\n");
    for(int i=0;i<10;i++){
        for(int j=0;j<7;j++)
            printf("%-15d ",ParseTable[i][j]);
        printf("\n");;
    }
    
}



  //malloc
//     for(int i=0;i<HASH_SIZE;i++)
//       free(ht->table[i]);
//   free(ht->table);
//   free(ht);
// }

int main(){
	ht = hashtable_create(HASH_SIZE);
	add_terminals(ht);   
    add_nonterminals(ht);

	FILE* grammarFile= fopen("grammar.txt","r");

	if (grammarFile == NULL) {
	    printf("Grammar File Not Found \n");
	    return 0;
	}

	for(int i=0;i<GRAMMAR_SIZE;i++){
	    grammar[i] = createLinkedList();
	}

  readIntoArr(grammarFile, grammar);
  
  for(int i=0;i<NT_SIZE;i++){
  	map[i].head=NULL;
  	map[i].tail=NULL;
  }

  for(int i=0;i<GRAMMAR_SIZE;i++){
		NON_TERMINAL index = (grammar[i]->head->data).nt_val;
		if(map[index].head==NULL){
			map[index].head = malloc(sizeof(Rule_node));
			map[index].head->rule = i;
			map[index].head->next = NULL;
			map[index].tail = map[index].head;
		}
		else{
			map[index].tail->next = malloc(sizeof(Rule_node));
			map[index].tail = map[index].tail->next;
			map[index].tail->rule = i;
			map[index].tail->next = NULL;
		}
	}

	populateArray();

	// For printing 
	/*
	for(int i=0;i<NT_SIZE;i++){
		iterateNode* curr = followMap[i].head;
		printf("NT=%d ",i+1);
		while(curr!=NULL){
			printf("%d, ",curr->rule + 1);
			curr = curr->next;
		}
		printf("\n");
	}*/

		// For printing stored grammar
  /*FILE* fp = fopen("testGrammar.txt","w");
  for(int i=0;i<GRAMMAR_SIZE;i++){
        node* curr = grammar[i]->head;
        fprintf(fp,"%s ", convert2(curr->data,curr->tag));
        curr = curr->next;
        while(curr!=NULL){
            fprintf(fp,"%s ", convert2(curr->data,curr->tag));
            curr = curr->next;
        }

        fprintf(fp,"\n");
    }*/
   
 for(int i=0;i<NT_SIZE;i++)
 	calculateFirst((NON_TERMINAL)i);
 for(int i=0;i<NT_SIZE;i++)
 	calculateFollow((NON_TERMINAL)i);

  //For first set
 /*
 Symbol s;
 printf("\n\n");
  for(int i=0;i<NT_SIZE;i++){
  	s.nt_val = (NON_TERMINAL)i;
  	printf("NT= %-25s\t First= {",convert2(s,2));
  	convertfirst(first[i]);
  	printf("}\n");
  }

  printf("\n\n");
  */

 //For follow set
 /*
 Symbol s;
 printf("\n\n");
  for(int i=0;i<NT_SIZE;i++){
  	s.nt_val = (NON_TERMINAL)i;
  	printf("NT= %-25s\t Follow= {",convert2(s,2));
  	convertfirst(follow[i]);
  	printf("}\n");
  }

  printf("\n\n");
  */
    populate_parse_table();

}