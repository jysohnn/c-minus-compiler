C- Compiler Project
=====================

## Run

```
$ make
$ ./cminus filename.c
$ spim load filename.s
```

## Using
```
1. flex
2. bison
3. spim
```

### Project 1: Lexer
* Source Code -> Token Stream
* Check lexical error
### Project 2: Parser
* Token Stream -> AST
* Check syntax error
### Project 3: Semantic Analyzer
* AST -> decorated AST
* Check semantic error (scope, type...)
### Project 4: Code Generation
* decorated AST -> Target Code (MIPS Assembly)