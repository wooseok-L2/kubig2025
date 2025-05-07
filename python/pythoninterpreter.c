#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    OP_PRINT,
    OP_UNKNOWN
} OpCode;

// bytecode -> .pyc
typedef struct{
    OpCode opcode;
    const char *arg;
} Insturction;

//parser
Insturction parse(const char *source)
{
    Insturction inst;
    if (strncmp(source, "print(\"hello\")", 15) == 0){
        inst.opcode = OP_PRINT;
        inst.arg = "hello";
    }
    else {
        inst.opcode = OP_UNKNOWN;
        inst.arg = NULL;
    }
    return inst;
}

// Make PVM
void execute(Insturction inst)
{
    switch(inst.opcode)
    {
    case OP_PRINT:
        printf("%s \n", inst.arg);
        break;
    
    case OP_UNKNOWN:
        printf("Cannot execute Instruction!!");
        break;
    }
}

int main()
{
    char source[256];

    printf("python prototype V1.0 (print(\"hello\")) : \n >>>");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = 0;

    Insturction inst = parse(source);
    execute(inst);

    return 0;
}