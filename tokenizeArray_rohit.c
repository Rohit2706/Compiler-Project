#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HASH_SIZE 91
#define INT_MAX 2147483647

typedef enum{INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
             WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM, EPSILON, DOLLAR
             } TOKEN;

typedef enum{PROGRAM_NT,MODULEDECLARATIONS,MODULEDECLARATION,OTHERMODULES,DRIVERMODULE,MODULE_NT,RET,INPUT_PLIST,
             INPUT_PLIST_1,OUTPUT_PLIST,OUTPUT_PLIST_1,DATATYPE,TYPE,MODULEDEF,STATEMENTS,STATEMENT,IOSTMT,VAR,
             VAR_ID_NUM,BOOLCONSTT,WHICHID,SIMPLESTMT,ASSIGNMENTSTMT,WHICHSTMT,LVALUEIDSTMT,LVALUEARRSTMT,INDEX,
             MODULEREUSESTMT,OPTIONAL,IDLIST,IDLIST_1,EXPRESSION,U,U_1,ARMORBOOL,N7,ANYTERM,N8,ARITHMETICEXPR,
             ARITHMETICEXPR_1,TERM,TERM_1,FACTOR,OP1,OP2,LOGICALOP,RELATIONALOP,DECLARESTMT,CONDITIONALSTMT,CASESTMT,
             CASESTMT_1,VALUE,DEFAULT_NT,ITERATIVESTMT,RANGE_ARRAYS,RANGE} NON_TERMINAL;


typedef union symbol{

    NON_TERMINAL nt_val;
    TOKEN t_val;
}Symbol;

typedef struct Datapair {
   char* key;   
   Symbol value;
   int tag;
   struct Datapair *next;
}Datapair;

// hashtable is a data structure containing all the Datapairs 
typedef struct {
    int size;
    Datapair **table;
}hashtable;




int gtag = 0;
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
Datapair* create_pair_terminal(char* key, TOKEN val){

    Datapair *newpair = malloc(sizeof(Datapair));
    newpair->value.t_val = val;
    newpair->key = strdup(key);
    newpair->tag = 1;
    return newpair;
}

Datapair* create_pair_nonterminal(char* key, NON_TERMINAL val){

    Datapair *newpair = malloc(sizeof(Datapair));
    newpair->value.nt_val = val;
    newpair->key = strdup(key);
    newpair->tag = 2;
    return newpair;
}

