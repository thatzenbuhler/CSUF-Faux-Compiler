Faux Compiler
======
Recursive Descent Parser and Compiler for a University Computer Science Course, written in C++ using Microsoft Visual Studio.

Explanation
------
This project consists of one 'driver' file, handling the launch of three separate sections of the applications:
1. Token Extraction ( Lexical Analysis)
2. Syntax Analysis
3. Code Generation

The Lexical Analysis parses a given text file line by line and extracts tokens such as syntax characters or keywords and stores them in order. This also handles line counting for error checks. This is done using a partial Finite State Automaton.

The Syntax Analysis uses recursively ordered functions to check the ordered tokens with the rules of the 'RAT17F' fictional programming language. This spits out an error and exits the program if incorrect syntax is detected.

The Code Generation, whose function calls are embedded in the syntax analysis, generates generic assembly instructions and stores them in a vector, which is then saved to a text file at the end of the program. This also includes handling stack memory order and branch statements.

The resulting generic assembly could then be theoretically executed as an example of a fully compiled program written in the 'RAT17F' fictional programming language.
