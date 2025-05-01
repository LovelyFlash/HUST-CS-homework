#include <stdio.h>
#include <string.h>

#define MAX_KEY_LEN 65
#define TABLE_SIZE (1 << 18)

// 哈希表项结构体
typedef struct
{
    char key[MAX_KEY_LEN];
    int count;
    int used;
} Entry;

Entry table[TABLE_SIZE];

unsigned long hash_str(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int find_index(const char *key)
{
    unsigned long h = hash_str(key);
    int idx = h % TABLE_SIZE;
    while (table[idx].used)
    {
        if (strcmp(table[idx].key, key) == 0)
            return idx;
        idx = (idx + 1) % TABLE_SIZE;
    }
    return idx;
}

int main()
{
    int n;
    scanf("%d", &n);

    char matrixKey[MAX_KEY_LEN];

    for (int i = 0; i < n; i++)
    {
        int pos = 0;
        for (int r = 0; r < 8; r++)
        {
            char line[9];
            scanf("%s", line);
            for (int j = 0; j < 8; j++)
            {
                matrixKey[pos++] = line[j];
            }
        }
        matrixKey[pos] = '\0';

        int idx = find_index(matrixKey);
        if (!table[idx].used)
        {
            table[idx].used = 1;
            strcpy(table[idx].key, matrixKey);
            table[idx].count = 0;
        }
        table[idx].count++;
        printf("%d\n", table[idx].count);
    }

    return 0;
}
