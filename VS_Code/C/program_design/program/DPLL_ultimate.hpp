#ifndef __DPLL_OPTIMIZED__
#define __DPLL_OPTIMIZED__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <windows.h>

#define TIMELIMIT 20000 // 超时时间限制（毫秒）

namespace mystl
{
    /**
     * @brief 简单的队列实现
     * @tparam T 队列元素类型
     */
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
        Node *head, *tail; // 队列头尾指针

    public:
        queue() : head(nullptr), tail(nullptr) {}

        /**
         * @brief 向队列尾部添加元素
         * @param a 要添加的元素
         */
        void push(T a)
        {
            Node *newnode = new Node;
            newnode->data = a;
            if (!head)
                head = tail = newnode;
            else
                tail = tail->next = newnode;
        }

        /**
         * @brief 检查队列是否为空
         * @return true 队列为空
         */
        bool empty() { return !head; }

        /**
         * @brief 从队列头部移除并返回元素
         * @return 队列头部元素
         * @throws 队列为空时抛出异常
         */
        T pop()
        {
            if (empty())
                throw "queue empty";
            T data = head->data;
            Node *temp = head;
            head = head->next;
            delete temp;
            if (!head)
                tail = nullptr;
            return data;
        }
    };

    /**
     * @brief 简单的栈实现
     * @tparam T 栈元素类型
     */
    template <class T>
    class stack
    {
    private:
        struct Node
        {
            T data;
            Node *next;
            Node() : next(nullptr) {}
        } *top; // 栈顶指针

    public:
        stack() : top(nullptr) {}

        /**
         * @brief 向栈顶压入元素
         * @param a 要压入的元素
         */
        void push(T a)
        {
            Node *newnode = new Node;
            newnode->data = a;
            newnode->next = top;
            top = newnode;
        }

        /**
         * @brief 检查栈是否为空
         * @return true 栈为空
         */
        bool empty() { return !top; }

        /**
         * @brief 从栈顶弹出并返回元素
         * @return 栈顶元素
         * @throws 栈为空时抛出异常
         */
        T pop()
        {
            if (empty())
                throw "stack empty";
            T data = top->data;
            Node *temp = top;
            top = top->next;
            delete temp;
            return data;
        }
    };
}

/**
 * @brief CNF公式求解器类，实现DPLL算法
 */
struct CNF
{
    // 状态标志
    bool solved;  // 是否已求解
    bool timeout; // 是否超时

    // 文件信息
    std::string path; // 文件路径

    // 时间统计
    clock_t start; // 开始时间
    double ms;     // 执行时间（毫秒）

    // CNF基本信息
    int var_c; // 变量数量
    int cls_c; // 子句数量

    // 求解结果
    bool flag;   // 可满足性标志
    bool *value; // 变量赋值结果

    // 统计信息
    int *pos_cnt; // 正文字出现次数
    int *neg_cnt; // 负文字出现次数

    /**
     * @brief CNF公式节点结构，表示文字在公式中的出现
     */
    struct Node
    {
        bool sign;   // 文字符号（true为正，false为负）
        bool status; // 节点状态（是否被删除）
        int var;     // 变量索引
        int cls;     // 子句索引
        Node *vnxt;  // 同一变量的下一个文字
        Node *vpre;  // 同一变量的前一个文字
        Node *cnxt;  // 同一子句的下一个文字
        Node *cpre;  // 同一子句的前一个文字

        Node() : sign(true), status(false), vnxt(nullptr), vpre(nullptr),
                 cnxt(nullptr), cpre(nullptr), var(-1), cls(-1) {}
    };

    /**
     * @brief 链表头结构，用于管理变量和子句
     */
    struct Title
    {
        int num;     // 活跃节点数量
        bool status; // 是否被删除
        Node head;   // 链表头节点

        Title() : num(0), status(false) {}
    } *var, *cls; // 变量链表头和子句链表头

