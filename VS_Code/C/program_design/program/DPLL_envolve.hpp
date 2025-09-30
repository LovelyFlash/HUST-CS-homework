#ifndef __DPLL__
#define __DPLL__
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <windows.h>
#define TIMELIMIT 40000

namespace mystl
{
    template <class T>
    class queue
    {
    private:
        struct Node
        {
            T data;
            Node *next;
            Node() : next(nullptr) {}
        };
        Node *head, *tail;

    public:
        queue()
        {
            head = tail = nullptr;
        }
        void push(T a)
        {
            Node *newnode = new Node;
            newnode->data = a;
            newnode->next = nullptr;
            if (head == nullptr)
            {
                head = tail = newnode;
            }
            else
            {
                tail->next = newnode;
                tail = newnode;
            }
        }
        bool empty()
        {
            return head == nullptr;
        }
        T pop()
        {
            if (empty())
                throw "queue pop on empty";
            T a = head->data;
            Node *tmp = head;
            head = head->next;
            delete tmp;
            return a;
        }
        ~queue()
        {
            while (!empty())
                pop();
        }
    };

    template <class T>
    class stack
    {
    private:
        struct Node
        {
            T data;
            Node *next;
            Node() : next(nullptr) {}
        } *head;

    public:
        stack() : head(nullptr) {}
        void push(T a)
        {
            Node *newnode = new Node;
            newnode->data = a;
            newnode->next = head;
            head = newnode;
        }
        bool empty()
        {
            return head == nullptr;
        }
        T pop()
        {
            if (empty())
                throw "stack pop on empty";
            Node *p = head;
            T a = p->data;
            head = head->next;
            delete p;
            return a;
        }
        ~stack()
        {
            while (!empty())
                pop();
        }
    };
};

struct CNF
{
    bool solved;
    std::string path;
    clock_t start;
    int var_c = -1, cls_c = -1;
    double ms;
    bool flag;
    bool *value;
    
    // 新增：记录每个变元的正负出现情况
    int *positive_count;  // 正文字出现次数
    int *negative_count;  // 负文字出现次数
    
    struct Node
    {
        bool sign;
        bool status;
        int var, cls;
        Node *vnxt, *vpre, *cnxt, *cpre;
        Node() : sign(true), status(false), vnxt(nullptr), vpre(nullptr), cnxt(nullptr), cpre(nullptr), var(-1), cls(-1) {}
    };
    
    struct Title
    {
        int num;
        bool status;
        Node head;
        Title() : num(0), status(false) {}
    } *var, *cls;

    CNF() : var_c(-1), cls_c(-1), var(nullptr), cls(nullptr), flag(false), 
            value(nullptr), solved(false), positive_count(nullptr), negative_count(nullptr) {}

    ~CNF()
    {
        if (var) delete[] var;
        if (cls) delete[] cls;
        if (value) delete[] value;
        if (positive_count) delete[] positive_count;
        if (negative_count) delete[] negative_count;
    }

    void push(int c, int v, bool sign)
    {
        v = abs(v);
        Node *newnode = new Node;
        newnode->sign = sign;
        newnode->var = v;
        newnode->cls = c;
        newnode->cnxt = cls[c].head.cnxt;
        if (newnode->cnxt != nullptr)
            newnode->cnxt->cpre = newnode;
        cls[c].head.cnxt = newnode;
        newnode->cpre = &cls[c].head;
        cls[c].num++;

        newnode->vnxt = var[v].head.vnxt;
        if (newnode->vnxt != nullptr)
            newnode->vnxt->vpre = newnode;
        var[v].head.vnxt = newnode;
        newnode->vpre = &var[v].head;
        var[v].num++;
        
        // 更新正负计数
        if (sign)
            positive_count[v]++;
        else
            negative_count[v]++;
    }

