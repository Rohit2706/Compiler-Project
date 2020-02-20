#include<stdlib.h>
#include<stdio.h>
#define buffer_size 5
#include<string.h>
#include "lexer.h"

const char* convert(TOKEN sym){
    switch(sym)
    {
        case PLUS: return "PLUS" ; break;
        case MINUS: return "MINUS" ; break;
        case MUL: return "MUL" ; break;
        case DIV: return "DIV" ; break;
        case LT: return "LT" ; break;
        case LE: return "LE" ; break;
        case GE: return "GE" ; break;
        case GT: return "GT" ; break;
        case EQ: return "EQ" ; break;
        case NE: return "NE" ; break;
        case DEF: return "DEF" ; break;
        case ENDDEF: return "ENDDEF" ; break;
        case DRIVERDEF: return "DRIVERDEF" ; break;
        case DRIVERENDDEF: return "DRIVERENDDEF" ; break;
        case COLON: return "COLON" ; break;
        case RANGEOP: return "RANGEOP" ; break;
        case SEMICOL: return "SEMICOL" ; break;
        case COMMA: return "COMMA" ; break;
        case ASSIGNOP: return "ASSIGNOP" ; break;
        case SQBO: return "SQBO" ; break;
        case SQBC: return "SQBC" ; break;
        case BO: return "BO" ; break;
        case BC: return "BC" ; break;
        case ID: return "ID" ; break;
        case NUM: return "NUM" ; break;
        case RNUM: return "RNUM" ; break;
        case ERROR: return "ERROR" ; break;

    }
}

FILE* file;
char* forward;
int status = 1;
int line_count = 1;
int *flag;


void getStream(char* buffer){
	int size = fread(buffer, sizeof(char), buffer_size, file);
	if(size!=buffer_size)
		buffer[size] = '\0';
	forward = buffer;
}

TokenInfo failure(TokenInfo newToken, char ch){
  if(ch=='\0')
    return tokenGen(newToken, SUCCESS);
  return tokenGen(newToken, ERROR);
}

