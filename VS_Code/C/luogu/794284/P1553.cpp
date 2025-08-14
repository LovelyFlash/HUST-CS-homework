#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long

void print_num(char *num)
{
    int i;
    if (strlen(num) == 1)
        cout << num;
    else
    {
        for (i = 0; num[i] == '0'; i++)
            ;
        for (; i < strlen(num); i++)
            cout << num[i];
    }
}

int main()
{
    char num_1[25], x, num_2[25];
    cin >> num_1;
    int i = 0, j = 0, len = strlen(num_1);
    ull tem;
    for (i = 0; num_1[i] <= '9' && '0' <= num_1[i] && i < len; i++)
        ;
    x = num_1[i];
    num_1[i++] = '\0';
    while (i < len)
        num_2[j++] = num_1[i++];
    i = 0;
    j = 0;
    int len1 = strlen(num_1);
    for (i = 0; i < len1 / 2; i++)
        swap(num_1[i], num_1[len1 - i - 1]);

    int len2 = strlen(num_2);
    for (j = 0; j < len2 / 2; j++)
        swap(num_2[j], num_2[len2 - j - 1]);

    switch (x)
    {
    case '\0':
        print_num(num_1);
        break;
    case '.':
        print_num(num_1);
        tem = atoi(num_2);
        while ((tem % 10) == 0 && tem != 0)
            tem /= 10;
        cout << x << tem;
        break;
    case '/':
        print_num(num_1);
        cout << x;
        print_num(num_2);
        break;
    case '%':
        print_num(num_1);
        cout << x;
        break;
    }
    return 0;
}