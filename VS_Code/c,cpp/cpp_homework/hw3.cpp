#include <bits/stdc++.h>

using namespace std;
class Student
{
private:
    char name[10];
    int age;
    int score;

public:
    Student(const char *name, int age, int score)
    {
        strcpy(this->name, name);
        this->age = age;
        this->score = score;
    }
    void displayInfo()
    {
        cout << "Student Name: " << name << ", Age: " << age << ", Score: " << score << endl;
    } // 在一行中 显示学生信息
    ~Student()
    {
        cout << "Deconstructing Student: " << name << endl;
    } // 显示 deconstruct student
};

class Teacher
{
private:
    char name[10];
    float salary;

public:
    Teacher(const char *name, float salary)
    {
        strcpy(this->name, name);
        this->salary = salary;
    }
    void displayInfo()
    {
        cout << "Teacher Name: " << name << ", Salary: " << salary << endl;
    } //  显示教师信息（显示在一行）
    ~Teacher()
    {
        cout << "Deconstructing Teacher: " << name << endl;
    } // 显示 deconstruct teacher
};

class PersonNode
{
private:
    int type;   // type=1 表示 student; =2 teacher
    void *node; // 指向一个 Student ,或者 Teacher
    PersonNode *next;

public:
    PersonNode(int type, void *p, PersonNode *next = NULL)
    {
        this->type = type;
        this->node = p;
        this->next = next;
    } // 构造一个结点
    // 在体外定义函数时，应写为
    //  PersonNode::PersonNode(int type, void *p，PersonNode *next) { ...}
    ~PersonNode()
    {
        if (type == 1)
            delete (Student *)node;
        else if (type == 2)
            delete (Teacher *)node;
    } //  析构node 指向的对象
    int gettype()
    {
        return type;
    } // 返回 type
    void *getnode()
    {
        return node;
    } // 返回 node
    PersonNode *getnext()
    {
        return next;
    } // 返回 next
    void setnext(PersonNode &p)
    {
        next = &p;
    } // 将 next 设置为 p
};

class PersonList
{
private:
    PersonNode *head;

public:
    void insertIntoList(PersonNode *p)
    {
        if (head == nullptr)
            head = p;
        else
        {
            PersonNode *current = head;
            while (current->getnext())
                current = current->getnext();
            current->setnext(*p);
        }
    }
    void displayInfo()
    {
        PersonNode *tem = head;
        while (tem)
        {
            int type = tem->gettype();
            cout << "type: " << (type ? "student" : "teacher") << ", ";
            if (type == 1)
                ((Student *)tem->getnode())->displayInfo();
            else
                ((Teacher *)tem->getnode())->displayInfo();
            tem = tem->getnext();
        }
    } // 显示链表中所有结点的信息
    PersonList()
    {
        head = nullptr;
    } // 初始化时 链表为空,即 head=NULL
    ~PersonList()
    {
        PersonNode *p = head;
        while (p)
        {
            PersonNode *tem = p->getnext();
            delete p;
            p = tem;
        }
    } // 析构整个链表，回到链表为空的状态，注意释放所有通过new申请的空间
};

int main()
{
    PersonList mylist;
    PersonNode *pp;
    Teacher *tp;
    Student *sp;
    tp = new Teacher("ZhangSan", 5850); // 创建一个教师对象，加入链表; …… 参数自定
    pp = new PersonNode(2, tp);
    mylist.insertIntoList(pp);

    sp = new Student("LiSi", 19, 89.12); // 创建一个学生对象，加入链表
    pp = new PersonNode(1, sp);
    mylist.insertIntoList(pp);

    Teacher &tr = *new Teacher("WangWu", 4920); // 创建一个教师对象，加入链表
    pp = new PersonNode(2, &tr);                //  用引用代替指针的用法示例
    mylist.insertIntoList(pp);

    mylist.displayInfo();
    return 0;
}