    bool read(const char file[])
    {
        path = std::string(file);
        FILE *fin = fopen(file, "r");
        if (!fin)
        {
            throw "文件读取失败";
            return false;
        }
        int cl = 0;
        while (!feof(fin))
        {
            char buff[1000];
            fgets(buff, 1000, fin);
            if (*buff == 'c') continue;
            else if (*buff == 'p')
            {
                char format[100];
                char temp;
                sscanf(buff, "%c%s%d%d", &temp, format, &var_c, &cls_c);
                if (strcmp(format, "cnf") != 0)
                {
                    throw "CNF文件错误:文件类型错误";
                    return false;
                }
                if (var_c <= 0 || cls_c <= 0)
                {
                    throw "CNF文件错误:文件信息错误";
                    return false;
                }
                
                var = new Title[var_c + 1];
                cls = new Title[cls_c + 1];
                value = new bool[var_c + 1];
                positive_count = new int[var_c + 1];
                negative_count = new int[var_c + 1];
                
                memset(value, 0, (var_c + 1) * sizeof(bool));
                memset(positive_count, 0, (var_c + 1) * sizeof(int));
                memset(negative_count, 0, (var_c + 1) * sizeof(int));
            }
            else if (*buff >= '0' && *buff <= '9' || *buff == '-')
            {
                cl++;
                if (cl > cls_c) break;
                
                char *bp = buff;
                while (1)
                {
                    int a = 0, f = 1;
                    while (*bp != ' ' && *bp != '\n' && *bp != '\0' && *bp != '\r')
                    {
                        if (*bp == '-') f = -1;
                        else if (*bp >= '0' && *bp <= '9') a = a * 10 + *bp - '0';
                        else
                        {
                            throw "CNF文件错误:数字中含有非法字符";
                            return false;
                        }
                        bp++;
                    }
                    a *= f;
                    if (a == 0) break;
                    push(cl, a, a > 0);
                    if (*bp == '\0') break;
                    bp++;
                }
            }
        }
        fclose(fin);
        return true;
    }

    void del(Node *p, mystl::stack<Node *> &bp)
    {
        p->status = true;
        var[p->var].num--;
        cls[p->cls].num--;
        bp.push(p);
    }

    void rec(mystl::stack<Node *> &bp)
    {
        while (!bp.empty())
        {
            Node *p = bp.pop();
            if (!p->status)
                continue;
            p->status = false;
            var[p->var].num++;
            cls[p->cls].num++;
            var[p->var].status = false;
            cls[p->cls].status = false;
        }
    }

    void del_cls(int c, mystl::stack<Node *> &bp)
    {
        for (Node *i = cls[c].head.cnxt; i != nullptr; i = i->cnxt)
        {
            if (i->status)
                continue;
            del(i, bp);
            if (var[i->var].num == 0)
                var[i->var].status = true;
        }
        cls[c].status = true;
    }

    void del_var(int v, bool sign, mystl::stack<Node *> &bp)
    {
        value[v] = sign;
        for (Node *i = var[v].head.vnxt; i != nullptr; i = i->vnxt)
        {
            if (i->status)
                continue;
            if (sign ^ i->sign)
                del(i, bp);
            else
                del_cls(i->cls, bp);
        }
        var[v].status = true;
    }

    bool simplify(mystl::stack<Node *> &bp)
    {
        mystl::queue<int> q;
        for (int i = 1; i <= cls_c; i++)
        {
            if (cls[i].status)
                continue;
            if (cls[i].num == 0)
                return false;
            if (cls[i].num == 1)
                q.push(i);
        }

        while (!q.empty())
        {
            int c = q.pop();
            if (cls[c].status)
                continue;
            if (cls[c].num == 0)
                return false;

            int v;
            bool sign;
            for (Node *i = cls[c].head.cnxt; i != nullptr; i = i->cnxt)
            {
                if (i->status)
                    continue;
                v = i->var;
                sign = i->sign;
                break;
            }

            value[v] = sign;

            for (Node *i = var[v].head.vnxt; i != nullptr; i = i->vnxt)
            {
                if (i->status)
                    continue;
                if (sign ^ i->sign)
                {
                    del(i, bp);
                    if (cls[i->cls].num == 0)
                        return false;
                    if (cls[i->cls].num == 1)
                        q.push(i->cls);
                }
                else
                {
                    del_cls(i->cls, bp);
                }
            }
            var[v].status = true;
        }
        return true;
    }

