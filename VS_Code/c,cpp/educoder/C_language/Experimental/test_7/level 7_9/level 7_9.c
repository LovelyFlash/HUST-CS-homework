#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100 // 定义数组的最大容量，可根据需要调整

// 用数组模拟栈结构
typedef struct 
{
    long stack[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void init_stack(Stack *s) 
{
    s->top = -1;
}

// 压入新元素到栈
void push(Stack *s, long n) 
{
    if (s->top < MAX_SIZE - 1) 
    {
        s->stack[++s->top] = n;
    } 
    else 
    {
        printf("栈已满，无法压入元素！\n");
        exit(1);
    }
}

// 从栈中弹出元素并返回其值
long pop(Stack *s)
 {
    if (s->top == -1) 
    {
        printf("栈为空，无法弹出元素！\n");
        exit(1);
    }
    return s->stack[s->top--];
}

int main() 
{
    char token[20]; // 单个输入的令牌
    Stack stack;
    init_stack(&stack);

    // 使用 scanf 读取每个输入
    while (scanf("%s", token)!= EOF) 
    {
        if (strcmp(token, "+") == 0) 
        {
            long b = pop(&stack);
            long a = pop(&stack);
            push(&stack, a + b);
        } 
        else if (strcmp(token, "-") == 0) 
        {
            long b = pop(&stack);
            long a = pop(&stack);
            push(&stack, a - b);
        } 
        else if (strcmp(token, "*") == 0) 
        {
            long b = pop(&stack);
            long a = pop(&stack);
            push(&stack, a * b);
        } 
        else if (strcmp(token, "/") == 0) 
        {
            long b = pop(&stack);
            long a = pop(&stack);
            push(&stack, a / b);
        } 
        else 
        {
            // 将数字压入栈
            push(&stack, atol(token));
        }
    }

    // 检查结果
    printf("%ld\n", pop(&stack));

    return 0;
}