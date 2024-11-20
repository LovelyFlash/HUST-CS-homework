#include <stdio.h>

void conversion(char hexString[]) {

    // 遍历字符串直到遇到非十六进制字符或字符串结束符
    int result = 0, i = 0;
    for (; hexString[i] != '\0'; i++) {

        if (hexString[i] >= '0' && hexString[i] <= '9') 
        {
            result *= 16;
            result += hexString[i] - '0';
        } 
        else if (hexString[i] >= 'a' && hexString[i] <= 'f') 
        {
            result *= 16;
            result += hexString[i] - 'a' + 10;
        } 
        else if (hexString[i] >= 'A' && hexString[i] <= 'F') 
        {
            result *= 16;
            result += hexString[i] - 'A' + 10;
        } 
        else 
        {
            break;  // 遇到非十六进制字符，停止转换
        }
        
    }

    // 输出转换结果
    printf("转换结果: %d\n", result);

}
