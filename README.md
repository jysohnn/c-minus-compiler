C-Minus Compiler
=====================

### Run

```
$ make
$ ./project4_3 filename.c
$ spim load filename.s
```

### Using
```
1. flex
2. bison
3. spim
```

#### Project 1: Lexer
1. Source Code -> Token Stream
2. Check lexical error
#### Project 2: Parser
1. Token Stream -> AST
2. Check syntax error
#### Project 3: Semantic Analyzer
1. AST -> decorated AST
2. Check semantic error (scope, type...)
#### Project 4: Code Generation
1. decorated AST -> Target Code (MIPS Assembly)