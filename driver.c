//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "ast.h"
int main(int args, char* argv[])
{
    int choice;
    tree_node* ast;
    FILE* fp;
    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;
    printf("\n");
    printf("LEVEL 4: Symbol Table/Type Checking/Semantic Rules Modules Work/Handled Static and Dynamic Arrays in Type Checking and code generation\n\n");
   
    printf("Displaying the menu with options:\n\n");
    
    do{
        printf("1. Print the list of tokens, as generated by the lexer on console \n");
        printf("2. Print all the syntactic errors on console and print the parse tree (inorder) on the console \n");
        printf("3. Travel the AST (inorder traversal) and print on the console \n");
        printf("4. Display the amount of allocated memory and number of nodes to each ParseTree and AST \n");
        printf("5. Print the Symbol Table \n");
        printf("6. Print the total memory requirement for each function \n");
        printf("7. Print the type expressions and width of array variables \n");
        printf("8. Print the syntactic and semantic errors (if any) and print the total time taken by the compiler \n");
        printf("9. Generate assembly code \n");
        printf("Enter 0 to exit.\n\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 0: exit(0);
            case 1: printTokens(argv[1]);
                    break;
            case 2: run_lexer_parser(argv[1],1,1);
                    break;
            case 3: ast_driver(argv[1],1,0,0,0,0,0,0,NULL);
                    break;
            case 4: ast_driver(argv[1],0,0,1,0,0,0,0,NULL);
                    break;
            case 5: ast_driver(argv[1],0,1,0,1,0,0,0,NULL);
                    break;

            case 6: ast_driver(argv[1],0,1,0,0,1,0,0,NULL);
                    break;

            case 7: ast_driver(argv[1],0,1,0,0,0,1,0,NULL);
                    break;

            case 8: start_time = clock();
                    ast_driver(argv[1],0,1,0,0,0,0,0,NULL);
                    end_time = clock();
                    printf("\n");
                    total_CPU_time = (double) (end_time - start_time);
                    total_CPU_time_in_seconds = total_CPU_time/CLOCKS_PER_SEC;
                    printf("Total time taken by CPU: %lf\n",total_CPU_time);
                    printf("Total time taken by CPU in seconds: %lf\n",total_CPU_time_in_seconds);
                    break;

        case 9: fp = fopen(argv[2],"w");
                if(fp==NULL)
                    printf("NASM CODE DESTINATION FILE NOT FOUND\n");
                ast = ast_driver(argv[1],0,1,0,0,0,0,1,fp);
                printf("\n");
                printf("Run the following command for code generation using NASM 64-bit:\n\n");
                printf("\t\t\t\t\tnasm -f elf64 code.asm && gcc -g -no-pie code.o && ./a.out\n\n");
                printf("\n");
                generateAssembly(ast,fp);
                fclose(fp);
                break;

            default: printf("Wrong choice entered, try again\n");
        }
    }while(1);
    
    return 0;
}