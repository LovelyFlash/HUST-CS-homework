#include <crtdbg.h>
#include <bits/stdc++.h>
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
        cout << "正在释放元素空间" << endl;
    }

    MAT(MAT &&other) noexcept : r(other.r), c(other.c), e(other.e)
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

    MAT &operator=(MAT &&other) noexcept
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

    int *operator[](int row)
    {
        cout << "正在取回第" << row << "行首元素：";
        return e + (row - 1) * c;
    }

    int &operator()(int row, int col)
    {
        cout << "正在访问第" << row + 1 << "行第" << col + 1 << "列的元素" << endl;
        return e[row * c + col];
    }

    MAT operator+(MAT &other)
    {
        cout << "正在将矩阵相加" << endl;
        MAT tem(r, c);
        for (int i = 0; i < r * c; i++)
            tem.e[i] = (*this).e[i] + other.e[i];
        return tem;
    }

    MAT &operator++()
    {
        cout << "正在运行前置++" << endl;
        for (int i = 0; i < r * c; i++)
            e[i]++;
        return *this;
    }

    MAT operator++(int)
    {
        cout << "正在运行后置++" << endl;
        MAT tem(*this);
        ++(*this);
        return tem;
    }

    int sum()
    {
        cout << "矩阵中所有元素之和:";
        int res = 0;
        for (int i = 0; i < r * c; i++)
            res += e[i];
        return res;
    }

    void print(string s)
    {
        cout << "正在打印矩阵：" << s << endl;
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
    a.print("a");
    cout << "a[2] = " << *a[2] << endl;
    cout << a.sum() << endl;
    MAT b, c;
    b = c = a;
    ++b;
    b.print("b");
    c = std::move(b);
    (c++).print("c++");
    MAT d(std::move(c));
    d.print("d");
    MAT e;
    e = a + a + d;
    e.print("e");
}

int main()
{
    test();
    _CrtDumpMemoryLeaks();
}