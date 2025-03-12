#include <stdio.h>
#include <stdlib.h>

void transfer(const char *filename)
{
    FILE *fp_in = fopen(filename, "r");
    if (!fp_in)
    {
        perror("无法打开输入文件");
        return;
    }

    int rows, cols;

    if (fscanf(fp_in, "%d %d", &rows, &cols) != 2)
    {
        fprintf(stderr, "文件格式错误：无法读取矩阵维度\n");
        fclose(fp_in);
        return;
    }

    if (rows <= 0 || cols <= 0)
    {
        fprintf(stderr, "无效的矩阵维度：%d x %d\n", rows, cols);
        fclose(fp_in);
        return;
    }

    int matrix_in[rows][cols];
    int matrix_out[cols][rows];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (fscanf(fp_in, "%d", &matrix_in[i][j]) != 1)
            {
                fprintf(stderr, "文件格式错误：无法读取矩阵数据\n");
                fclose(fp_in);
                return;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix_out[cols - j - 1][i] = matrix_in[i][j];
        }
    }

    fclose(fp_in);

    const char *output_file = "matrix.out";
    FILE *fp_out = fopen(output_file, "w");
    if (!fp_out)
    {
        perror("无法打开输出文件");
        return;
    }

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if(j < rows-1)
                fprintf(fp_out, "%d ", matrix_out[i][j]);
            else
                fprintf(fp_out, "%d", matrix_out[i][j]);
        }
        fprintf(fp_out, "\n");
    }

    fclose(fp_out);
}

int main()
{
    char filepath[100];
    scanf("%s", filepath);
    transfer(filepath);
    return 0;
}
