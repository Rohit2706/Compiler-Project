#include<stdlib.h>
#include<stdio.h>
#define buffer_size 50

FILE* file, *file2;
char* forward;
int status = 1;

void getStream(char* buffer){
	int size = fread(buffer, sizeof(char), buffer_size, file);
	if(size!=buffer_size)
		buffer[size] = '\0';
	forward = buffer;
	//printf("buffer=%srohit\n\n",buffer);
}

char getNextChar(char* buffer1, char* buffer2, char* lexeme, int* length){
    
    if(*forward !=EOF){
        forward++;
        lexeme[*length]=*(forward-1);
        *length++;
        return *(forward-1);
    }
    
    if(feof(file))
        return '\0';
        
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

int main(){

   	file = fopen("test_for_comments","r");
   	file2 = fopen("testfuncoutput","w");
   	
   	char ch;
   	
   	char* buffer1 = (char*) malloc((buffer_size+1)*sizeof(char));
	char* buffer2 = (char*) malloc((buffer_size+1)*sizeof(char));
	buffer1[buffer_size] = EOF;
	buffer2[buffer_size] = EOF;

	/*printf("buffer1 = %p",buffer1);
	printf("\n\n");
	printf("buffer2 = %p",buffer2);
	printf("\n\nafter***********\n\n");*/

	getStream(buffer1);

	char* lexeme = malloc(sizeof(char)*20);
	int* length = malloc(sizeof(int));
	*length = 0;
	
   	while((ch=getNextChar(buffer1, buffer2, lexeme, length))!='\0'){
   		fprintf(file2,"%c",ch);
   	}

   	free(buffer1);
   	free(buffer2);
   	free(lexeme);
   	free(length);
   	fclose(file);
   	fclose(file2);

   	return 0;
}

