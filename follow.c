
int isKthBitSet(int n, int k) 
{ 
    if (n & (1 << (k - 1))) 
        return 1; 
    else
        return 0; 
} 


unsigned long int fillParseTableFirst(NON_TERMINAL nt){
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
        parseTable[nt][(symbol_node->data).t_val]=curr->rule;
        break;
      }
        else{
        val = calculateFirst((symbol_node->data).nt_val);

        for(int i=1;i<64;i++){
            int res=isKthBitSet(val, i);
            if(res==1){
              parseTable[nt][i]=curr->rule;
            }
        }

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
