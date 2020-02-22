
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define HASH_SIZE 57

// typedef enum {PROGRAM,MODULEDECLARATIONS,MODULEDECLARATION,OTHERMODULES,DRIVERMODULE,MODULE,RET,INPUT_PLIST,INPUT_PLIST_1,OUTPUT_PLIST,OUTPUT_PLIST_1,DATATYPE,TYPE,MODULEDEF,STATEMENTS,STATEMENT,IOSTMT,VAR,VAR_ID_NUM,BOOLCONSTT,WHICHID,SIMPLESTMT,ASSIGNMENTSTMT,WHICHSTMT,LVALUEIDSTMT,LVALUEARRSTMT,INDEX,MODULEREUSESTMT,OPTIONAL,IDLIST,IDLIST_1,EXPRESSION,U,U_1,ARMORBOOL,N7,ANYTERM,N8,ARITHMETICEXPR,ARITHMETICEXPR_1,TERM,TERM_1,FACTOR,OP1,OP2,LOGICALOP,RELATIONALOP,DECLARESTMT,CONDITIONALSTMT,CASESTMT,CASESTMT_1,VALUE,DEFAULT,ITERATIVESTMT,RANGE_ARRAYS,RANGE} TOKEN;
typedef enum{INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
             WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM, EPSILON, DOLLAR
             } TOKEN;


// Datapair2 is a structure that stores the key-value pair
typedef struct Datapair2 {
   char* key;   
   TOKEN value;
   struct Datapair2 *next;
}Datapair2;

// hashtable2 is a data structure containing all the Datapairs 
typedef struct {
    int size;
    Datapair2 **table;
}hashtable2;

// Function prototypes

hashtable2* hashtable_create2(int size);
int hash_func2(hashtable2 *ht, char* key );
Datapair2* create_pair2(char* key, TOKEN val);
void insert_entry2(hashtable2 *ht, char* key, TOKEN val);
TOKEN get_value2(hashtable2 *ht,char* key);
void add_keywords2(hashtable2 *ht);



