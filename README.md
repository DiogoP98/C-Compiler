# C Compiler
C compiler for a small subset of the C language. It recognizes "if"/"else" and "while" expressions, assignments and declarations and input/output operations.

## Requirements
GCC - C compiler

## Usage
Execute MakeFile.

```bash
make
```

To test just execute "stack" file and give an example as input.

```bash
./stack < exemplo1.txt
```

## Description of the program
When given a C program as input, the program starts by syntax analyzing it, reporting erros if there is any syntax mistake.<br/>
If the syntax is all correct the program will build an intermediate code, in P-CODE, and print it to the bash.<br/>
After this is built, it will analyze it and build an executable MIPS file.

## Authors
| Nome              | Numero UP     |
| ----------------- | ------------- |
| Diogo Pereira     | 201605323     |
| Frederico Emanuel | 201604674     |