    /**
     * @brief 默认构造函数
     */
    CNF() : var_c(-1), cls_c(-1), var(nullptr), cls(nullptr), flag(false),
            value(nullptr), solved(false), timeout(false), pos_cnt(nullptr), neg_cnt(nullptr) {}

    /**
     * @brief 析构函数，释放所有动态分配的内存
     */
    ~CNF()
    {
        // 释放所有节点
        for (int i = 1; i <= var_c; i++)
        {
            Node *p = var[i].head.vnxt;
            while (p)
            {
                Node *temp = p;
                p = p->vnxt;
                delete temp;
            }
        }

        delete[] var;
        delete[] cls;
        delete[] value;
        delete[] pos_cnt;
        delete[] neg_cnt;
    }

    /**
     * @brief 向CNF公式中添加一个文字
     * @param c 子句索引
     * @param v 文字值（可为正负）
     * @param sign 文字符号
     */
    void push(int c, int v, bool sign)
    {
        v = abs(v); // 取绝对值得到变量索引

        Node *newnode = new Node;
        newnode->sign = sign;
        newnode->var = v;
        newnode->cls = c;

        // 添加到子句链表
        newnode->cnxt = cls[c].head.cnxt;
        if (newnode->cnxt)
            newnode->cnxt->cpre = newnode;
        cls[c].head.cnxt = newnode;
        newnode->cpre = &cls[c].head;
        cls[c].num++;

        // 添加到变量链表
        newnode->vnxt = var[v].head.vnxt;
        if (newnode->vnxt)
            newnode->vnxt->vpre = newnode;
        var[v].head.vnxt = newnode;
        newnode->vpre = &var[v].head;
        var[v].num++;

        // 更新出现次数统计
        sign ? pos_cnt[v]++ : neg_cnt[v]++;
    }

    /**
     * @brief 读取CNF文件并构建数据结构
     * @param file 文件路径
     * @return true 读取成功
     * @return false 读取失败
     */
    bool read(const char file[])
    {
        path = file;
        FILE *fin = fopen(file, "r");
        if (!fin)
            return false;

        int cl = 0; // 当前子句索引
        char buff[1024];

        while (fgets(buff, sizeof(buff), fin))
        {
            if (buff[0] == 'c')
                continue; // 跳过注释行

            if (buff[0] == 'p') // 文件头信息
            {
                char fmt[10];
                sscanf(buff, "p %s %d %d", fmt, &var_c, &cls_c);
                if (strcmp(fmt, "cnf") != 0 || var_c <= 0 || cls_c <= 0)
                    return false;

                // 分配内存
                var = new Title[var_c + 1];
                cls = new Title[cls_c + 1];
                value = new bool[var_c + 1]();  // 初始化为false
                pos_cnt = new int[var_c + 1](); // 初始化为0
                neg_cnt = new int[var_c + 1](); // 初始化为0
            }
            else if (isdigit(buff[0]) || buff[0] == '-') // 子句数据
            {
                if (++cl > cls_c)
                    break; // 忽略多余子句

                char *p = buff;
                while (*p)
                {
                    int num = 0, sign = 1;
                    while (*p == ' ' || *p == '\t')
                        p++; // 跳过空白字符
                    if (*p == '-')
                        sign = -1, p++; // 处理负号

                    while (isdigit(*p))
                        num = num * 10 + (*p++ - '0'); // 解析数字
                    num *= sign;

                    if (num == 0)
                        break;              // 子句结束标记
                    push(cl, num, num > 0); // 添加文字
                    if (*p)
                        p++;
                }
            }
        }
        fclose(fin);
        return true;
    }

    /**
     * @brief 标记节点为删除状态
     * @param p 要删除的节点
     * @param bp 回溯栈，用于记录删除操作
     */
    void del(Node *p, mystl::stack<Node *> &bp)
    {
        p->status = true;
        var[p->var].num--;
        cls[p->cls].num--;
        bp.push(p); // 记录删除操作以便回溯
    }

