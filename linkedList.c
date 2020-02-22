
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
