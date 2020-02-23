
#define STACK_CAPACITY 150

typedef struct tree_node{

    tagged_union val;
    int no_child,
    struct tree_node ** child;

}tree_node;

typedef struct Stack{

    int pos;
    int capacity = STACK_CAPACITY;
    tree_node * vals[STACK_CAPACITY];

}stack;

stack* makeStack(){
    stack* res=(stack*)malloc(sizeof(stack));
    res->capacity=STACK_CAPACITY;
    res->pos=-1;
    return res;
}

void push(stack* inpStack, tree_node* pushnode){
    
    if(inpStack->pos<inpStack->capacity){
        inpStack->pos++;
        inpStack->elem[inpStack->pos]=pushnode;
    }
    else
        return;
    
}

int size(stack* inpStack){
    return inpStack->pos+1;
}

tree_node* top(stack* inpStack){
    return (tree_node*)inpStack->elem[inpStack->pos];
}

node* pop(stack* inpStack){
    if(inpStack->pos==-1){
        return NULL;
    }
    
    else{
        inpStack->pos--;
        return (tree_node*)inpStack->elem[inpStack->pos+1];
    }
    
}

tree_node* makenode(tagged_union inputtag){
    tree_node* newnode = (tree_node*) malloc(sizeof(tree_node));
    newnode->val=inputtag;
    newnode->child=NULL;
    newnode->no_child=0;
    return newnode;
}

tree_node* addsinglenode( tree_node* head, tagged_union newtag){

    tree_node* newnode = makenode(newtag);

    head->child = realloc(head->child, (head->no_child+1)*(sizeof(node *)) );
    head->child[head->no_child] = newnode; 
    head->no_child++;

    return newnode;
}

 
void create_pt(){

    // Initialising every variable for the Parse tree
    TOKEN term;
    tagged_union  stackval;               
    stack* st = makeStack();
    stackval.tag = 2; stackval.value =  PROGRAM_NT;    
    node* Root = makenode(stackval); 
    push(st,Root);
    int rule_no;
    // End of initializing

    term = getNextToken()->token;

    do{       
        stackval = top(st)->val;
        tree_node* head = top(st);

        if(stackval.tag==1 && stackval.value == term ){
            
            pop(st);
            if(term == DOLLAR)
                break;
            term = getNextToken();
        }
        else if (stackval.tag==1 && stackval.value != term ){
            
            // HANDLE PANIC MODE ERROR
        
        }
        else {

            rule_no = lookup(term,stackval.value.nt_val);

            if(rule_no==-1){         
                // HANDLE PANIC MODE ERROR
            }
            else{

                node* temp = arrLinkedList[rule_no]->head->next;
                while(temp){
                    addsinglenode(head,temp->val);
                    temp = temp->next;
                }

                pop(st);
                for(int i= head->no_child-1;i>=0;i--){
                    push(st,head->child[i]);
                }


            }


        }
        
    }while(1)

    




}




// Just to check

int main()
{
    node* root = (node*) malloc(sizeof(node));
    // strcpy(root->val, "asdf");
    root->val = "asf";

    char * word ="ani";
    addsinglenode(word,root);
    addsinglenode(word,root);
    addsinglenode(word,root);
    addsinglenode(word,root);
    addsinglenode(word,root);

    printf("%d",root->no_child);
}


void generate_parse_tree(){

}