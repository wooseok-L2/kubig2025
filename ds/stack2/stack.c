int stack[100];               // global
int tos;                      // top of stack

void push(int data)            // func. definition
{
    stack[tos] = data;
    tos++;
}

int pop(void)
{
    --tos;
    return stack[tos];
}

