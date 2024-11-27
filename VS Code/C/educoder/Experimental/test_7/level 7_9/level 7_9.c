#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// 栈结构
typedef struct 
{
    int stack[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void init_stack(Stack *s) 
{
    s->top = -1;
}

// 入栈
void push(Stack *s, int value) 
{
    if (s->top < MAX_SIZE - 1) 
    {
        s->stack[++(s->top)] = value;
    }
}

// 出栈
int pop(Stack *s) 
{
    if (s->top == -1) 
    {
        printf("Stack underflow\n");
        return -1; // 错误处理
    }
    return s->stack[(s->top)--];
}

// 判断是否是操作符
int is_operator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 执行操作
int apply_operator(int a, int b, char operator) 
{
    switch (operator) 
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

// 计算RPN表达式
int evaluate_rpn(char *expression) 
{
    Stack s;
    init_stack(&s);
    int i = 0, num = 0;
    int has_num = 0;

    while (expression[i] != '\0') 
    {
        if (isdigit(expression[i])) 
        {
            // 构建多位数
            num = num * 10 + (expression[i] - '0');
            has_num = 1;
        } 
        else if (is_operator(expression[i])) 
        {
            if (has_num) 
            {
                push(&s, num);
                num = 0;
                has_num = 0;
            }
            int b = pop(&s);
            int a = pop(&s);
            int result = apply_operator(a, b, expression[i]);
            push(&s, result);
        } 
        else if (expression[i] == ' ') 
        {
            if (has_num) 
            {
                push(&s, num);
                num = 0;
                has_num = 0;
            }
        }
        i++;
    }

    if (has_num) 
    {
        push(&s, num); // 处理最后的数字
    }

    return pop(&s); // 最终结果
}

int main() {
    char expression[MAX_SIZE];
    fgets(expression, sizeof(expression), stdin);  // 读取整行输入
    expression[strcspn(expression, "\n")] = 0;  // 去除换行符
    int result = evaluate_rpn(expression);
    printf("%d", result); 
    return 0;
}
