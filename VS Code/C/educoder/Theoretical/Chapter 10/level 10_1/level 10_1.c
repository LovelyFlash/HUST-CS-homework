#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 函数声明
void read_file(const char *filename);
void read_file_p(const char *filename);


int main()
{
    char argv[2][10] = {0};
    char file[10], *filename = file;
    scanf("%s %s", &argv[0], &argv[1]);
    if(strcmp(argv[0], "type_c") == 0)
    {
        if(strcmp(argv[1], "/p") == 0)
        {
            scanf("%s", filename);
            read_file_p(filename);
        }
        else
        {
            read_file(argv[1]);
        }
    }
    else printf("指令错误\n");
}

void read_file(const char *filename)
{
    char full_path[256];
    const char *path_prefix = "src/step1_1/";

    // 拼接路径和文件名
    snprintf(full_path, sizeof(full_path), "%s%s", path_prefix, filename);

    FILE *fp = fopen(full_path, "r");
    if (!fp)
    {
        printf("无法打开文件：%s\n", full_path);
        return;
    }

    int line = 0;
    char ch;
    printf("1  "); // 第一行行号

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
        if (ch == '\n')
        {
            line++;
            printf("%d  ", line + 1); // 打印行号
        }
    }

    fclose(fp);
}

void read_file_p(const char *filename)
{
    char full_path[256];
    const char *path_prefix = "src/step1_1/";

    // 拼接路径和文件名
    snprintf(full_path, sizeof(full_path), "%s%s", path_prefix, filename);

    FILE *fp = fopen(full_path, "r");
    if (!fp)
    {
        printf("无法打开文件：%s\n", full_path);
        return;
    }

    int screen_line = 1;    // 当前屏内行号
    int displayed_lines = 0; // 当前屏内显示的总行数
    char ch;

    printf("%d  ", screen_line++); // 打印第一行行号

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);

        if (ch == '\n')
        {
            displayed_lines++;
            if (displayed_lines < 10)
            {
                printf("%d  ", screen_line++); // 打印行号
            }
            else
            {
                displayed_lines = 0; // 重置当前屏内显示行数
                screen_line = 1;     // 下一屏从 1 开始

                // 等待用户输入'q'
                char input;
                do
                {
                    input = getchar();
                } while (input != 'q');

                printf("%d  ", screen_line++); // 下一屏第一行行号
            }
        }
    }

    fclose(fp);
}
