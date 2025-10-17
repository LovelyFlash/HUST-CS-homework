#include <bits/stdc++.h>
#include <crtdbg.h>
using namespace std;

class MAT
{
    int r = 0;
    int c = 0;
    int *e = nullptr;

public:
    MAT() : r(0), c(0), e(nullptr)
    {
        cout << "默认构造中" << endl;
    }

    MAT(int row, int col) : r(row), c(col)
    {
        cout << "根据行列构造中" << endl;
        e = new int[r * c];
    }
    ~MAT()
    {
        delete[] e;
        cout << "正在释放该元素空间" << endl,
    }

    MAT(MAT &&other) : r(other.r), c(other.c), e(other.e)
    {
        cout << "正在移动构造" << endl;
        other.e = nullptr;
        other.r = 0;
        other.c = 0;
    }

    MAT(const MAT &other) : r(other.r), c(other.c)
    {
        cout << "正在复制构造" << endl;
        e = new int[r * c];
        memcpy(e, other.e, sizeof(int) * r * c);
    }

    MAT &operator=(const MAT &other)
    {
        cout << "正在深拷贝赋值" << endl;
        if (this != &other)
        {
            delete[] e;
            r = other.r;
            c = other.c;
            e = new int[r * c];
            memcpy(e, other.e, sizeof(int) * r * c);
        }
        return *this;
    }

    MAT &operator=(MAT &&other)
    {
        cout << "正在移动赋值" << endl;
        if (this != &other)
        {
            delete[] e;
            r = other.r;
            c = other.c;
            e = other.e;
            other.e = nullptr;
            other.c = 0;
            other.r = 0;
        }
        return *this;
    }

    MAT &operator+()(const MAT &a,const MAT &b){
        for(int i=0;i<a.r*a.c;i++)
    }

    int *operator[](int row)
    {
        return e + (row - 1) * c;
    }

    int &operator()(int row, int col)
    {
        return e[row * c + col];
    }

    MAT &operator++()
    {
        for (int i = 0; i < r * c; i++)
            e[i]++;
        return *this;
    }

    MAT operator++(int)
    {
        MAT tem(*this);
        ++(*this);
        return tem;
    }

    int sum(MAT &m)
    {
        int res = 0;
        for (int i = 0; i < r * c; i++)
            res += m.e[i];
        return res;
    }

    void print()
    {
        cout << "row = " << r << ", col = " << c << endl;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                cout << e[i * c + j] << ' ';
            cout << endl;
        }
    }
};

void test()
{
    MAT a(4, 5);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            a(i, j) = i * 5 + j;
    cout << "Matrix: a" << endl;
    a.print();
    cout << "a[2] = " << *a[2] << endl;
    MAT b, c;
    b = c = a;
    ++b;
    cout << "Matrix: b" << endl;
    b.print();
    c(b);
    cout << "Matrix: c++" << endl;
    (c++).print();
    cout << "Matrix: c" << endl;
    c.print();
}

int main()
{
    test();
    _CrtDumpMemoryLeaks();
}