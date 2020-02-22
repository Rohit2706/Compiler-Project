
void readIntoArr(FILE* grammarRules, linkedList** arrLinkedList){
    
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
            printf("end is %d\n",end);
            printf("beg is %d\n",beg);

            if(line[end]==' ' || line[end]=='\0' || line[end]=='\n'){
                printf("in comparison \n");
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
