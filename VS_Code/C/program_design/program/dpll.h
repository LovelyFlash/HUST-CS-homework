#include <iostream>
#include <cstdlib>
#ifndef _DPLL_
#define _DPLL_

int cmp_1(const void *a, const void *b)
{
    return a > b;
}
class Sentence
{
private:
    int MAX = 730;
    int *arr;

public:
    Sentence()
    {
        arr = new int[MAX];
        for (int i = 0; i < MAX; i++)
            arr[i] = 0;
    }
    int operator[](int n)
    {
        return arr[n];
    }
    void assign(int n)

    // 标识对应文字存在性以及正负性
    {
        if (n > 0)
            arr[n] = 1;
        else if (n < 0)
            arr[n] = -1;
        arr[0]++;
    }

    void del_var(int n)
    // 依据单子句规则修改句子
    {
        if (arr[n] == 1)
            arr[0] = -1; // 标识该句子已被删除
        else if (arr[n] == -1)
        {
            arr[n] = 0;
            arr[0]--; // 标识该句子文字数量减少
        }
    }

    void add(int n)
    { // 用于记录文字出现次数
        arr[n]++;
    }

    void minus(int n)
    { // 用于记录文字出现次数
        arr[n]--;
    }

    int findFirstVar()
    // 找到该句子中第一个文字
    {
        int i = 0;
        while (arr[i])
            i++;
        return i;
    }
};

int cmp(Sentence s1, Sentence s2)
{
    return s1[0] > s2[0];
}
int cmp_adapter(const void *a, const void *b)
{
    return cmp(*(const Sentence *)a, *(const Sentence *)b);
}
struct CNF
{
    int var_num = -1, clause = -1, var;
    Sentence *sentence;

    CNF(const char *filename)
    {
        FILE *file = fopen(filename, "r");
        while (!feof(file))
        {
            char tem[100];
            char msg;
            char line[1000];
            fgets(line, 1000, file);
            if (line[0] == 'c')
                continue;
            else if (line[0] == 'p')
            {
                if (var_num != -1 && clause != -1)
                {
                    printf("CNF文件错误：文件有多个信息");
                    exit(-1);
                }
                try
                {
                    sscanf(line, "%s%s%d%d", &msg, tem, &var_num, &clause);
                }
                catch (const std::exception &e)
                {
                    printf("CNF文件错误：文件信息读取失败");
                    exit(-1);
                }
                if (var_num <= 0 || clause <= 0)
                {
                    printf("CNF文件错误：文件信息有误");
                    exit(-1);
                }
                break;
            }
            else
            {
                printf("CNF文件错误：文件信息缺失");
                exit(-1);
            }
        }

        sentence = new Sentence[clause + 1];
        int num = 1;
        while (!feof(file))
        {
            fscanf(file, "%d", var);
            if (var)
            {
                sentence[num].assign(var);
                sentence[0].add(var); // 增加对应文字出现次数
            }
            else
                num++;
        }
    }
    void sort()
    {
        qsort(sentence, clause, sizeof(Sentence), cmp_adapter);
    }
    int var_exist()
    // 判断是否存在单子句
    {
        for (int i = 0; i < clause; i++)
            if (sentence[i][0] == 1)
                return 1;
        return 0;
    }
    CNF find_maxvar(CNF S)
    // 找到出现次数最多的文字,并将其作为单子句添加到整体中
    {
        int max = -1;
        for (int i = 0; i < var_num; i++)
            if (sentence[0][i] > max)
                max = i;
        clause++;
        sentence = (Sentence *)realloc(sentence, (clause + 1) * sizeof(Sentence)); // 分配空间增加句子
        sentence[clause].assign(max);
        return S;
    }
    void del_var(int line, int var)
    // 删除文字的同时，减少对应的文字出现次数
    {
        sentence[line].del_var(var);
        sentence[0].minus(var);
    }
    CNF back(CNF S)
    // 与find_maxvar功能相似，添加的是否命题单子句
    {
        int max = -1;
        for (int i = 0; i < var_num; i++)
            if (sentence[0][i] > max)
                max = i;
        clause++;
        sentence = (Sentence *)realloc(sentence, (clause + 1) * sizeof(Sentence));
        sentence[clause].assign(-max);
        return S;
    }
};

bool DPLL(CNF S)
{
    S.sort();
    while (S.var_exist())
        for (int i = 0; S.sentence[i][0] <= 1; i++)
            if (S.sentence[i][0] == 1) // 找到所有单子句并操作
            {
                int k = S.sentence[i].findFirstVar(); // 找到单子句中的文字
                for (int j = i; j < S.clause; j++)
                {
                    S.del_var(j, k);           // 删除文字
                    if (S.sentence[j][0] == 0) // 出现空子句即说明无结果
                        return false;
                }
                S.sort();
                if (S.sentence[S.clause - 1][0] == -1) // 若排序后文字数量最大的句子已被删除，则说明有解
                    return true;
            }
    CNF tem = S;
    if (DPLL(S.find_maxvar(S)) > 0)
        return true;
    return DPLL(tem.back(tem));
}

bool DPLL(const char *filename)
{
    return DPLL(CNF(filename));
}
#endif