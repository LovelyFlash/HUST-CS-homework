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

// 使用数组存储的CNF求解器实现
struct CNF
{
    // 状态标志（与主程序兼容）
    bool solved;      // 是否已求解
    bool timeout;     // 是否超时
    bool satisfiable; // 可满足性结果

    // 文件信息
    std::string file_path; // 文件路径

    // 时间统计
    clock_t start_time;       // 开始时间
    double execution_time_ms; // 执行时间（毫秒）

    // CNF基本信息（与主程序兼容）
    int variable_count; // 变量数量
    int clause_count;   // 子句数量

    // 求解结果（与主程序兼容）
    bool *variable_values; // 变量赋值结果

    // 统计信息
    int *positive_count; // 正文字出现次数
    int *negative_count; // 负文字出现次数

    // 使用数组存储的数据结构
    struct ClauseNode
    {
        int variable_index; // 变量索引
        bool is_positive;   // 是否为正文字
        bool is_deleted;    // 是否被删除
        int clause_index;   // 所属子句索引
    };

    struct VariableHeader
    {
        int active_count;    // 活跃出现次数
        bool is_deleted;     // 是否被删除
        int *clause_indices; // 出现的子句索引数组
        int clause_count;    // 出现的子句数量
    };

    struct ClauseHeader
    {
        int active_count;      // 活跃文字数量
        bool is_deleted;       // 是否被删除
        int *variable_indices; // 包含的变量索引数组
        bool *is_positive_arr; // 文字符号数组
        int literal_count;     // 文字数量
    };

    // 数据存储数组
    VariableHeader *variable_headers;
    ClauseHeader *clause_headers;
    ClauseNode *all_nodes; // 所有节点的连续存储
    int node_count;        // 总节点数量

    /**
     * @brief 默认构造函数
     */
    CNF() : variable_count(-1), clause_count(-1), variable_headers(nullptr),
            clause_headers(nullptr), all_nodes(nullptr), node_count(0),
            variable_values(nullptr), solved(false), timeout(false),
            satisfiable(false), positive_count(nullptr), negative_count(nullptr) {}

    /**
     * @brief 析构函数，释放所有动态分配的内存
     */
    ~CNF()
    {
        delete[] variable_headers;
        delete[] clause_headers;
        delete[] all_nodes;
        delete[] variable_values;
        delete[] positive_count;
        delete[] negative_count;

        // 释放二级数组
        if (variable_headers)
        {
            for (int i = 1; i <= variable_count; i++)
                delete[] variable_headers[i].clause_indices;
        }
        if (clause_headers)
        {
            for (int i = 1; i <= clause_count; i++)
            {
                delete[] clause_headers[i].variable_indices;
                delete[] clause_headers[i].is_positive_arr;
            }
        }
    }

