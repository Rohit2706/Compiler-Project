
// getNextChar
// retract         
// tokenGen
// searchID
// line_num++
// replace LETTER and DIGIT
// retractBy2
// failure()

switch(state){
    case 0:
        c=getNextChar();
        if(c==LETTER)  state=1;
        else if(c==';') state=3;
        else if(c==DIGIT) state=4;
        else if(c=='.') state=12;
        else if(c=='*') state=14;
        else if(c=='/') state=19;
        else if(c==',') state=20;
        else if(c=='[') state=21;
        else if(c==']') state=22;
        else if(c=='=') state=23;
        else if(c=='!') state=25;
        else if(c=='(') state=27;
        else if(c==')') state=28;
        else if(c=='<') state=29;
        else if(c=='>') state=33;
        else if(c==':') state=37;
        else if(c=='+') state=40;
        else if(c=='-') state=41;
        else if(c==" ") state=0;
        else if(c=="\n"){
            line_num++;
            state=0;
        }
        break;
    
    case 1:
        c=getNextChar();
        if(c==LETTER || DIGIT || '_') state=1;
        else    state=2;
        break;
    
    case 2:
        retract();
        tokenGen(searchID);
        break;
    
    case 3:
        tokenGen(SEMICOL);
        break;
    
    case 4:
        c=getNextChar();
        if(c==DIGIT)    state=4;
        else if(c=='.') state=5;
        else state=11;
        break;
    
    case 5:
        c=getNextChar();
        if(c==DIGIT)    state=6;
        else if(c=='.'){
            retractBy2();
            tokenGen(NUM);
        }
        else    failure();
        break;
        
    case 6:
        c=getNextChar();
        if(c==DIGIT)    state=6;
        else if(c=='E' || c=='e')   state=7;
        else state=10;
        break;
    
    case 7:
        c=getNextChar();
        if(c==DIGIT)    state=9;
        else if(c=='+' || c=='-')   state=8;
        else failure();
        break;
        
    case 8:
        c=getNextChar();
        if(c==DIGIT)    state=9;
        else failure();
        break;
    
    case 9:
        c=getNextChar();
        if(c==DIGIT)    state=9;
        else state=10;
        break;
    
    case 10:
        retract();
        tokenGen(RNUM);
    
    case 11:
        retract();
        tokenGen(NUM);  
        
    case 12:
        c=getNextChar();
        if(c=='.')  state=13;
        else    failure();
    
    case 13:
        tokenGen(RANGEOP);
    
    case 14:
        c=getNextChar();
        if(c=='*')    state=15;
        else state=18;
        
    // case 15:
    //     c=getNextChar();
    //     if(c=='*')    state=16;
    //     else if(c=='\n'){
    //         line_num++;
    //         state=48;
    //     }
    //     else state=15;
    
    // case 16:
    //     c=getNextChar();
    //     if(c=='*')    state=17;
    //     else if(c=='\n'){
    //         line_num++;
    //         state=48;
    //     }
    //     else state=15;
    
    case 18:
        retract();
        tokenGen(MUL);
        break;
    
    case 19:
        tokenGen(DIV);
        break;
    
    case 20:
        tokenGen(COMMA);
        break; 
        
    case 21:
        tokenGen(SQBO);
        break; 
        
    case 22:
        tokenGen(SQBC);
        break; 
    
    case 23:
        c=getNextChar();
        if(c=='=')  state=24;
        else failure();
        break;
    
    case 24:
        tokenGen(EQ);
        break;
    
    case 25:
        c=getNextChar();
        if(c=='=')  state=26;
        else failure();
        break;
    
    case 26:
        tokenGen(NE);
        break; 
        
    case 20:
        tokenGen(COMMA);
        break; 
        
    case 27:
        tokenGen(BO);
        break; 
        
    case 28:
        tokenGen(BC);
        break; 
        
    case 29:
        c=getNextChar();
        if(c=='<')  state=30;
        else if(c=='=') state=31;
        else    state=32;
        break;
    
    case 30:
        tokenGen(DEF);
        break; 
    
    case 31:
        tokenGen(LE);
        break; 
        
    case 32:
        retract();
        tokenGen(LT);
        break; 
    
    case 33:
        c=getNextChar();
        if(c=='>')  state=34;
        else if(c=='=') state=35;
        else    state=36;
        break; 
    
    case 34:
        tokenGen(ENDDEF);
        break; 
    
    case 35:
        tokenGen(GE);
        break; 
        
    case 36:
        retract();
        tokenGen(GT);
        break; 
        
    case 37:
        c=getNextChar();
        if(c=='=')  state=38;
        else    state=39;
        break; 
    
    case 38:
        tokenGen(ASSIGNOP);
        break; 
        
    case 39:
        retract();
        tokenGen(COLON);
        break; 
    
    case 40:
        tokenGen(PLUS);
        break; 
    
    case 41:
        tokenGen(MINUS);
        break;   
    
    
}
