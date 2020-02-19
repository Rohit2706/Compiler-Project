
void retract(char* buffer1, char* buffer2, char* lexeme, int* length, int* flag){
    
    if(forward==buffer2){
        *flag=1;
        forward= buffer1+ buffer_size-1;
        *length=*length-1;
    }
    
    else if(forward==buffer1){
        *flag=1;
        forward= buffer2+ buffer_size-1;
        *length=*length-1;
    }
    
    else{
        forward=forward-1;
        *length=*length-1;
    }
    
}


void retractBy2(char* buffer1, char* buffer2, char* lexeme, int* length, int* flag){
    if(forward==buffer2){
        *flag=1;
        forward= buffer1+ buffer_size-2;
        *length=*length-2;
    }
    
    if(forward==buffer2+1){
        *flag=1;
        forward= buffer1+ buffer_size-1;
        *length=*length-2;
    }
    
    if(forward==buffer1){
        *flag=1;
        forward= buffer2+ buffer_size-2;
        *length=*length-2;
    }
    
    if(forward==buffer1+1){
        *flag=1;
        forward= buffer2+ buffer_size-1;
        *length=*length-2;
    }
    
    else{
        forward=forward-2;
        *length=*length-2;
    }
}



char getNextChar(char* buffer1, char* buffer2, char* lexeme, int* length, int* flag){
    
    if(*forward !=EOF){
        forward++;
        lexeme[*length]=*(forward-1);
        *length++;
        return *(forward-1);
    }
    
    else{
        if(feof(file))
            return '\0';
        
        if(*flag==1){
            *flag=0;
            if(forward==buffer1+buffer_size){
                forward=buffer2;
                forward++;
                return *(forward-1);
            }
            else if(forward==buffer2+buffer_size){
                forward=buffer1;
                forward++;
                return *(forward-1);
            }
        }
            
        if(status==1){
            getStream(buffer2);
        }
        else{
            getStream(buffer1);
        }
        
        status = status^1;
    
        forward++;
        lexeme[*length]=*(forward-1);
        *length++;
        return *(forward-1);
    }
}
