// Implementation of Operator Precedence Parser

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char stack[50] = "$";
char handles[][6] = {"i", "S-S", "S/S", "S*S", "S+S"};
int stackTop = 0, inputPointer = 0, stackCheckPointer = 0;

char precedenceTable[6][6] = {
        //         +    -    *    /    i    $
        /*  + */  '>', '>', '<', '<', '<', '>',

        /*  - */  '>', '>', '<', '<', '<', '>',

        /*  * */  '>', '>', '>', '>', '<', '>',

        /*  / */  '>', '>', '>', '>', '<', '>',

        /*  i */  '>', '>', '>', '>', '=', '>',

        /*  $ */  '<', '<', '<', '<', '<', '>',
};


int getIndex(char c)
{
    switch (c)
    {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case 'i':
            return 4;
        case '$':
            return 5;
    }
}


void shift(char *input)
{
    stack[++stackTop] = input[inputPointer++];
    stackCheckPointer = stackTop;
    stack[stackTop + 1] = '\0';

    printf("\t\tSHIFT");
}


bool reducer()
{
    int k, m, length;
    bool isFound = true;

    for (k=0; k<6; k++) // For selecting handles
    {
        length = strlen(handles[k]);
        if (stack[stackTop] == handles[k][length - 1] && stackTop + 1 >= length)
        {
            isFound = true;
        
            for (m=0; m < length; m++)
            {
                if (stack[stackTop - m] != handles[k][length - 1 - m])
                {
                    isFound = false;
                
                    break;
                }
            }

            if (isFound) // Successful reduction
            {
                stack[stackTop - m + 1] = 'S';
                stackTop = stackTop - m + 1;
                stackCheckPointer = stackTop;

                //  For finding a non-terminal symbol
                while(stack[stackCheckPointer] == 'S')
                {
                    stackCheckPointer--;
                }
                
                stack[stackTop + 1] = '\0';
                printf("\t\tREDUCED S -- > %s", handles[k]);
                
                return true;
            }
        }
    }

    return false;
}


char* substr(const char *src, int m, int n)
{
    // To get the length of the destination string
    int len = n - m;

    // To allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char *)malloc(sizeof(char) * (len + 1));

    // To extracts characters between m'th and n'th index from source string and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // To null-terminate the destination string
    *dest = '\0';

    // To return the destination string
    return dest - len;
}

// To parse the input sentence
void parse(char * inputString){
    while(inputString[inputPointer] != '$')
    {
        printf("\n%s", stack);
        printf("\t\t%s", substr(inputString,inputPointer, strlen(inputString)));
        if(precedenceTable[getIndex(stack[stackCheckPointer])][getIndex(inputString[inputPointer])] == '>')
        {
            reducer();
        }
        else
        {
            shift(inputString);
        }
    }

    printf("\n%s", stack);
    printf("\t\t%s", substr(inputString,inputPointer, strlen(inputString)));

    while(reducer())
    {
        printf("\n%s", stack);
        printf("\t\t%s", substr(inputString,inputPointer, strlen(inputString)));
    }

    // To check  final stack
    if (strcmp(stack, "$S") == 0)
    {
        printf("\t\tACCEPTED!!");
    }
    else
    {
        printf("\t\tREJECTED!!");
    }
}

// Driver Function
int main(){

    printf("The given grammer is as follows: \n\n");
    printf("S -- > i\nS --> S+S\nS --> S-S\nS --> S*S\nS --> S/S\n");

    char * inputString = (char *) malloc(sizeof(char ) * 50);

    printf("\nEnter the input sentence: ");
    gets(inputString);
    
    int length = strlen(inputString);
    inputString[length] = '$';
    inputString[length + 1] = '\0';

    // For setting the table format
    printf("\nSTACK\t\tINPUT\t\tACTION");
    printf("\n-----\t\t-----\t\t------");
    
    parse(inputString);

    // For releasing memory
    free(inputString);
    
    return 0;
}