// 1. To create hash table
hashtable2* hashtable_create2(int size){

    hashtable2 *newtable = (hashtable2 *)malloc(sizeof(hashtable2));
    newtable->table = (Datapair2 **)malloc(sizeof(Datapair2*) * size);

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

int hash_func2(hashtable2 *ht, char* key ){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    return (hashvalue%(ht->size));
}


// 3. to create the key-value Datapair2
Datapair2* create_pair2(char* key, TOKEN val){

    Datapair2 *newpair = malloc(sizeof(Datapair2));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

// 4. To insert an entry in the hashtable2
void insert_entry2(hashtable2 *ht, char* key, TOKEN val){

    
    int hashval =hash_func2(ht,key);

    Datapair2 *end=NULL;
    Datapair2 *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair2 *newpair = create_pair2(key,val);

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
TOKEN get_value2(hashtable2 *ht,char* key){

    Datapair2* pair = NULL;
    int hashvalue =hash_func2(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

  //   if( pair == NULL||pair->key == NULL||strcmp( key, pair->key ) != 0 ) {
        // return ID;
  //   }
    return pair->value;
    
}


void add_keywords2(hashtable2 *ht){
     insert_entry2(ht,"PLUS",PLUS);
     insert_entry2(ht,"MINUS",MINUS);
     insert_entry2(ht,"MUL",MUL);
     insert_entry2(ht,"DIV",DIV);
     insert_entry2(ht,"LT",LT);
     insert_entry2(ht,"LE",LE);
     insert_entry2(ht,"GE",GE);
     insert_entry2(ht,"GT",GT);
     insert_entry2(ht,"EQ",EQ);
     insert_entry2(ht,"NE",NE);
     insert_entry2(ht,"DRIVERDEF",DRIVERDEF);
     insert_entry2(ht,"DRIVERENDDEF",DRIVERENDDEF);
     insert_entry2(ht,"DEF",DEF);
     insert_entry2(ht,"ENDDEF",ENDDEF);
     insert_entry2(ht,"COLON",COLON);
     insert_entry2(ht,"RANGEOP",RANGEOP);
     insert_entry2(ht,"SEMICOL",SEMICOL);
     insert_entry2(ht,"COMMA",COMMA);
     insert_entry2(ht,"ASSIGNOP",ASSIGNOP);
     insert_entry2(ht,"SQBO",SQBO);
     insert_entry2(ht,"SQBC",SQBC);
     insert_entry2(ht,"BO",BO);
     insert_entry2(ht,"BC",BC);
     insert_entry2(ht,"ID",ID);
     insert_entry2(ht,"NUM",NUM);
     insert_entry2(ht,"RNUM",RNUM);
     insert_entry2(ht,"EPSILON",EPSILON);
     insert_entry2(ht,"DOLLAR",DOLLAR);


}



















typedef enum {NONE,PROGRAM_NT,MODULEDECLARATIONS,MODULEDECLARATION,OTHERMODULES,DRIVERMODULE,MODULE_NT,RET,INPUT_PLIST,INPUT_PLIST_1,OUTPUT_PLIST,OUTPUT_PLIST_1,DATATYPE,TYPE,MODULEDEF,STATEMENTS,STATEMENT,IOSTMT,VAR,VAR_ID_NUM,BOOLCONSTT,WHICHID,SIMPLESTMT,ASSIGNMENTSTMT,WHICHSTMT,LVALUEIDSTMT,LVALUEARRSTMT,INDEX,MODULEREUSESTMT,OPTIONAL,IDLIST,IDLIST_1,EXPRESSION,U,U_1,ARMORBOOL,N7,ANYTERM,N8,ARITHMETICEXPR,ARITHMETICEXPR_1,TERM,TERM_1,FACTOR,OP1,OP2,LOGICALOP,RELATIONALOP,DECLARESTMT,CONDITIONALSTMT,CASESTMT,CASESTMT_1,VALUE,DEFAULT_NT,ITERATIVESTMT,RANGE_ARRAYS,RANGE} NON_TERMINAL;



// Datapair1 is a structure that stores the key-value pair
typedef struct Datapair1 {
   char* key;   
   NON_TERMINAL value;
   struct Datapair1 *next;
}Datapair1;

// hashtable1 is a data structure containing all the Datapairs 
typedef struct {
    int size;
    Datapair1 **table;
}hashtable1;

// Function prototypes

hashtable1* hashtable_create1(int size);
int hash_func1(hashtable1 *ht, char* key );
Datapair1* create_pair1(char* key, NON_TERMINAL val);
void insert_entry1(hashtable1 *ht, char* key, NON_TERMINAL val);
NON_TERMINAL get_value1(hashtable1 *ht,char* key);
void add_keywords1(hashtable1 *ht);




// 1. To create hash table
hashtable1* hashtable_create1(int size){

    hashtable1 *newtable = (hashtable1 *)malloc(sizeof(hashtable1));
    newtable->table = (Datapair1 **)malloc(sizeof(Datapair1*) * size);

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

int hash_func1(hashtable1 *ht, char* key ){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    return (hashvalue%(ht->size));
}


// 3. to create the key-value Datapair1
Datapair1* create_pair1(char* key, NON_TERMINAL val){

    Datapair1 *newpair = malloc(sizeof(Datapair1));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

// 4. To insert an entry in the hashtable1
void insert_entry1(hashtable1 *ht, char* key, NON_TERMINAL val){

    
    int hashval =hash_func1(ht,key);

    Datapair1 *end=NULL;
    Datapair1 *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair1 *newpair = create_pair1(key,val);

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
NON_TERMINAL get_value1(hashtable1 *ht,char* key){

    Datapair1* pair = NULL;
    int hashvalue =hash_func1(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

  //   if( pair == NULL||pair->key == NULL||strcmp( key, pair->key ) != 0 ) {
        // return ID;
  //   }
    return pair->value;
    
}


void add_keywords1(hashtable1 *ht){

     insert_entry1(ht,"program",PROGRAM_NT);
     insert_entry1(ht,"moduleDeclarations",MODULEDECLARATIONS);
     insert_entry1(ht,"moduleDeclaration",MODULEDECLARATION);
     insert_entry1(ht,"otherModules",OTHERMODULES);
     insert_entry1(ht,"driverModule",DRIVERMODULE);
     insert_entry1(ht,"module",MODULE_NT);
     insert_entry1(ht,"ret",RET);
     insert_entry1(ht,"input_plist",INPUT_PLIST);
     insert_entry1(ht,"input_plist_1",INPUT_PLIST_1);
     insert_entry1(ht,"output_plist",OUTPUT_PLIST);
     insert_entry1(ht,"output_plist_1",OUTPUT_PLIST_1);
     insert_entry1(ht,"dataType",DATATYPE);
     insert_entry1(ht,"type",TYPE);
     insert_entry1(ht,"moduleDef",MODULEDEF);
     insert_entry1(ht,"statements",STATEMENTS);
     insert_entry1(ht,"statement",STATEMENT);
     insert_entry1(ht,"ioStmt",IOSTMT);
     insert_entry1(ht,"var",VAR);
     insert_entry1(ht,"var_id_num",VAR_ID_NUM);
     insert_entry1(ht,"boolConstt",BOOLCONSTT);
     insert_entry1(ht,"whichId",WHICHID);
     insert_entry1(ht,"simpleStmt",SIMPLESTMT);
     insert_entry1(ht,"assignmentStmt",ASSIGNMENTSTMT);
     insert_entry1(ht,"whichStmt",WHICHSTMT);
     insert_entry1(ht,"lvalueIDStmt",LVALUEIDSTMT);
     insert_entry1(ht,"lvalueARRStmt",LVALUEARRSTMT);
     insert_entry1(ht,"index",INDEX);
     insert_entry1(ht,"moduleReuseStmt",MODULEREUSESTMT);
     insert_entry1(ht,"optional",OPTIONAL);
     insert_entry1(ht,"idList",IDLIST);
     insert_entry1(ht,"idList_1",IDLIST_1);
     insert_entry1(ht,"expression",EXPRESSION);
     insert_entry1(ht,"U",U);
     insert_entry1(ht,"U_1",U_1);
     insert_entry1(ht,"armOrbool",ARMORBOOL);
     insert_entry1(ht,"N7",N7);
     insert_entry1(ht,"AnyTerm",ANYTERM);
     insert_entry1(ht,"N8",N8);
     insert_entry1(ht,"arithmeticExpr",ARITHMETICEXPR);
     insert_entry1(ht,"arithmeticExpr_1",ARITHMETICEXPR_1);
     insert_entry1(ht,"term",TERM);
     insert_entry1(ht,"term_1",TERM_1);
     insert_entry1(ht,"factor",FACTOR);
     insert_entry1(ht,"op1",OP1);
     insert_entry1(ht,"op2",OP2);
     insert_entry1(ht,"logicalOp",LOGICALOP);
     insert_entry1(ht,"relationalOp",RELATIONALOP);
     insert_entry1(ht,"declareStmt",DECLARESTMT);
     insert_entry1(ht,"conditionalStmt",CONDITIONALSTMT);
     insert_entry1(ht,"caseStmt",CASESTMT);
     insert_entry1(ht,"caseStmt_1",CASESTMT_1);
     insert_entry1(ht,"value",VALUE);
     insert_entry1(ht,"default",DEFAULT_NT);
     insert_entry1(ht,"iterativeStmt",ITERATIVESTMT);
     insert_entry1(ht,"range_arrays",RANGE_ARRAYS);
     insert_entry1(ht,"range",RANGE);

}


















typedef union symbol{

    NON_TERMINAL non_term;
    TOKEN term;
}SYMBOL;

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

    hashtable2* ht2=hashtable_create2(57);
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