    // 新增：优化变量选择策略 - 优先选择全为正或全为负的变元
    int select_optimal_variable()
    {
        int best_var = -1;
        int best_score = -1;
        
        for (int v = 1; v <= var_c; v++)
        {
            if (var[v].status) continue; // 跳过已赋值的变量
            
            // 计算分数：优先选择全为正或全为负的变量
            int score = 0;
            
            // 如果变量只以正文字出现
            if (negative_count[v] == 0 && positive_count[v] > 0)
            {
                score = 1000 + positive_count[v]; // 高优先级
            }
            // 如果变量只以负文字出现
            else if (positive_count[v] == 0 && negative_count[v] > 0)
            {
                score = 1000 + negative_count[v]; // 高优先级
            }
            // 如果变量既有正文字又有负文字
            else
            {
                // 选择出现次数更多的极性
                score = std::max(positive_count[v], negative_count[v]);
            }
            
            if (score > best_score)
            {
                best_score = score;
                best_var = v;
            }
        }
        
        // 如果没有找到合适的变量，使用第一个未赋值的变量
        if (best_var == -1)
        {
            for (int v = 1; v <= var_c; v++)
            {
                if (!var[v].status)
                    return v;
            }
        }
        
        return best_var;
    }

    // 新增：为选择的变量确定最佳赋值方向
    bool get_best_assignment(int v)
    {
        // 如果变量只以正文字出现，赋true
        if (negative_count[v] == 0 && positive_count[v] > 0)
            return true;
        
        // 如果变量只以负文字出现，赋false
        if (positive_count[v] == 0 && negative_count[v] > 0)
            return false;
        
        // 如果既有正文字又有负文字，选择出现次数更多的极性
        return positive_count[v] >= negative_count[v];
    }

    bool dpll()
    {
        ms = (clock() - start) * 1000 / CLOCKS_PER_SEC;
        if (ms >= TIMELIMIT)
            return false;

        mystl::stack<Node *> bp;
        if (!simplify(bp))
        {
            rec(bp);
            return false;
        }

        bool emp = true;
        for (int i = 1; i <= cls_c; i++)
        {
            if (!cls[i].status)
            {
                emp = false;
                break;
            }
        }
        
        if (emp)
            return true;

        // 使用优化策略选择变量
        int v = select_optimal_variable();
        if (v == -1) return true; // 所有变量都已赋值

        // 确定最佳赋值方向
        bool best_assignment = get_best_assignment(v);

        mystl::stack<Node *> branch;
        
        // 先尝试最佳赋值方向
        del_var(v, best_assignment, branch);
        if (dpll())
            return true;
        else
            rec(branch);

        // 再尝试相反方向
        del_var(v, !best_assignment, branch);
        if (dpll())
            return true;

        rec(branch);
        rec(bp);
        return false;
    }

    bool write(const char file[])
    {
        if (!solved)
        {
            throw "SAT not solved";
            return false;
        }
        std::fstream out(file, std::ios::out);
        if (ms >= TIMELIMIT)
        {
            out << "s -1\n";
        }
        else
        {
            out << "s " << (flag ? 1 : 0) << std::endl;
            if (flag)
            {
                out << "v";
                for (int i = 1; i <= var_c; i++)
                {
                    out << ' ' << (value[i] ? i : -i);
                }
                out << std::endl;
            }
        }
        out << "t " << ms << std::endl;
        return true;
    }

    void solve()
    {
        if (solved)
        {
            throw "SAT already solved";
            return;
        }
        solved = true;
        start = clock();
        flag = dpll();
        ms = (clock() - start) * 1000 / CLOCKS_PER_SEC;
    }
};

#endif
