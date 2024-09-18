## my C compiler

# guide and direction: https://norasandler.com/2017/11/29/Write-a-Compiler.html

# target:
 1. looking forward to building a simple C compiler, at least to the assembly level - yet to have decided the target assembly (x86_64)

# Steps:
 1. accept a single file
 2. creating a tokenizer
    - tokenize the code file to its tokens and keep it in a Lexer struct. The Lexer consists of the tokens in the file and their offset locations.
 3. creating a parser
    - the parser creates an AST out of the tokenizer's output - the Lexer structure.
