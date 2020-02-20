
typedef stuct Stack{
    int capacity;
    int pos;
    char* elem;
}stack;

stack* makeStack(int inpCapacity){
    stack* res=(stack*)malloc(sizeof(stack));
    res->capacity=inpCapacity;
    res->pos=-1;
    res->elem=(char*)malloc(sizeof(char`)*inpCapacity);
}

void push(stack* inpStack, char pushElem){
    if(inpStack->pos<inpStack->capacity-1){
        inpStack->pos++;
        inpStack->elem[inpStack->pos]=pushElem;
    }
    
    else{
        return;
    }
    
}

char pop(stack* inpStack){
    if(inpStack->pos==-1){
        return '#';
    }
    
    else{
        inpStack->pos--;
        return inpStack->elem[inpStack->pos+1];
    }
    
}


int size(stack* inpStack){
    return inpStack->pos+1;
}