    /**
     * @brief 读取CNF文件并构建数组数据结构
     * @param filename 文件路径
     * @return true 读取成功
     * @return false 读取失败
     */
    bool read_cnf_file(const char *filename)
    {
        file_path = filename;
        FILE *file = fopen(filename, "r");
        if (!file)
            return false;

        char buffer[1024];
        int current_clause = 0;
        int total_literals = 0;

        // 第一遍扫描：统计信息
        while (fgets(buffer, sizeof(buffer), file))
        {
            if (buffer[0] == 'c')
                continue;

            if (buffer[0] == 'p')
            {
                char format[10];
                if (sscanf(buffer, "p %s %d %d", format, &variable_count, &clause_count) != 3)
                    return false;

                if (strcmp(format, "cnf") != 0)
                    return false;

                // 分配主数组内存
                variable_headers = new VariableHeader[variable_count + 1];
                clause_headers = new ClauseHeader[clause_count + 1];
                variable_values = new bool[variable_count + 1]();
                positive_count = new int[variable_count + 1]();
                negative_count = new int[variable_count + 1]();

                // 初始化头信息
                for (int i = 1; i <= variable_count; i++)
                {
                    variable_headers[i].active_count = 0;
                    variable_headers[i].is_deleted = false;
                    variable_headers[i].clause_count = 0;
                }

                for (int i = 1; i <= clause_count; i++)
                {
                    clause_headers[i].active_count = 0;
                    clause_headers[i].is_deleted = false;
                    clause_headers[i].literal_count = 0;
                }
            }
            else if (isdigit(buffer[0]) || buffer[0] == '-')
            {
                current_clause++;
                if (current_clause > clause_count)
                    break;

                char *ptr = buffer;
                while (*ptr)
                {
                    int literal = 0;
                    int sign = 1;

                    // 跳过空白字符
                    while (*ptr == ' ' || *ptr == '\t')
                        ptr++;
                    if (*ptr == '-')
                    {
                        sign = -1;
                        ptr++;
                    }

                    // 解析数字
                    while (isdigit(*ptr))
                    {
                        literal = literal * 10 + (*ptr - '0');
                        ptr++;
                    }

                    if (literal == 0)
                        break;

                    literal *= sign;
                    int var_index = abs(literal);
                    bool is_pos = literal > 0;

                    // 更新计数
                    clause_headers[current_clause].literal_count++;
                    variable_headers[var_index].clause_count++;
                    total_literals++;

                    is_pos ? positive_count[var_index]++ : negative_count[var_index]++;

                    if (*ptr)
                        ptr++;
                }
            }
        }

        fclose(file);

        // 分配二级数组内存
        for (int i = 1; i <= variable_count; i++)
        {
            variable_headers[i].clause_indices = new int[variable_headers[i].clause_count];
            variable_headers[i].active_count = variable_headers[i].clause_count;
        }

        for (int i = 1; i <= clause_count; i++)
        {
            clause_headers[i].variable_indices = new int[clause_headers[i].literal_count];
            clause_headers[i].is_positive_arr = new bool[clause_headers[i].literal_count];
            clause_headers[i].active_count = clause_headers[i].literal_count;
        }

        // 分配节点数组
        all_nodes = new ClauseNode[total_literals];
        node_count = total_literals;

        // 第二遍扫描：填充数据
        file = fopen(filename, "r");
        current_clause = 0;
        int node_index = 0;
        int *var_pos = new int[variable_count + 1]();
        int *cls_pos = new int[clause_count + 1]();

        while (fgets(buffer, sizeof(buffer), file))
        {
            if (buffer[0] == 'c' || buffer[0] == 'p')
                continue;

            if (isdigit(buffer[0]) || buffer[0] == '-')
            {
                current_clause++;
                if (current_clause > clause_count)
                    break;

                char *ptr = buffer;
                while (*ptr)
                {
                    int literal = 0;
                    int sign = 1;

                    while (*ptr == ' ' || *ptr == '\t')
                        ptr++;
                    if (*ptr == '-')
                    {
                        sign = -1;
                        ptr++;
                    }

                    while (isdigit(*ptr))
                    {
                        literal = literal * 10 + (*ptr - '0');
                        ptr++;
                    }

                    if (literal == 0)
                        break;

                    literal *= sign;
                    int var_index = abs(literal);
                    bool is_pos = literal > 0;

                    // 创建节点
                    all_nodes[node_index].variable_index = var_index;
                    all_nodes[node_index].is_positive = is_pos;
                    all_nodes[node_index].is_deleted = false;
                    all_nodes[node_index].clause_index = current_clause;

                    // 填充变量头信息
                    variable_headers[var_index].clause_indices[var_pos[var_index]++] = current_clause;

                    // 填充子句头信息
                    clause_headers[current_clause].variable_indices[cls_pos[current_clause]] = var_index;
                    clause_headers[current_clause].is_positive_arr[cls_pos[current_clause]] = is_pos;
                    cls_pos[current_clause]++;

                    node_index++;
                    if (*ptr)
                        ptr++;
                }
            }
        }

        fclose(file);
        delete[] var_pos;
        delete[] cls_pos;
        return true;
    }

    /**
     * @brief 标记节点为删除状态
     */
    void mark_node_deleted(int node_idx)
    {
        if (all_nodes[node_idx].is_deleted)
            return;

        all_nodes[node_idx].is_deleted = true;
        int var_idx = all_nodes[node_idx].variable_index;
        int cls_idx = all_nodes[node_idx].clause_index;

        variable_headers[var_idx].active_count--;
        clause_headers[cls_idx].active_count--;

        // 如果变量不再活跃，标记为删除
        if (variable_headers[var_idx].active_count == 0)
            variable_headers[var_idx].is_deleted = true;

        // 如果子句不再活跃，标记为删除
        if (clause_headers[cls_idx].active_count == 0)
            clause_headers[cls_idx].is_deleted = true;
    }

    /**
     * @brief 恢复节点状态
     */
    void restore_node(int node_idx)
    {
        if (!all_nodes[node_idx].is_deleted)
            return;

        all_nodes[node_idx].is_deleted = false;
        int var_idx = all_nodes[node_idx].variable_index;
        int cls_idx = all_nodes[node_idx].clause_index;

        variable_headers[var_idx].active_count++;
        clause_headers[cls_idx].active_count++;

        // 取消删除标记
        variable_headers[var_idx].is_deleted = false;
        clause_headers[cls_idx].is_deleted = false;
    }

