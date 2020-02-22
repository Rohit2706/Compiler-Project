#include<stdio.h>
#include<stdlib.h>

#define GRAMMAR_SIZE 104

typedef struct Node{
    char* data;
    struct Node* next;
    struct Node* prev;
}node;

typedef struct LinkedList{
    node* head;
    node* tail;
}linkedList;

linkedList* createLinkedList(){
    linkedList* lhsNode=(linkedList* )malloc(sizeof(linkedList));
    return lhsNode;
}

void addLhs(linkedList* inpLinkedList, char* inpData){
    node* lhs=(node*)malloc(sizeof(node));
    lhs->data=inpData;
    lhs->next=NULL;
    lhs->prev=NULL;
    inpLinkedList->head=lhs;
    inpLinkedList->tail=lhs;
}

void addRhs(linkedList* inpLinkedList, char* inpData){
    node* rhs=(node*)malloc(sizeof(node));
    rhs->data=inpData;
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
        // printf("%s\n",line);
        beg=0;
        end=0;
        while(line[end]!='\0' || line[end]!='\n'){

            if(line[end]==' ' || line[end]=='\0' || line[end]=='\n'){
                char* insert=(char*)malloc((end-beg)*sizeof(char));
                
                for(int i=beg;i<end;i++){
                    insert[i-beg]=line[i];    
                }
                    
                // printf("%s\n", insert);

                if(flag==0){
                    addLhs(arrLinkedList[currRow], insert);
                    flag=1;
                }
                
                else{
                    addRhs(arrLinkedList[currRow], insert);
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
        printf("%s-> ", curr->data);
        curr = curr->next;
        while(curr!=NULL){
            printf("%s ", curr->data);
            curr = curr->next;
        }

        printf("\n\n");
    }
}

