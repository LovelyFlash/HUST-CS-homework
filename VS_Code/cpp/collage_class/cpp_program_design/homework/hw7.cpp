/*作业7：智能指针、Lambda表达式和STL编程
用 STL建立一个学生和教师信息的 vector。设有学生包含姓名、年龄、学习课程、分数等信息；教师含有姓名、年龄、工资信息。编写一个程序，能够向vector中添加学生和教师；能够显示所有人（学生和教师在一起）的信息；按照姓名排序后显示信息；按年龄排序后，显示所有人的信息；排序策略用lambda表达式实现。
    学生、教师对象都采用 动态方式生成（即不能定义学生对象、教师对象），使用智能指针管理对象内存空间，在程序结束时，应显示析构了的各个对象（学生和教师）的名字。
测试数据自定。
 要求给出运行效果截图，源程序（不要提交执行程序）。

提示：vector 中的元素，应是智能指针（即封装了原始指针的对象）。
例如：vector<shared_ptr<Person>> people;
生成一个共享智能指针：
make_shared<Student>(name, age, course, score))
当vector的生命周期结束时，它会销毁其所有元素。如果这些元素是智能指针（如shared_ptr或unique_ptr），则会调用这些智能指针的析构函数。*/

#include <bits/stdc++.h>

using namespace std;

class Person
{
protected:
    string name;
    int age;

public:
    ~Person()
    {
        cout << "正在析构" + name << endl;
    }
};

class Student : public Person
{
private:
    string course;
    int score;

public:
    Student(string name, int age, string course, int score) : name(name), age(age), course(course), score(score) {};
};

class Teacher : public Person
{
private:
    int salary;

public:
    Teacher(string name, int age, int salary) : name(name), age(age), salary(salary) {};
};

int main()
{
    vector<shared_ptr<Person>> people;
    people.push_back(make_shared<Student>("张三", 25, "C++程序设计", 95));
    people.push_back(make_shared<Student>("李四", 19, "C++程序设计", 87));
    people.push_back(make_shared<Teacher>("王五", 47, 6500));
    return 0;
}
