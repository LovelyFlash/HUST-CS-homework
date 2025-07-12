#include <bits/stdc++.h>
using namespace std;

int main()
{
    char num_1[25], x, num_2[25];
    cin >> num_1;
    int i = 0, j = 0;
    for (i = 0; num_1[i] <= '9' && '0' <= num_1[i]; i++)
        ;
    x = num_1[i];
    num_1[i] = '\0';
    while (num_1[++i])
        num_2[j++] = num_1[i];
    i = 0;
    j = 0;
    while (i <= strlen(num_1) / 2)
    {
        swap(num_1[i], num_1[strlen(num_1) - i - 1]);
        i++;
    }
    while (j <= strlen(num_1) / 2)
    {
        swap(num_2[j], num_2[strlen(num_2) - j - 1]);
        j++;
    }
    int a = atoi(num_1);
    int b = atoi(num_2);
    cout << a << x;
    if (b)
        cout << b;
    return 0;
}