    /**
     * @brief 恢复被删除的节点状态
     * @param bp 回溯栈，包含要恢复的删除操作
     */
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
        }
    }

    /**
     * @brief 删除整个子句
     * @param c 子句索引
     * @param bp 回溯栈
     */
    void del_cls(int c, mystl::stack<Node *> &bp)
    {
        if (cls[c].status)
            return; // 子句已经被删除

        cls[c].status = true;
        for (Node *i = cls[c].head.cnxt; i; i = i->cnxt)
        {
            if (!i->status)
                del(i, bp);
        }
    }

    /**
     * @brief 为变量赋值并传播影响
     * @param v 变量索引
     * @param sign 赋值（true或false）
     * @param bp 回溯栈
     */
    void del_var(int v, bool sign, mystl::stack<Node *> &bp)
    {
        value[v] = sign;
        for (Node *i = var[v].head.vnxt; i; i = i->vnxt)
        {
            if (i->status)
                continue;
            // 如果赋值与文字符号相反，删除文字；否则删除整个子句
            (sign ^ i->sign) ? del(i, bp) : del_cls(i->cls, bp);
        }
        var[v].status = true;
    }

    /**
     * @brief 单子句传播过程
     * @param bp 回溯栈
     * @return true 传播成功
     * @return false 发现冲突
     */
    bool simplify(mystl::stack<Node *> &bp)
    {
        bool changed;
        do
        {
            changed = false;
            mystl::queue<int> q;

            // 收集所有单子句
            for (int i = 1; i <= cls_c; i++)
            {
                if (!cls[i].status && cls[i].num == 1)
                    q.push(i);
            }

            while (!q.empty())
            {
                int c = q.pop();
                if (cls[c].status)
                    continue; // 子句已被删除，跳过

                if (cls[c].num == 0)
                    return false; // 空子句冲突

                // 找到单子句中的唯一文字
                Node *unit = nullptr;
                for (Node *i = cls[c].head.cnxt; i; i = i->cnxt)
                {
                    if (!i->status)
                    {
                        if (unit)
                        {
                            // 不应该有多个活跃文字
                            return false;
                        }
                        unit = i;
                    }
                }

                if (!unit)
                {
                    // 没有活跃文字，但num不为0，状态不一致
                    return false;
                }

                int v = unit->var;
                bool sign = unit->sign;

                // 如果变量已经被赋值，检查是否一致
                if (var[v].status)
                {
                    if (value[v] != sign)
                        return false; // 冲突
                    continue;
                }

                value[v] = sign;
                var[v].status = true;

                // 传播赋值影响
                for (Node *i = var[v].head.vnxt; i; i = i->vnxt)
                {
                    if (i->status)
                        continue;

                    if (sign ^ i->sign) // 赋值与文字符号相反
                    {
                        del(i, bp);
                        if (cls[i->cls].num == 0)
                            return false; // 产生空子句
                        if (cls[i->cls].num == 1 && !cls[i->cls].status)
                        {
                            q.push(i->cls); // 产生新的单子句
                            changed = true;
                        }
                    }
                    else
                    {
                        // 赋值满足整个子句
                        del_cls(i->cls, bp);
                    }
                }
            }
        } while (changed); // 继续循环直到没有新的单子句产生

        return true;
    }

    /**
     * @brief 纯字面消去过程
     * @param bp 回溯栈
     * @return true 消去成功
     * @return false 发现冲突
     */
    bool pure_elimination(mystl::stack<Node *> &bp)
    {
        bool changed;
        do
        {
            changed = false;
            for (int v = 1; v <= var_c; v++)
            {
                if (var[v].status)
                    continue;

                // 检查变量是否为纯字面
                int mask = 0;
                for (Node *p = var[v].head.vnxt; p && mask != 3; p = p->vnxt)
                {
                    if (p->status)
                        continue;
                    p->sign ? mask |= 1 : mask |= 2; // 1: 正文字, 2: 负文字
                }

                // 如果是纯字面（只有正文字或只有负文字）
                if (mask == 1 || mask == 2)
                {
                    mystl::stack<Node *> tmp;
                    del_var(v, mask == 1, tmp); // 赋值为纯字面的符号
                    while (!tmp.empty())
                        bp.push(tmp.pop()); // 合并到主回溯栈
                    changed = true;
                }
            }
        } while (changed); // 继续循环直到没有新的纯字面产生
        return true;
    }

    /**
     * @brief 选择分支变量（启发式）
     * @return int 选择的变量索引，-1表示无可用变量
     */
    int choose_var()
    {
        int best_v = -1, best_cnt = -1;
        for (int v = 1; v <= var_c; v++)
        {
            if (var[v].status)
                continue;
            // 选择出现次数最多的变量
            if (var[v].num > best_cnt)
                best_cnt = var[v].num, best_v = v;
        }
        return best_v;
    }

    /**
     * @brief 确定变量的最佳赋值方向
     * @param v 变量索引
     * @return bool 建议的赋值（true或false）
     */
    bool get_best_assign(int v)
    {
        return pos_cnt[v] >= neg_cnt[v]; // 选择出现次数更多的极性
    }

    /**
     * @brief DPLL算法递归实现
     * @return true 公式可满足
     * @return false 公式不可满足
     */
    bool dpll()
    {
        // 检查超时
        if ((clock() - start) * 1000 / CLOCKS_PER_SEC >= TIMELIMIT)
            return timeout = true;

        mystl::stack<Node *> bp; // 回溯栈

        // 执行单子句传播和纯字面消去
        if (!simplify(bp) || !pure_elimination(bp))
        {
            rec(bp);
            return false;
        }

        // 再次检查超时
        if ((clock() - start) * 1000 / CLOCKS_PER_SEC >= TIMELIMIT)
        {
            rec(bp);
            return timeout = true;
        }

        // 检查是否所有子句都已满足
        for (int i = 1; i <= cls_c; i++)
            if (!cls[i].status)
                goto not_satisfied;
        return true;

    not_satisfied:
        // 选择分支变量
        int v = choose_var();
        if (v == -1)
        {
            rec(bp);
            return false;
        } // 无可用变量

        bool assign = get_best_assign(v);
        mystl::stack<Node *> branch;

        // 尝试第一个分支
        del_var(v, assign, branch);
        if (dpll())
            return true;
        rec(branch);

        // 再次检查超时
        if ((clock() - start) * 1000 / CLOCKS_PER_SEC >= TIMELIMIT)
        {
            rec(bp);
            return timeout = true;
        }

        // 尝试第二个分支
        del_var(v, !assign, branch);
        if (dpll())
            return true;
        rec(branch);

        // 回溯
        rec(bp);
        return false;
    }

    /**
     * @brief 求解CNF公式
     */
    void solve()
    {
        if (solved)
            return;
        solved = true;
        start = clock();
        flag = dpll();
        ms = (clock() - start) * 1000.0 / CLOCKS_PER_SEC;
    }

    /**
     * @brief 将求解结果写入文件
     * @param file 输出文件路径
     * @return true 写入成功
     * @return false 写入失败
     */
    bool write(const char file[])
    {
        if (!solved)
            return false;

        std::ofstream out(file);
        if (ms >= TIMELIMIT)
            out << "s -1\n"; // 超时标记
        else
        {
            out << "s " << flag << "\n"; // 可满足性结果
            if (flag)                    // 如果可满足，输出赋值
            {
                out << "v";
                for (int i = 1; i <= var_c; i++)
                    out << " " << (value[i] ? i : -i);
                out << "\n";
            }
        }
        out << "t " << ms << "\n"; // 执行时间
        return true;
    }

    /**
     * @brief 便捷构造函数，从文件构造CNF对象
     * @param file CNF文件路径
     */
    CNF(const char file[]) : CNF() { read(file); }
};

#endif // __DPLL_OPTIMIZED__
