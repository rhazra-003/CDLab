Write a Lexical Analyser with C language which only performs lexical analysis of a subset of C language. The subset language uses the following 
keywords, identifiers, operators, relational operators and punctuation symbols:

a) keywords: if, else, else if, switch, case, goto, while, do, for, break, continue.
b) identifiers: letter(letter|digit) * delimiter
c) arithmetic operators: +, --, *, /, %
d) relational operators: <, <=, >, >=, ==, !=, &&, ||, !
e) Assignment operators: =
f) Increment and decrement operators: ++ , -- --
g) punctuation symbols: “{“ , “}” “,” “;”

The output should be a stream of tokens with their type mentioned. An unrecognizable token should be identified with its position and 
error messages should be reported. Also construct the symbol table to be displayed.
