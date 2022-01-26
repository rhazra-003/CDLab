#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


const char *KEYWORDS[11] = {
    "if", "else", "else if", "switch", "case",
    "goto", "while", "do", "for", "break", "continue"};

const char *OPERATORS[] = {
    "--", "<=", ">=", "==", "!=", "&&", "||", "++", "--"};

// Function to check if the string is a delimiter
bool is_delimiter(char ch)
{
    if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\0'
    || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' 
    || ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '='
    || ch == '&' || ch =='|' || ch == '!' || ch == '{' || ch == '}'
    || ch == '(' || ch == ')')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to check if the string is a whitespace
bool is_whitespace(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to check if the string is a single character operator
bool is_operator(char ch) {
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' 
    || ch == '>' || ch == '<' || ch == '=' || ch == '&' || ch =='|' 
    || ch == '!' || ch == ',' || ch == ';' || ch == '{' || ch == '}') {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to check if the string is an identifier
bool is_identifier(char *str)
{
    if (str[0] >= 'a' && str[0] <= 'z')
        ;
    else if (str[0] >= 'A' && str[0] <= 'Z')
        ;
    else
    {
        return false;
    }

    for (int i=1; i<strlen(str); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            continue;
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            continue;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    
    return true;
}

// Function to check if the string is a keyword
bool is_keyword(char *str)
{
    for (int i=0; i<11; i++)
    {
        if (strcmp(str, KEYWORDS[i]) == 0)
        {
            return (true);
        }
    }        
    
    return (false);
}

// Function to check if string is a multi character operator
bool is_multi_char_operator(char *str)
{
    for (int i=0; i < sizeof(OPERATORS) / sizeof(OPERATORS[0]); i++)
    {
        if (strcmp(str, OPERATORS[i]) == 0)
        {
            return true;
        }
    
    return false;
    }
}

// Function to fetch the substring
char *substr(char *str, int left, int right)
{
    int i;
    char *subStr = (char *)malloc(sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
    {
        subStr[i - left] = str[i];
    }
    
    subStr[right - left + 1] = '\0';
    
    return (subStr);
}

bool is_punctuation(char ch)
{
    if (ch == ';' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == ',')
        return true;
    else
        return false;
}

bool is_incre_decre_Operator(char *str)
{
    if ((str[0] == '+' && str[1] == '+') || (str[0] == '-' && str[1] == '-'))
        return true;
    else
        return false;
}

bool is_unary_arithmetic_Operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
        return true;
    else
        return false;
}

bool is_unary_relational_Operator(char ch)
{
    if (ch == '>' || ch == '<')
        return true;
    else
        return false;
}

bool is_assignment_Operator(char *str)
{
    if (is_unary_arithmetic_Operator(str[0]) && str[1] == '=')
    {
        return true;
    }
    else
        return false;
}

bool is_multi_relational_Operator(char *str)
{
    if ((is_unary_relational_Operator(str[0]) || str[0] == '!' || str[0] == '=') && str[1] == '=')
    {
        return true;
    }
    else
        return false;
}

bool is_logical_Operator1(char *str)
{
    if ((str[0] == '&' && str[1] == '&') || (str[0] == '|' && str[1] == '|'))
        return true;
    else
        return false;
}

bool is_logical_Operator2(char ch)
{
    if (ch == '!')
        return true;
    else
        return false;
}

void check_for_unary_Operators(char ch)
{
    if (ch == '=')
        printf("%c ---  ASSIGNMENT OPERATOR\n", ch);
    else if (is_punctuation(ch))
        printf("%c --- PUNCTUATION\n", ch);
    else if (is_unary_arithmetic_Operator(ch))
        printf("%c --- ARITHMETIC OPERATOR\n", ch);
    else if (is_unary_relational_Operator(ch))
        printf("%c --- RELATIONAL OPERATOR\n", ch);
    else if (is_logical_Operator2(ch))
        printf("%c --- LOGICAL OPERATOR\n", ch);
}


// Function to parse the input string
int parse(char *str, char *symbols[100])
{
    int prev=0, p=0, len = strlen(str), k=0;

    // Parsing starts from here
    while (p < len && prev <= p)
    {
        if (!is_delimiter(str[p]))
        {
            p++;
        }
        if (is_delimiter(str[p]) && prev == p)
        {
            if (p + 1 < len && is_operator(str[p]) && is_operator(str[p + 1]) && str[p] != ' ')
            {
                char *strsub = substr(str, p, p + 1);
                if (is_multi_char_operator(strsub))
                {
                    if (is_incre_decre_Operator(strsub))
                    {
                        printf("%c%c --- ARITHMETIC OPERATORS\n", str[p], str[p + 1]);
                    }
                    else if (is_assignment_Operator(strsub))
                    {
                        printf("%c%c --- ASSIGNMENT OPERATOR\n", str[p], str[p + 1]);
                    }
                    else if (is_multi_relational_Operator(strsub))
                    {
                        printf("%c%c --- RELATIONAL OPERATOR\n", str[p], str[p + 1]);
                    }
                    else if (is_logical_Operator1(strsub))
                    {
                        printf("%c%c --- LOGICAL OPERATOR\n", str[p], str[p + 1]);
                    }
                }
                
                else
                {
                    check_for_unary_Operators(str[p]);
                    check_for_unary_Operators(str[p + 1]);
                }
                
                p += 2;
                prev = p;
                
                continue;
            }
            else if (is_operator(str[p]))
            {
                check_for_unary_Operators(str[p]);
            }
            
            p += 1;
            prev = p;
        }

        else if (is_delimiter(str[p]) && prev != p)
        {
            char *sub = substr(str, prev, p - 1);
            
            if (is_keyword(sub))
            {
                printf("%s --- KEYWORD\n", sub);
            }
            else if (is_identifier(sub))
            {
                printf("%s --- IDENTIFIER\n", sub);
                symbols[k++] = sub;
            }
            else
            {
                printf("%s --- INVALID at position %d\n", sub, prev);
            }
            
            prev = p;
        }
    }
    
    // To return the size of symbol table
    return k;
}


// Driver Code
int main()
{
    char str[200];
    printf("\nWrite the Expression here: ");
    fgets(str, 200, stdin);
    char *symbols[100];
    printf("\n");
    int size_sym = parse(str, symbols);
    
    printf("\n---SYMBOL TABLE---\n");
    
    for (int i = 0; i < size_sym; i++)
    {
        printf("%s\n", symbols[i]);
    }
    
    return 0;
}