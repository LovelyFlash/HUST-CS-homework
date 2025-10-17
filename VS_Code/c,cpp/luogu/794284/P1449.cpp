#include <bits/stdc++.h>
using namespace std;

int main()
{
    char num[50][10] = {0};
    char *a, *b, *result;
    int resnum;
    stack<char *> s;
    char x = '0';
    int i = 0, j = 0;
    while (x != '@')
    {
        cin >> x;
        if ('0' <= x && x <= '9')
        {
            num[i][j++] = x;
        }
        else if (x == '.')
        {
            num[i][j] = '\0';
            i++;
            j = 0;
            s.push(num[i - 1]);
        }
        else if (x != '@')
        {
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            int num_a, num_b;
            num_a = atoi(a);
            num_b = atoi(b);
            switch (x)
            {
            case '+':
            {
                resnum = num_a + num_b;
                break;
            }
            case '-':
            {
                resnum = num_b - num_a;
                break;
            }
            case '*':
            {
                resnum = num_a * num_b;
                break;
            }
            case '/':
            {
                if (num_a == 0)
                {
                    cout << "Error: Division by zero" << endl;
                    return 1; // Exit on division by zero
                }
                resnum = num_b / num_a;
                break;
            }
            }
            result = new char[20];
            sprintf(result, "%d", resnum);
            strcpy(num[i], result);
            i++;
            j = 0;
            s.push(num[i - 1]);
        }
        else if (x == '@')
        {
            if (s.empty())
            {
                cout << "错误：栈为空" << endl;
                return 1;
            }
            result = s.top();
            cout << result << endl;
            return 0;
        }
    }
}