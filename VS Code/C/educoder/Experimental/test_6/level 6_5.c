#include <stdio.h>
#include <string.h>

int main()
{
    int func = 0;
    char string1[100], string2[100];
    char *result, c;
    char *(*p[4])(char *, const char *) = {0, strcpy, strcat, strtok}; 
    while (1)
    {
        scanf("%d", &func);
        getchar();
        
        if (func == 4) break;
        fgets(string1, sizeof(string1), stdin);
        string1[strcspn(string1, "\n")] = '\0'; 
        fgets(string2, sizeof(string1), stdin);
        string1[strcspn(string1, "\n")] = '\0'; 
        result = p[func](string1, string2);
        printf("%s", result);
    }
    return 0;
}