char getNextChar(char* buffer1, char* buffer2, char* lexeme, int* length){
    
  if(*forward !=EOF){
      forward++;
      lexeme[*length]=*(forward-1);
      (*length)++;
      return *(forward-1);
  }
  
  if(feof(file))
      return '\0';
  
  if(*flag==1){
      *flag=0;
      if(forward==buffer1+buffer_size){
          forward=buffer2;
          forward++;
          lexeme[*length]=*(forward-1);
          (*length)++;
          return *(forward-1);
      }
      else if(forward==buffer2+buffer_size){
          forward=buffer1;
          forward++;
          lexeme[*length]=*(forward-1);
          (*length)++;
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
  (*length)++;
  return *(forward-1);
}

int main(){

 	file = fopen("t1.txt","r");
  int x = 0;
 	char ch;
 	flag=&x;
 	char* buffer1 = (char*) malloc((buffer_size+1)*sizeof(char));
	char* buffer2 = (char*) malloc((buffer_size+1)*sizeof(char));
	buffer1[buffer_size] = EOF;
	buffer2[buffer_size] = EOF;

	getStream(buffer1);
  /*comment1
	char* lexeme = malloc(sizeof(char)*20);
	int* length = malloc(sizeof(int));
	*length = 0;
	
 	while((ch=getNextChar(buffer1, buffer2, lexeme, length))!='\0'){
 		printf("%c",ch);
 	}*/

  TokenInfo mytoken;
  while((mytoken = getNextToken(buffer1, buffer2)).token!= SUCCESS){ //&& mytoken.line_no<24){
    printf("Token:%s\t\tLexeme:%-15sLine:%d\t",convert(mytoken.token),mytoken.lexeme,mytoken.line_no);
    if(mytoken.tag==1)
      printf("Value: %d\n",mytoken.value.num_value);
    else if(mytoken.tag==2)
       printf("Value: %f\n",mytoken.value.rnum_value);
     else
       printf("Value: None\n");//,mytoken.value.num_value);
  }

  //printf("%d",  line_count);
 	fclose(file);
  free(buffer1);
  free(buffer2);
  /*comment1
  free(lexeme);
  free(length);
  */
  return 0;
}

void retract(char* buffer1, char* buffer2, char* lexeme, int* length){
    
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

TOKEN search_keyword(char* lexeme){
  return ID;
}
TokenInfo tokenGen(TokenInfo newToken, TOKEN token_name){
    newToken.lexeme[newToken.length] = '\0';
    newToken.token = token_name;
    newToken.line_no = line_count;

    if(token_name == NUM){
      (newToken.value).num_value = atoi(newToken.lexeme);
      newToken.tag = 1;
    }
    else if(token_name == RNUM){
      (newToken.value).rnum_value = atof(newToken.lexeme);
      newToken.tag = 2;
    }

    return newToken;
}

TokenInfo getNextToken(char* buffer1, char* buffer2){
  TokenInfo newToken;
  newToken.length = 0;
  newToken.tag=0;
  int start = 0;
  char c;
  int* state = &start;

  while(1){
    switch(*state){
    case 0:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));

        if((c>='a' && c<='z') || (c>='A' && c<='Z')) *state=1;
        else if(c==';') *state=3;
        else if(c>='0' && c<='9') *state=4;
        else if(c=='.') *state=12;
        else if(c=='*') *state=14;
        else if(c=='/') *state=19;
        else if(c==',') *state=20;
        else if(c=='[') *state=21;
        else if(c==']') *state=22;
        else if(c=='=') *state=23;
        else if(c=='!') *state=25;
        else if(c=='(') *state=27;
        else if(c==')') *state=28;
        else if(c=='<') *state=29;
        else if(c=='>') *state=33;
        else if(c==':') *state=37;
        else if(c=='+') *state=40;
        else if(c=='-') *state=41;
        else if(c==' ' || c=='\r' || c=='\t'){ 
          *state=0;
          newToken.length--;
        }
        else if(c=='\n'){ 
          *state=42;
          newToken.length--;
        }
        else{
          return failure(newToken, c);
        }
        break;
    
    case 1:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_') *state=1;
        else    *state=2;

        break;
    
    case 2:
        retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, search_keyword(newToken.lexeme));

        break;
    
    case 3:
        return tokenGen(newToken, SEMICOL);

        break;
    
    case 4:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=4;
        else if(c=='.') *state=5;
        else *state=11;
        break;
    
    case 5:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=6;
        else if(c=='.'){
            retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
            retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
            return tokenGen(newToken, NUM);
        }
        else{
          retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
        
    case 6:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=6;
        else if(c=='E' || c=='e')   *state=7;
        else *state=10;

        break;
    
    case 7:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=9;
        else if(c=='+' || c=='-')   *state=8;
        else{
          retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
        
    case 8:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=9;
        else{
          retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
    
    case 9:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=9;
        else *state=10;

        break;
    
    case 10:
        retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, RNUM);

        break;
    
    case 11:
        retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, NUM);  

        break;
        
    case 12:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='.')  *state=13;
        else{
          retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;

    case 13:
        return tokenGen(newToken, RANGEOP);

        break;
    
    case 14:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='*'){
          *state=15;
          newToken.length -= 2;
        }
        else *state=18;

        break;
        
    case 15:
          c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
         if(c=='*')    *state=16;
         else if(c=='\n'){
            line_count++;
            *state=43;
          }
         else{ 
            *state=15;
            
         }
         newToken.length--;
         break;
    
    case 16:
         c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
         if(c=='*'){
            *state=17;
         }
         else if(c=='\n'){
             line_count++;
             *state=43;
             
         }
         else *state=15;
          newToken.length--;
         break;
    
    case 17:
         *state=0;
         break; 

    case 18:
        retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, MUL);

        break;
    
    case 19:
        return tokenGen(newToken, DIV);
        break;
    
    case 20:
        return tokenGen(newToken, COMMA);
        break; 
        
    case 21:
        return tokenGen(newToken, SQBO);
        break; 
        
    case 22:
        return tokenGen(newToken, SQBC);
        break; 
    
    case 23:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='=')  *state=24;
        else{
          retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
    
    case 24:
        return tokenGen(newToken, EQ);
        break;
    
    case 25:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='=')  *state=26;
        else{
          retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
    
    case 26:
        return tokenGen(newToken, NE);
        break; 
        
    case 27:
        return tokenGen(newToken, BO);
        break; 
        
    case 28:
        return tokenGen(newToken, BC);
        break; 
        
    case 29:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='<')  *state=30;
        else if(c=='=') *state=31;
        else    *state=32;
        break;
    
    case 30:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='<')  *state = 44;
        else  *state = 45;
        break; 
    
    case 31:
        return tokenGen(newToken, LE);
        break; 
        
    case 32:
        retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, LT);
        break; 
    
    case 33:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='>')  *state=34;
        else if(c=='=') *state=35;
        else    *state=36;
        break; 
    
    case 34:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='>')  *state=46;
        else *state=47;
        break; 
    
    case 35:
        return tokenGen(newToken, GE);
        break; 
        
    case 36:
        retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, GT);
        break; 
        
    case 37:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='=')  *state=38;
        else    *state=39;
        break; 
    
    case 38:
        return tokenGen(newToken, ASSIGNOP);
        break; 
        
    case 39:
        retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, COLON);
        break; 
    
    case 40:
        return tokenGen(newToken, PLUS);
        break; 
    
    case 41:
        return tokenGen(newToken, MINUS);
        break;   
    
    case 42:
        line_count++;
        *state=0;

        break;

    case 43:
        c=getNextChar(buffer1, buffer2, newToken.lexeme, &(newToken.length));
        if(c=='\n'){
          line_count++;
          *state=43;
        }
        else if(c=='*') *state = 16;
        else *state=15;
        newToken.length--;
        break;

    case 44:
      return tokenGen(newToken, DRIVERDEF);
      break; 

    case 45:
      retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
      return tokenGen(newToken, DEF);

      break;

    case 46:
      return tokenGen(newToken, DRIVERENDDEF);
      break;

    case 47:
      retract(buffer1, buffer2, newToken.lexeme, &(newToken.length));
      return tokenGen(newToken, ENDDEF);

      break;
  }
}
}