// 4. To insert an entry in the hashtable
void insert_entry_terminal(hashtable *ht, char* key, TOKEN val){

    
    int hashval =hash_func(ht,key);

    Datapair *end=NULL;
    Datapair *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair *newpair = create_pair_terminal(key,val);

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

void insert_entry_nonterminal(hashtable *ht, char* key, NON_TERMINAL val){

    
    int hashval =hash_func(ht,key);

    Datapair *end=NULL;
    Datapair *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair *newpair = create_pair_nonterminal(key,val);

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
Symbol get_value2(hashtable *ht,char* key){

    Datapair* pair = NULL;
    int hashvalue =hash_func(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

    gtag = pair->tag;
    return pair->value;
    
}


void add_terminals(hashtale *ht){
    insert_entry2_terminal(ht,"PLUS",PLUS);
    insert_entry2_terminal(ht,"MINUS",MINUS);
    insert_entry2_terminal(ht,"MUL",MUL);
    insert_entry2_terminal(ht,"DIV",DIV);
    insert_entry2_terminal(ht,"LT",LT);
    insert_entry2_terminal(ht,"LE",LE);
    insert_entry2_terminal(ht,"GE",GE);
    insert_entry2_terminal(ht,"GT",GT);
    insert_entry2_terminal(ht,"EQ",EQ);
    insert_entry2_terminal(ht,"NE",NE);
    insert_entry2_terminal(ht,"DRIVERDEF",DRIVERDEF);
    insert_entry2_terminal(ht,"DRIVERENDDEF",DRIVERENDDEF);
    insert_entry2_terminal(ht,"DEF",DEF);
    insert_entry2_terminal(ht,"ENDDEF",ENDDEF);
    insert_entry2_terminal(ht,"COLON",COLON);
    insert_entry2_terminal(ht,"RANGEOP",RANGEOP);
    insert_entry2_terminal(ht,"SEMICOL",SEMICOL);
    insert_entry2_terminal(ht,"COMMA",COMMA);
    insert_entry2_terminal(ht,"ASSIGNOP",ASSIGNOP);
    insert_entry2_terminal(ht,"SQBO",SQBO);
    insert_entry2_terminal(ht,"SQBC",SQBC);
    insert_entry2_terminal(ht,"BO",BO);
    insert_entry2_terminal(ht,"BC",BC);
    insert_entry2_terminal(ht,"ID",ID);
    insert_entry2_terminal(ht,"NUM",NUM);
    insert_entry2_terminal(ht,"RNUM",RNUM);
    insert_entry2_terminal(ht,"EPSILON",EPSILON);
    insert_entry2_terminal(ht,"DOLLAR",DOLLAR);
    insert_entry2_terminal(ht,"integer",INTEGER);
    insert_entry2_terminal(ht,"real",REAL);
    insert_entry2_terminal(ht,"boolean",BOOLEAN);
    insert_entry2_terminal(ht,"of",OF);
    insert_entry2_terminal(ht,"array",ARRAY);
    insert_entry2_terminal(ht,"start",START);
    insert_entry2_terminal(ht,"end",END);
    insert_entry2_terminal(ht,"declare",DECLARE);
    insert_entry2_terminal(ht,"module",MODULE);
    insert_entry2_terminal(ht,"driver",DRIVER);
    insert_entry2_terminal(ht,"program",PROGRAM);
    insert_entry2_terminal(ht,"get_value",GET_VALUE);
    insert_entry2_terminal(ht,"print",PRINT);
    insert_entry2_terminal(ht,"use",USE);
    insert_entry2_terminal(ht,"with",WITH);
    insert_entry2_terminal(ht,"parameters",PARAMETERS);
    insert_entry2_terminal(ht,"true",TRUE);
    insert_entry2_terminal(ht,"false",FALSE);
    insert_entry2_terminal(ht,"takes",TAKES);
    insert_entry2_terminal(ht,"input",INPUT);
    insert_entry2_terminal(ht,"returns",RETURNS);
    insert_entry2_terminal(ht,"AND",AND);
    insert_entry2_terminal(ht,"OR",OR);
    insert_entry2_terminal(ht,"for",FOR);
    insert_entry2_terminal(ht,"in",IN);
    insert_entry2_terminal(ht,"switch",SWITCH);
    insert_entry2_terminal(ht,"case",CASE);
    insert_entry2_terminal(ht,"break",BREAK);
    insert_entry2_terminal(ht,"default",DEFAULT);
    insert_entry2_terminal(ht,"while",WHILE);
}


void add_nonterminals(hastable *ht){

     insert_entry2_nonterminal(ht,"program",PROGRAM_NT);
     insert_entry2_nonterminal(ht,"moduleDeclarations",MODULEDECLARATIONS);
     insert_entry2_nonterminal(ht,"moduleDeclaration",MODULEDECLARATION);
     insert_entry2_nonterminal(ht,"otherModules",OTHERMODULES);
     insert_entry2_nonterminal(ht,"driverModule",DRIVERMODULE);
     insert_entry2_nonterminal(ht,"module",MODULE_NT);
     insert_entry2_nonterminal(ht,"ret",RET);
     insert_entry2_nonterminal(ht,"input_plist",INPUT_PLIST);
     insert_entry2_nonterminal(ht,"input_plist_1",INPUT_PLIST_1);
     insert_entry2_nonterminal(ht,"output_plist",OUTPUT_PLIST);
     insert_entry2_nonterminal(ht,"output_plist_1",OUTPUT_PLIST_1);
     insert_entry2_nonterminal(ht,"dataType",DATATYPE);
     insert_entry2_nonterminal(ht,"type",TYPE);
     insert_entry2_nonterminal(ht,"moduleDef",MODULEDEF);
     insert_entry2_nonterminal(ht,"statements",STATEMENTS);
     insert_entry2_nonterminal(ht,"statement",STATEMENT);
     insert_entry2_nonterminal(ht,"ioStmt",IOSTMT);
     insert_entry2_nonterminal(ht,"var",VAR);
     insert_entry2_nonterminal(ht,"var_id_num",VAR_ID_NUM);
     insert_entry2_nonterminal(ht,"boolConstt",BOOLCONSTT);
     insert_entry2_nonterminal(ht,"whichId",WHICHID);
     insert_entry2_nonterminal(ht,"simpleStmt",SIMPLESTMT);
     insert_entry2_nonterminal(ht,"assignmentStmt",ASSIGNMENTSTMT);
     insert_entry2_nonterminal(ht,"whichStmt",WHICHSTMT);
     insert_entry2_nonterminal(ht,"lvalueIDStmt",LVALUEIDSTMT);
     insert_entry2_nonterminal(ht,"lvalueARRStmt",LVALUEARRSTMT);
     insert_entry2_nonterminal(ht,"index",INDEX);
     insert_entry2_nonterminal(ht,"moduleReuseStmt",MODULEREUSESTMT);
     insert_entry2_nonterminal(ht,"optional",OPTIONAL);
     insert_entry2_nonterminal(ht,"idList",IDLIST);
     insert_entry2_nonterminal(ht,"idList_1",IDLIST_1);
     insert_entry2_nonterminal(ht,"expression",EXPRESSION);
     insert_entry2_nonterminal(ht,"U",U);
     insert_entry2_nonterminal(ht,"U_1",U_1);
     insert_entry2_nonterminal(ht,"armOrbool",ARMORBOOL);
     insert_entry2_nonterminal(ht,"N7",N7);
     insert_entry2_nonterminal(ht,"AnyTerm",ANYTERM);
     insert_entry2_nonterminal(ht,"N8",N8);
     insert_entry2_nonterminal(ht,"arithmeticExpr",ARITHMETICEXPR);
     insert_entry2_nonterminal(ht,"arithmeticExpr_1",ARITHMETICEXPR_1);
     insert_entry2_nonterminal(ht,"term",TERM);
     insert_entry2_nonterminal(ht,"term_1",TERM_1);
     insert_entry2_nonterminal(ht,"factor",FACTOR);
     insert_entry2_nonterminal(ht,"op1",OP1);
     insert_entry2_nonterminal(ht,"op2",OP2);
     insert_entry2_nonterminal(ht,"logicalOp",LOGICALOP);
     insert_entry2_nonterminal(ht,"relationalOp",RELATIONALOP);
     insert_entry2_nonterminal(ht,"declareStmt",DECLARESTMT);
     insert_entry2_nonterminal(ht,"conditionalStmt",CONDITIONALSTMT);
     insert_entry2_nonterminal(ht,"caseStmt",CASESTMT);
     insert_entry2_nonterminal(ht,"caseStmt_1",CASESTMT_1);
     insert_entry2_nonterminal(ht,"value",VALUE);
     insert_entry2_nonterminal(ht,"default",DEFAULT_NT);
     insert_entry2_nonterminal(ht,"iterativeStmt",ITERATIVESTMT);
     insert_entry2_nonterminal(ht,"range_arrays",RANGE_ARRAYS);
     insert_entry2_nonterminal(ht,"range",RANGE);

}

const char* convert(Symbol sym){
    if(gtag==2)
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
        default: return "UNRECOGNIZED TOKEN"; break;
    }
}

int main(){(HASH_SIZE);
    add_terminals(ht);   
    add_nonterminals(ht);
    // Some Test Cases (Note that it will print ID for the keys that are not keywords)
    printf("\n");
    printf("Input: integer  \tTOKEN: %s\n",convert(get_value2(ht,"integer")));
    printf("Input: range    \tTOKEN: %s\n",convert(get_value2(ht,"range")));
    printf("Input: SWITCH   \tTOKEN: %s\n",convert(get_value2(ht,"switch")));
    printf("Input: compiler \tTOKEN: %s\n",convert(get_value2(ht,"for")));
    printf("Input: get_value\tTOKEN: %s\n",convert(get_value2(ht,"program")));
    printf("Input: term_1   \tTOKEN: %s\n",convert(get_value2(ht,"term_1")));
    printf("\n");

    // Free memory

    for(int i=0;i<HASH_SIZE;i++)
        free(ht->table[i]);
    free(ht->table);
    free(ht);
    
}















/*
typedef struct Node{
    SYMBOL data;
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

void addLhs(linkedList* inpLinkedList, SYMBOL inpData, int inpTag){
    node* lhs=(node*)malloc(sizeof(node));
    lhs->data=inpData;
    lhs->tag=inpTag;
    lhs->next=NULL;
    lhs->prev=NULL;
    inpLinkedList->head=lhs;
    inpLinkedList->tail=lhs;
}

void addRhs(linkedList* inpLinkedList, SYMBOL inpData, int inpTag){
    node* rhs=(node*)malloc(sizeof(node));
    rhs->data=inpData;
    rhs->tag=inpTag;
    rhs->next=NULL;
    rhs->prev=inpLinkedList->tail;
    inpLinkedList->tail->next=rhs;
    inpLinkedList->tail=rhs;

}


void readIntoArr(FILE* grammarRules, linkedList** arrLinkedList){
    
    hashtable1* ht1=hashtable_create1(57);
    add_keywords1(ht1);

    hashtable* ht2=hashtable_create(57);
    add_keywords2(ht2);

    char line[1000]={'#'};
    int flag=0;
    int currRow=0;
    
    int beg=0;
    int end=0;
    
    while(fgets(line,sizeof(line),grammarRules) != NULL){
        printf("%s\n",line);
        beg=0;
        end=0;
        while(line[end]!='\0' || line[end]!='\n'){
            printf("end is %d\n",end);
            printf("beg is %d\n",beg);

            if(line[end]==' ' || line[end]=='\0' || line[end]=='\n'){
                // printf("in comparison \n");
                char* insert=(char*)malloc((end-beg)*sizeof(char))+1;
                
                for(int i=beg;i<end;i++){
                    insert[i-beg]=line[i];    
                }
                insert[end-beg]='\0';    

                printf("%s\n", insert);
                
                int tag=0;
                NON_TERMINAL xyz;
                SYMBOL insertToken;

                insertToken.non_term=get_value1(ht1,insert);

                printf("yes%d\n", insertToken.non_term);

                int i=insertToken.non_term;
                printf("%d\n", i);

                if(i==0){
                    printf("in here\n");
                    insertToken.term=get_value2(ht2,insert);
                    tag=1;
                }


                printf("insert token is %d\n",insertToken);

                if(flag==0){
                    addLhs(arrLinkedList[currRow], insertToken,tag);
                    flag=1;
                }
                
                else{
                    addRhs(arrLinkedList[currRow], insertToken,tag);
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






int main(){


    FILE* grammarFile= fopen("C:\\Users\\admin\\Desktop\\grammarRules.txt","r");

    if (grammarFile == NULL) {
        printf("Hakuna matata \n");
        return 1;
    }

    linkedList* arrLinkedList[1000];
    for(int i=0;i<1000;i++){
        arrLinkedList[i] = createLinkedList();
    }
    // addLhs(arrLinkedList[0], "abc");
    // printf("%s\n", arrLinkedList[0]->head->data);
    printf("here at least\n");
    readIntoArr(grammarFile, arrLinkedList);

    // for(int i=0;i<12;i++){
    //     node* temp=arrLinkedList[i]->head;
    //     while(temp!=NULL){
    //         printf("%s ",temp->data);
    //         temp=temp->next;
    //     }
    //     printf("\n");
    // }


}
*/