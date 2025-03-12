#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct scoreNode
{
    char num[11];
    char name[10];
    int score[4];
    struct scoreNode *next;
};

struct scoreNode *createlist(struct scoreNode *head, int num)
{
    struct scoreNode *p, *tail = head;

    while (tail != NULL && tail->next != NULL)
    {
        tail = tail->next;
    }

    char x[11], y[10];
    int z[4];

    for (int i = 0; i < num; i++)
    {
        scanf("%s %s %d %d %d %d", x, y, &z[0], &z[1], &z[2], &z[3]);
        p = (struct scoreNode *)malloc(sizeof(struct scoreNode));
        if (p == NULL)
        {
            perror("内存分配失败");
            exit(EXIT_FAILURE);
        }
        strcpy(p->num, x);
        strcpy(p->name, y);
        for (int j = 0; j < 4; j++)
        {
            p->score[j] = z[j];
        }
        p->next = NULL;

        if (tail == NULL)
        {
            head = p;
        }
        else
        {
            tail->next = p;
        }
        tail = p; // 更新尾节点
    }
    return head;
}

void fun2(struct scoreNode *head)
{
    struct scoreNode *p = head;

    while (p != NULL)
    {
        printf("%s %s %d %d %d %d\n", p->num, p->name, p->score[0], p->score[1], p->score[2], p->score[3]);
        p = p->next;
    }
}

void fun3(struct scoreNode *head)
{
    char s[11];
    int course, new_score;
    scanf("%s", s);
    scanf("%d", &course);
    scanf("%d", &new_score);

    struct scoreNode *p = head;
    while (p != NULL)
    {
        if (strcmp(p->num, s) == 0)
        {
            if (course >= 1 && course <= 4)
                p->score[course - 1] = new_score;
            return;
        }
        p = p->next;
    }
}

void fun4(struct scoreNode *head)
{
    struct scoreNode *p = head;

    while (p != NULL)
    {
        float avg = (p->score[0] + p->score[1] + p->score[2] + p->score[3]) / 4.0;
        printf("%s %s %.2f\n", p->num, p->name, avg);
        p = p->next;
    }
}

void fun5(struct scoreNode *head)
{
    struct scoreNode *p = head;

    while (p != NULL)
    {
        int total = p->score[0] + p->score[1] + p->score[2] + p->score[3];
        float avg = total / 4.0;
        printf("%s %s %d %.2f\n", p->num, p->name, total, avg);
        p = p->next;
    }
}

void fun6(struct scoreNode *head, const char *filename)
{
    FILE *fp = fopen(filename, "wb"); // 打开文件以二进制写入模式
    if (!fp)
    {
        perror("文件打开失败");
        return;
    }

    struct scoreNode *p = head;
    while (p != NULL)
    {
        if (fwrite(p, sizeof(struct scoreNode), 1, fp) != 1)
        {
            perror("写入文件失败");
            fclose(fp);
            return;
        }
        p = p->next;
    }

    fclose(fp);
}

void fun7(struct scoreNode **head, const char *filename)
{
    FILE *fp = fopen(filename, "rb"); // 打开文件以二进制读取模式
    if (!fp)
    {
        perror("文件打开失败");
        return;
    }

    struct scoreNode *p, *tail = NULL;
    *head = NULL;

    while (1)
    {
        p = (struct scoreNode *)malloc(sizeof(struct scoreNode));
        if (fread(p, sizeof(struct scoreNode), 1, fp) != 1)
        {
            free(p);
            break;
        }
        p->next = NULL;

        if (*head == NULL)
        {
            *head = p;
        }
        else
        {
            tail->next = p;
        }
        tail = p;
    }
    fclose(fp);
}

void use_fun(struct scoreNode **head, int fun, const char *filename)
{
    switch (fun)
    {
    case 1:
    {
        int num;
        scanf("%d", &num);
        *head = createlist(*head, num);
        break;
    }
    case 2:
        fun2(*head);
        break;
    case 3:
        fun3(*head);
        break;
    case 4:
        fun4(*head);
        break;
    case 5:
        fun5(*head);
        break;
    case 6:
        fun6(*head, filename);
        break;
    case 7:
        fun7(head, filename);
        break;
    case 0:
        break;
    default:
        break;
    }
}

int main()
{
    struct scoreNode *head = NULL;
    int fun;
    const char *filename = "float.dat";
    do
    {
        scanf("%d", &fun);
        use_fun(&head, fun, filename);
    } while (fun != 0);

    struct scoreNode *p;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
    return 0;
}