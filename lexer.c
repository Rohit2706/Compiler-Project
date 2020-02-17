/*To be implemented

Doc and format
removeComments stores processed string in char stream instead of printing*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void removeComments(char *testcaseFile){
  
  while((*testcaseFile)!='\0'){
    
    if(*testcaseFile=='*' && *(testcaseFile+1)=='*'){
      testcaseFile+=2;
      while(!(*testcaseFile=='*' && *(testcaseFile+1)=='*')){
      	if(*testcaseFile=='\n')
          printf("%c", *testcaseFile);
        testcaseFile++;
      }
      testcaseFile+=2;
    }
    else{
      printf("%c", *testcaseFile);
      testcaseFile++;
    } 
  }
}

char* charstream(char *s, int size)
{
  
  FILE *fp = NULL;
  char* bruh;
  fp = fopen("test_for_comments","r");
  char ch;
//      ch=getc(fp);
  int currIdx = 0;
  while((ch=getc(fp)) != EOF)
  {
//              ch=getc(fp);
//              strcat(bruh,ch,1);
          if (currIdx>=size-1) {
                  size *= 2;
                  s = (char*) realloc(s, size*sizeof(char));
          }
          s[currIdx++] = ch;
          s[currIdx] = '\0';
          //printf("/t%c", ch);
//              fp++;
  }
  fclose(fp);
  return s;
}
int main()
{
        char *s = (char *) calloc(10,sizeof(char));
        
        if (s == NULL) {
          printf("Fux\n");
          return 1;
        }
        int size = 10;
        s[0] = '\0';
        s=charstream(s, size);
        removeComments(s);
        free(s); // at the end of program
        return 0;
}