    /**
     * @brief 为变量赋值并传播影响
     */
    void assign_variable(int var_index, bool value, int *backtrack_stack, int &stack_top)
    {
        variable_values[var_index] = value;
        variable_headers[var_index].is_deleted = true;

        // 处理该变量的所有出现
        for (int i = 0; i < variable_headers[var_index].clause_count; i++)
        {
            int cls_idx = variable_headers[var_index].clause_indices[i];
            if (clause_headers[cls_idx].is_deleted)
                continue;

            // 查找该变量在子句中的位置
            for (int j = 0; j < clause_headers[cls_idx].literal_count; j++)
            {
                if (clause_headers[cls_idx].variable_indices[j] == var_index)
                {
                    bool literal_value = clause_headers[cls_idx].is_positive_arr[j];

                    if ((value && literal_value) || (!value && !literal_value))
                    {
                        // 满足整个子句，删除子句
                        clause_headers[cls_idx].is_deleted = true;
                        backtrack_stack[stack_top++] = -cls_idx; // 负值表示子句删除
                    }
                    else
                    {
                        // 不满足该文字，删除文字
                        // 需要找到对应的节点索引（这里简化处理）
                        for (int k = 0; k < node_count; k++)
                        {
                            if (all_nodes[k].clause_index == cls_idx &&
                                all_nodes[k].variable_index == var_index)
                            {
                                mark_node_deleted(k);
                                backtrack_stack[stack_top++] = k;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    /**
     * @brief 单子句传播
     */
    bool unit_propagation(int *backtrack_stack, int &stack_top)
    {
        bool changed;
        do
        {
            changed = false;
            for (int i = 1; i <= clause_count; i++)
            {
                if (clause_headers[i].is_deleted || clause_headers[i].active_count != 1)
                    continue;

                // 找到单子句中的唯一文字
                int var_index = 0;
                bool literal_value = false;

                for (int j = 0; j < clause_headers[i].literal_count; j++)
                {
                    if (!all_nodes[find_node_index(i, clause_headers[i].variable_indices[j])].is_deleted)
                    {
                        var_index = clause_headers[i].variable_indices[j];
                        literal_value = clause_headers[i].is_positive_arr[j];
                        break;
                    }
                }

                if (var_index == 0)
                    continue;

                // 赋值并传播
                assign_variable(var_index, literal_value, backtrack_stack, stack_top);
                changed = true;

                // 检查冲突
                for (int j = 1; j <= clause_count; j++)
                {
                    if (!clause_headers[j].is_deleted && clause_headers[j].active_count == 0)
                        return false; // 冲突
                }
            }
        } while (changed);

        return true;
    }

    /**
     * @brief 纯字面消去
     */
    bool pure_literal_elimination(int *backtrack_stack, int &stack_top)
    {
        for (int i = 1; i <= variable_count; i++)
        {
            if (variable_headers[i].is_deleted)
                continue;

            bool has_positive = false;
            bool has_negative = false;

            // 检查变量的极性
            for (int j = 0; j < variable_headers[i].clause_count; j++)
            {
                int cls_idx = variable_headers[i].clause_indices[j];
                if (clause_headers[cls_idx].is_deleted)
                    continue;

                for (int k = 0; k < clause_headers[cls_idx].literal_count; k++)
                {
                    if (clause_headers[cls_idx].variable_indices[k] == i)
                    {
                        if (clause_headers[cls_idx].is_positive_arr[k])
                            has_positive = true;
                        else
                            has_negative = true;
                        break;
                    }
                }

                if (has_positive && has_negative)
                    break;
            }

            // 如果是纯字面
            if (has_positive != has_negative)
            {
                assign_variable(i, has_positive, backtrack_stack, stack_top);
            }
        }

        return true;
    }

    /**
     * @brief 查找节点索引
     */
    int find_node_index(int clause_index, int variable_index)
    {
        for (int i = 0; i < node_count; i++)
        {
            if (all_nodes[i].clause_index == clause_index &&
                all_nodes[i].variable_index == variable_index)
            {
                return i;
            }
        }
        return -1;
    }

    /**
     * @brief 选择分支变量
     */
    int choose_branch_variable()
    {
        int best_var = -1;
        int max_count = -1;

        for (int i = 1; i <= variable_count; i++)
        {
            if (variable_headers[i].is_deleted)
                continue;

            if (variable_headers[i].active_count > max_count)
            {
                max_count = variable_headers[i].active_count;
                best_var = i;
            }
        }

        return best_var;
    }

    /**
     * @brief 确定最佳赋值方向
     */
    bool get_best_assignment(int variable_index)
    {
        return positive_count[variable_index] >= negative_count[variable_index];
    }

    /**
     * @brief DPLL算法核心
     */
    bool dpll_recursive()
    {
        // 检查超时
        if ((clock() - start_time) * 1000 / CLOCKS_PER_SEC >= TIMELIMIT)
        {
            timeout = true;
            return false;
        }

        // 使用数组作为回溯栈
        int *backtrack_stack = new int[node_count * 2];
        int stack_top = 0;

        // 单子句传播
        if (!unit_propagation(backtrack_stack, stack_top))
        {
            // 回溯
            while (stack_top > 0)
            {
                int item = backtrack_stack[--stack_top];
                if (item < 0)
                {
                    // 恢复子句
                    clause_headers[-item].is_deleted = false;
                }
                else
                {
                    // 恢复节点
                    restore_node(item);
                }
            }
            delete[] backtrack_stack;
            return false;
        }

        // 纯字面消去
        if (!pure_literal_elimination(backtrack_stack, stack_top))
        {
            // 回溯
            while (stack_top > 0)
            {
                int item = backtrack_stack[--stack_top];
                if (item < 0)
                {
                    clause_headers[-item].is_deleted = false;
                }
                else
                {
                    restore_node(item);
                }
            }
            delete[] backtrack_stack;
            return false;
        }

        // 检查是否所有子句都已满足
        bool all_satisfied = true;
        for (int i = 1; i <= clause_count; i++)
        {
            if (!clause_headers[i].is_deleted)
            {

                all_satisfied = false;
                break;
            }
        }

        if (all_satisfied)
        {
            delete[] backtrack_stack;
            return true;
        }

        // 选择分支变量
        int branch_var = choose_branch_variable();
        if (branch_var == -1)
        {
            // 回溯
            while (stack_top > 0)
            {
                int item = backtrack_stack[--stack_top];
                if (item < 0)
                {
                    clause_headers[-item].is_deleted = false;
                }
                else
                {
                    restore_node(item);
                }
            }
            delete[] backtrack_stack;
            return false;
        }

        bool assignment = get_best_assignment(branch_var);

        // 尝试第一个分支
        int *branch_stack1 = new int[node_count * 2];
        int stack_top1 = 0;
        assign_variable(branch_var, assignment, branch_stack1, stack_top1);

        if (dpll_recursive())
        {
            delete[] backtrack_stack;
            delete[] branch_stack1;
            return true;
        }

        // 回溯第一个分支
        while (stack_top1 > 0)
        {
            int item = branch_stack1[--stack_top1];
            if (item < 0)
            {
                clause_headers[-item].is_deleted = false;
            }
            else
            {
                restore_node(item);
            }
        }
        variable_headers[branch_var].is_deleted = false;
        delete[] branch_stack1;

        // 尝试第二个分支
        int *branch_stack2 = new int[node_count * 2];
        int stack_top2 = 0;
        assign_variable(branch_var, !assignment, branch_stack2, stack_top2);

        if (dpll_recursive())
        {
            delete[] backtrack_stack;
            delete[] branch_stack2;
            return true;
        }

        // 回溯第二个分支
        while (stack_top2 > 0)
        {
            int item = branch_stack2[--stack_top2];
            if (item < 0)
            {
                clause_headers[-item].is_deleted = false;
            }
            else
            {
                restore_node(item);
            }
        }
        variable_headers[branch_var].is_deleted = false;
        delete[] branch_stack2;

        // 回溯当前层的传播操作
        while (stack_top > 0)
        {
            int item = backtrack_stack[--stack_top];
            if (item < 0)
            {
                clause_headers[-item].is_deleted = false;
            }
            else
            {
                restore_node(item);
            }
        }

        delete[] backtrack_stack;
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
        start_time = clock();
        satisfiable = dpll_recursive();
        execution_time_ms = (clock() - start_time) * 1000.0 / CLOCKS_PER_SEC;
    }

    /**
     * @brief 输出求解结果到文件
     */
    bool write_result(const char *filename)
    {
        if (!solved)
            return false;

        std::ofstream out(filename);
        if (timeout)
        {
            out << "s -1\n";
        }
        else
        {
            out << "s " << (satisfiable ? 1 : 0) << "\n";
            if (satisfiable)
            {
                out << "v";
                for (int i = 1; i <= variable_count; i++)
                {
                    out << " " << (variable_values[i] ? i : -i);
                }
                out << "\n";
            }
        }
        out << "t " << execution_time_ms << "\n";
        return true;
    }

    /**
     * @brief 便捷构造函数
     */
    CNF(const char *filename) : CNF()
    {
        read_cnf_file(filename);
    }

    // 与主程序兼容的接口方法
    int get_variable_count() const { return variable_count; }
    int get_clause_count() const { return clause_count; }
    bool is_satisfiable() const { return satisfiable; }
    bool is_timeout() const { return timeout; }
    double get_execution_time() const { return execution_time_ms; }
    const bool *get_variable_values() const { return variable_values; }
    const std::string &get_file_path() const { return file_path; }
};

#endif // __DPLL_OPTIMIZED__
