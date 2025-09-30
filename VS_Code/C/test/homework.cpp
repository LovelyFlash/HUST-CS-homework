#include <bits/stdc++.h>

using namespace std;

class homework
{

private:
    int len;
    int *data;

public:
    homework() : len(0), data(nullptr) {}

    homework(const int &l)
    {
        len = l;
        data = (int *)malloc(len * sizeof(int));
        for (int i = 0; i < len; i++)
            data[i] = 0;
    }
    homework(const homework &copy)
    {
        len = copy.len;
        data = (int *)malloc(len * sizeof(int));
        for (int i = 0; i < len; i++)
            data[i] = copy.data[i];
    }

    int operator[](int index)
    {
        return data[index];
    }

    void give_data(int index, int n)
    {
        data[index] = n;
    }

    int show_len()
    {
        return len;
    }

    int *show_data()
    {
        return data;
    }

    void print_all()
    {

        cout << "len = " << len << endl;
        for (int i = 0; i < len; i++)
            cout << data[i] << " ";
        cout << endl;
    }
};

int main()
{
    homework X(7);
    for (int i = 0; i < X.show_len(); i++)
        X.give_data(i, i + 1);
    homework Y(X);
    Y.print_all();
    X.give_data(2, 20);
    X.print_all();
    Y.print_all();
}