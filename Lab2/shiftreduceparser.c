// Implementation of a Shift Reduce Parser

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i=0;
char sentence[16], stack[16];

// Function to check whether the stack contains a production rule which needs to reduce //

void shiftreducer()
{
    int k;
    int stackLength = strlen(stack);

    for (k = stackLength-1; k >= 0; k--)
    {
        // Checking for production rule S ==> 0
        if (stack[k] == '0')
        {
            printf(" Reduce to S ==> 0 ");
            stack[k] = 'S';
            stack[k + 1] = '\0';
            
            // Printing the action
            printf("\n$%s\t%s$\t", stack, sentence);
        }
    }

    for (k = stackLength-1; k>0; k--)
    {
        // Checking for production rule S ==> S1
        if (stack[k - 1] == 'S' && stack[k] == '1')
        {
            printf(" Reduce to S ==> S1 ");
            stack[k - 1] = 'S';
            stack[k] = '\0';

            // Printing the action
            printf("\n$%s\t%s$\t", stack, sentence);
            i = i - 1;
        }
    }

    return;
}

// Driver Function

int main()
{
    printf("\nProduction rules are as follows:\nS ==> S1 \nS ==> 0\n");
    
    // Input the sentence
    printf("\nEnter the input sentence: ");
    gets(sentence);
    printf("The input sentence is: %s\n", sentence);
    
    // 'sentenceLength' contains length of input string
    int sentenceLength = strlen(sentence);
    
    // Printing the column names of table
    printf("\nSTACK \t INPUT \t ACTION");
    printf("\n----- \t ----- \t ------");
    
    // Printing initial values
    printf("\n$\t%s$\t", sentence);
    int j=0;
    
    for (i=0; j < sentenceLength; i++, j++)
    {
        // Printing action
        printf(" Shift ");
        
        // Pushing into stack
        stack[i] = sentence[j];
        stack[i + 1] = '\0';
        
        // Moving the pointer
        sentence[j] = ' ';
        
        // Printing the action
        printf("\n$%s\t%s$\t", stack, sentence);
        
        /* Checks whether stack contains any production or not and will reduce it */
        shiftreducer();
    }

    // End loop check for valid productions and reductions
    shiftreducer();
    
    // Checks final stack
    if (stack[0] == 'S' && stack[1] == '\0')
    printf(" ACCEPTED\n");
    else
    printf(" REJECTED\n");
}