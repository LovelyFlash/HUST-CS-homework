#include <iostream>
#include <cstdlib>
#ifndef _DPLL_
#define _DPLL_
int MAX = 730;
int cmp_1(const void *a, const void *b)
{
    return a > b;
}
class Sentence
{
private:
    int *arr;

public:
    Sentence()
    {
        arr = new int[MAX];
        for (int i = 0; i < MAX; i++)
            arr[i] = 0;
    }

    // 拷贝构造函数
    Sentence(const Sentence &other)
    {
        arr = new int[MAX];
        for (int i = 0; i < MAX; i++)
            arr[i] = other.arr[i];
    }

    void out()
    {
        for (int i = 0; i < MAX; i++)
            std::cout << i << ' ' << arr[i] << ' ';
        std::cout << '\n';
    }

    int operator[](int n)
    {
        return arr[abs(n)];
    }
    void assign(int n)

    // 标识对应文字存在性以及正负性
    {
        arr[abs(n)] = n / abs(n);
        arr[0]++;
    }

    void del_var(int n)
    // 依据单子句规则修改句子
    {
        if (arr[abs(n)] == n / abs(n))
            arr[0] = -1; // 标识该句子已被删除
        else if (arr[abs(n)] == -n / abs(n))
        {
            arr[abs(n)] = 0;
            arr[0]--; // 标识该句子文字数量减少
        }
    }

    void add(int n)
    { // 用于记录文字出现次数
        arr[abs(n)]++;
    }

    void minus(int n)
    { // 用于记录文字出现次数
        arr[abs(n)]--;
    }

    int findFirstVar()
    // 找到该句子中第一个文字
    {
        int i = 1;
        while (arr[i] == 0)
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
    Sentence *sentence = new Sentence[1];
    CNF() {
    };

    CNF(const CNF &other)
    {
        var_num = other.var_num;
        var = other.var;
        clause = other.clause;
        sentence = new Sentence[other.clause + 1];
        for (int i = 0; i < other.clause + 1; i++)
            sentence[i] = Sentence(other.sentence[i]);
    }
    CNF(const char *filename)
    {
        FILE *file = fopen(filename, "r");
        int clause_num = 1;
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
                    delete[] sentence; // 释放原有空间，防止内存泄漏
                    MAX = var_num + 1;
                    sentence = new Sentence[clause + 1];
                    // 第一个数组用于存储文字出现次数
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
            }
            else if (line[0] >= '0' && line[0] <= '9' || line[0] == '-')
            {
                if (var_num == -1 || clause == -1)
                {
                    printf("CNF文件错误：文件信息缺失");
                    exit(-1);
                }
                int i = 0;
                char *p = line;
                while (1)
                {
                    sscanf(p, "%d", &var);
                    if (var > var_num || var < -var_num)
                    {
                        printf("CNF文件错误：文字编号超出范围");
                        exit(-1);
                    }
                    if (var == 0)
                        break;
                    if (var == -1307)
                    {
                        sentence[clause_num].assign(var); // 记录句子
                        sentence[0].add(var);             // 记录文字出现次数
                    }
                    else
                    {
                        sentence[clause_num].assign(var); // 记录句子
                        sentence[0].add(var);             // 记录文字出现次数
                    }
                    while (*p != ' ' && *p != '\n' && *p != '\0')
                        p++;
                    if (*p == '\n' || *p == '\0')
                        break;
                    p++;
                }
                clause_num++;
                if (clause_num >= clause + 1)
                    break;
            }
            else
            {
                printf("CNF文件错误：文件信息缺失");
                exit(-1);
            }
        }
    }
    void sort()
    {
        qsort(sentence + 1, clause, sizeof(Sentence), cmp_adapter);
    }
    int var_exist()
    // 判断是否存在单子句
    {
        for (int i = 1; i < clause + 1; i++)
            if (sentence[i][0] == 1)
                return 1;
        return 0;
    }
    int find_maxvar(CNF &S)
    // 找到出现次数最多的文字,返回该文字索引
    {
        int max = -1;
        for (int i = 0; i < var_num; i++)
            if (sentence[0][i] > max)
                max = i;

        CNF t = CNF(S);
        clause++;
        sentence = new Sentence[clause + 1];
        for (int i = 0; i < clause; i++)
            sentence[i] = t.sentence[i];

        return max;
    }
    void del_var(int line, int var)
    // 删除文字的同时，减少对应的文字出现次数
    {
        sentence[line].del_var(var);
        sentence[0].minus(var);
    }

    CNF if_true(CNF &S, int max)
    // 假设选取变元为真
    {
        sentence[clause].assign(max);
        sentence[0].add(max);
        return S;
    }

    CNF if_false(CNF &S, int max)
    // 假设选取变元为假
    {
        sentence[clause].assign(-max);
        sentence[0].add(-max);
        return S;
    }
};

bool DPLL(CNF S)
{
    S.sort();
    // if (S.clause)
    //     for (int i = 0; i < S.clause + 1; i++)
    //         S.sentence[i].out();
    while (S.var_exist())
        for (int i = 1; S.sentence[i][0] <= 1; i++)
        {
            if (S.sentence[i][0] == 1) // 找到所有单子句并操作
            {
                int k = S.sentence[i].findFirstVar(); // 找到单子句中的文字
                for (int j = i; j < S.clause + 1; j++)
                {
                    S.del_var(j, k);           // 删除文字
                    if (S.sentence[j][0] == 0) // 出现空子句即说明无结果
                        return false;
                    else if (S.sentence[j][0] == -1)
                        // 若删除句子则减少该句中的文字出现次数
                        for (int m = 1; m <= S.var_num; m++)
                            if (S.sentence[j][m] && m != k)
                                S.sentence[0].minus(m);
                }
                S.sort();

                if (S.sentence[S.clause][0] == -1) // 若排序后文字数量最大的句子已被删除，则说明有解
                {

                    for (int i = 0; i < S.clause + 1; i++)
                        S.sentence[i].out();
                    return true;
                }
            }
        }

    CNF tem = CNF(S);
    int max = S.find_maxvar(S);
    if (DPLL(S.if_true(S, max)) > 0)
        return true;
    return DPLL(tem.if_false(tem, max));
}

bool DPLL(const char *filename)
{
    return DPLL(CNF(filename));
}
#endif