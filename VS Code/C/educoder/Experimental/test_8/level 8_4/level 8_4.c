#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 将浮点数以二进制形式写入文件
void write_floats_to_file(const char *filename)
{
    FILE *file = fopen(filename, "wb"); // 以二进制写模式打开文件
    if (!file)
    {
        perror("文件打开失败");
        exit(EXIT_FAILURE);
    }

    float numbers[10];
    for (int i = 0; i < 10; i++)
    {
        scanf("%f", &numbers[i]);
    }

    fwrite(numbers, sizeof(float), 10, file); // 将浮点数数组写入文件
    fclose(file);
}

// 从文件读取浮点数并以二进制显示每个字节
void read_and_display_binary(const char *filename)
{
    FILE *file = fopen(filename, "rb"); // 以二进制读模式打开文件
    if (!file)
    {
        perror("文件打开失败");
        exit(EXIT_FAILURE);
    }

    float numbers[10];
    fread(numbers, sizeof(float), 10, file); // 从文件读取浮点数数组
    fclose(file);

    for (int i = 0; i < 10; i++)
    {
        unsigned char *byte_ptr = (unsigned char *)&numbers[i];
        for (int j = sizeof(float) - 1; j >= 0; j--)
        {
            for (int k = 7; k >= 0; k--)
            {
                printf("%d", (byte_ptr[j] >> k) & 1);
            }
        }
        printf("\n");
    }
}

int main()
{
    const char *filename = "float.dat";

    // 写入浮点数到文件
    write_floats_to_file(filename);

    // 从文件中读取浮点数并显示其二进制形式
    read_and_display_binary(filename);

    return 0;
}
