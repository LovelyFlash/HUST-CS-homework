#ifndef STEP3_STU_H
#define STEP3_STU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *p; // 用于存储拼接后的字符串

// main0 函数的实现，跳过第一个字符串参数
static inline int main0(int n, char* inputStr[]) {
    // 如果没有足够的参数，直接返回
    if (n <= 1) {
        p = NULL;
        return -1;
    }

    // 计算从第二个参数开始拼接后的总长度
    int totalLength = 0;
    for (int i = 1; i < n; i++) {
        totalLength += strlen(inputStr[i]);
    }
    
    // 为连接后的字符串分配内存，并确保最后一个字符是 '\0'
    p = (char*)malloc(totalLength + 1);
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    
    // 初始化连接后的字符串为空串
    p[0] = '\0';
    
    // 从第二个参数开始拼接字符串
    for (int i = 1; i < n; i++) {
        strcat(p, inputStr[i]);
    }
    
    return 0;
}

#endif /* STEP3_STU_H */
