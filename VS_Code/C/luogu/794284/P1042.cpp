#include <bits/stdc++.h>
using namespace std;
#define MAX_LEN 62500

void eleven_win(char *score)
{
    int x = 0;
    int win = 0, lose = 0;
    while (score[x] != 'E')
    {
        if (score[x] == 'W')
            win++;
        else if (score[x] == 'L')
            lose++;
        if (max(win, lose) >= 11 && abs(win - lose) >= 2)
        {
            cout << win << ":" << lose << endl;
            win = 0, lose = 0;
        }
        x++;
    }
    cout << win << ':' << lose << endl;
}

void twenty_win(char *score)
{
    int x = 0;
    int win = 0, lose = 0;
    while (score[x] != 'E')
    {

        if (score[x] == 'W')
            win++;
        else if (score[x] == 'L')
            lose++;
        if (max(win, lose) >= 21 && abs(win - lose) >= 2)
        {
            cout << win << ":" << lose << endl;
            win = 0, lose = 0;
        }
        x++;
    }
    cout << win << ':' << lose << endl;
}

int main()
{
    char x, score[MAX_LEN];

    int i = 0;
    cin >> x;
    while (x != 'E')
    {
        if (x == 'W' || x == 'L')
            score[i++] = x;
        cin >> x;
    }
    score[i++] = 'E';
    score[i] = '\0';
    eleven_win(score);
    cout << endl;
    twenty_win(score);
    return 0;
}