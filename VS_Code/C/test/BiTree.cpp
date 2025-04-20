#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
#define _TraverseByStack true // 是否启用基于栈的树遍历
#define _Bin true             // 是否启用二进制读写文件
const string funcs[] = {
    "1.Exit",
    "2.InitByPreorderTraversalWithNullnode",
    "3.IniteByPreorderAndInorderTraversal",
    "4.InitByPostorderAndInorderTraversal",
    "5.InitAsEmptyTree",
    "6.DestroyBiTree",
    "7.ClearBiTree",
    "8.BiTreeEmpty",
    "9.BiTreeDepth",
    "10.LocateNode",
    "11.Assign",
    "12.GetSibling",
    "13.InsertNode",
    "14.DeleteNode",
    "15.PreorderTravers",
    "16.InorderTravers",
    "17.PostorderTravers",
    "18.LevelOrderTraverse",
    "19.MaxPathSum",
    "20.LowestCommonAncestor",
    "21.InvertTree",
    "22.save",
    "23.load",
    "24.showTrees",
};

#if _Bin
// 由于对包含string类的结构经行二进制读写时实际读写的是地址，需要自己定义兼容string的二进制读写方法
template <typename T, typename Enable = void>
struct bstream;

// 基础类型特化
template <typename T>
struct bstream<T,
               std::enable_if_t<
                   std::is_trivially_copyable_v<T> &&
                   !std::is_class_v<T> &&
                   !std::is_pointer_v<T>>>
{
    static void write(std::ostream &out, const T &value)
    {
        out.write((const char *)(&value), sizeof(T));
        if (!out)
            throw std::runtime_error("Failed to write basic type.");
    }
    static void read(std::istream &in, T &value)
    {
        in.read((char *)(&value), sizeof(T));
        if (!in)
            throw std::runtime_error("Failed to read basic type.");
    }
};

// std::string特化
template <>
struct bstream<std::string>
{
    static void write(std::ostream &out, const std::string &value)
    {
        size_t size = value.size();
        out.write((const char *)(&size), sizeof(size));
        out.write(value.data(), size);
        if (!out)
            throw std::runtime_error("Failed to write string.");
    }
    static void read(std::istream &in, std::string &value)
    {
        size_t size;
        in.read((char *)(&size), sizeof(size));
        if (!in)
            throw std::runtime_error("Failed to read string size.");
        value.resize(size);
        in.read(&value[0], size);
        if (!in)
            throw std::runtime_error("Failed to read string data.");
    }
};

// 用户自定义类
template <typename T>
struct bstream<T,
               std::enable_if_t<std::is_class_v<T> && !std::is_trivially_copyable_v<T>>>
{
    static void write(std::ostream &out, const T &obj)
    {
        obj.write(out);
    }
    static void read(std::istream &in, T &obj)
    {
        obj.read(in);
    }
};
#endif

template <class T1, class T2>
class BiTree
{
private:
    T1 key;
    T2 data;
    BiTree *left, *right;

public:
    BiTree() : key(0), data(0), left(nullptr), right(nullptr) {}

#if _Bin
    void write(ostream &out) const
    {
        bstream<T1>::write(out, this->key);
        bstream<T2>::write(out, this->data);
    }
    void read(istream &in)
    {
        bstream<T1>::read(in, this->key);
        bstream<T2>::read(in, this->data);
    }
#endif

    friend ostream &operator<<(ostream &out, const BiTree &bt)
    {
        out << bt.key << " " << bt.data;
        return out;
    }
    friend istream &operator>>(istream &in, BiTree &bt)
    {
        in >> bt.key >> bt.data;
        return in;
    }

    void DestroyBiTree()
    {
        if (this->left != nullptr)
            this->left->DestroyBiTree();
        if (this->right != nullptr)
            this->right->DestroyBiTree();
        delete this;
    }
    bool InitByPreorderTraversalWithNullnode(queue<pair<T1, T2>> &sq, const T1 nullnode)
    {
        stack<BiTree **> st;
        BiTree *head = this;
        st.push(&head);
        while (!sq.empty())
        {
            if (st.empty())
            {
                return false;
            }
            pair<T1, T2> value = sq.front();
            sq.pop();
            BiTree **node = st.top();
            st.pop();
            if (value.first == nullnode)
                continue;
            if (*node == nullptr)
                *node = new BiTree;
            (*node)->key = value.first;
            (*node)->data = value.second;
            st.push(&((*node)->right));
            st.push(&((*node)->left));
        }
        if (!st.empty())
        {
            return false;
        }
        return true;
    }
    bool InitByPreorderAndInorderTraversal(vector<pair<T1, T2>> &psq, vector<pair<T1, T2>> &isq, size_t pl, size_t pr, size_t il, size_t ir)
    {
        if (pr < pl || ir < il)
            return false;
        pair<T1, T2> pit = psq[pl];
        this->key = pit.first;
        this->data = pit.second;
        size_t k = il;
        while (k <= ir && isq[k].first != pit.first)
            k++;
        if (k > ir)
            return false;
        bool flag = true;
        if (k > il)
        {
            this->left = new BiTree;
            flag = flag && this->left->InitByPreorderAndInorderTraversal(psq, isq, pl + 1, pl + k - il, il, k - 1);
        }
        if (k < ir)
        {
            this->right = new BiTree;
            flag = flag && this->right->InitByPreorderAndInorderTraversal(psq, isq, pl + k - il + 1, pr, k + 1, ir);
        }
        return flag;
    }
    bool InitByPostorderAndInorderTraversal(vector<pair<T1, T2>> &psq, vector<pair<T1, T2>> &isq, size_t pl, size_t pr, size_t il, size_t ir)
    {
        if (pr < pl || ir < il)
            return false;
        pair<T1, T2> pit = psq[pr];
        this->key = pit.first;
        this->data = pit.second;
        size_t k = il;
        while (k <= ir && isq[k].first != pit.first)
            k++;
        if (k > ir)
            return false;
        bool flag = true;
        if (k > il)
        {
            this->left = new BiTree;
            flag = flag && this->left->InitByPostorderAndInorderTraversal(psq, isq, pl, pl + k - il - 1, il, k - 1);
        }
        if (k < ir)
        {
            this->right = new BiTree;
            flag = flag && this->right->InitByPostorderAndInorderTraversal(psq, isq, pl + k - il, pr - 1, k + 1, ir);
        }
        return flag;
    }
    void ClearBiTree()
    {
        if (this->left != nullptr)
            this->left->DestroyBiTree();
        if (this->right != nullptr)
            this->right->DestroyBiTree();
        this->key = 0;
        this->data = T2(0);
        this->left = nullptr;
        this->right = nullptr;
    }
    bool BiTreeEmpty()
    {
        return this->left == nullptr && this->right == nullptr && this->key == 0;
    }
    size_t BiTreeDepth()
    {
        if (this->key == 0)
            return 0;
        return max((this->left == nullptr ? 0 : this->left->BiTreeDepth()), (this->right == nullptr ? 0 : this->right->BiTreeDepth())) + 1;
    }
    BiTree *LocateNode(const T1 &e)
    {
        if (this->key == e)
            return this;
        BiTree *tmp = nullptr;
        if (this->left != nullptr)
            tmp = this->left->LocateNode(e);
        if (tmp != nullptr)
            return tmp;
        if (this->right != nullptr)
            tmp = this->right->LocateNode(e);
        return tmp;
    }
    bool Assign(const T1 &e, const T2 &value)
    {
        BiTree *tmp = this->LocateNode(e);
        if (tmp == nullptr)
            return false;
        tmp->data = value;
        return true;
    }
    BiTree *GetFather(const T1 &e, char &pos)
    {
        stack<BiTree *> st;
        st.push(this);
        while (!st.empty())
        {
            BiTree *node = st.top();
            st.pop();
            if (node == nullptr)
                continue;
            if (node->left != nullptr && node->left->key == e)
            {
                pos = 'L';
                return node;
            }
            if (node->right != nullptr && node->right->key == e)
            {
                pos = 'R';
                return node;
            }
            st.push(node->left);
            st.push(node->right);
        }
        pos = '\0';
        return nullptr;
    }
    BiTree *GetSibling(const T1 &e)
    {
        char pos;
        BiTree *father = this->GetFather(e, pos);
        if (father == nullptr)
            return nullptr;
        if (pos == 'L')
            return father->right;
        else
            return father->left;
    }
    bool InsertNode(const T1 &e, const char &mode, pair<T1, T2> node)
    {
        if (mode == 'H')
        {
            BiTree *tmp = new BiTree;
            tmp->key = this->key;
            tmp->data = this->data;
            tmp->left = this->left;
            tmp->right = this->right;
            this->key = node.first;
            this->data = node.second;
            this->left = nullptr;
            this->right = tmp;
            return true;
        }
        BiTree *tmp = this->LocateNode(e);
        if (tmp == nullptr)
            return false;
        if (mode == 'L')
        {
            BiTree *tmp2 = tmp->left;
            tmp->left = new BiTree;
            tmp->left->key = node.first;
            tmp->left->data = node.second;
            tmp->left->right = tmp2;
            return true;
        }
        if (mode == 'R')
        {
            BiTree *tmp2 = tmp->right;
            tmp->right = new BiTree;
            tmp->right->key = node.first;
            tmp->right->data = node.second;
            tmp->right->right = tmp2;
            return true;
        }
        return false;
    }
    bool DeleteNode(const T1 &e)
    {
        if (e == this->key)
        {
            BiTree *l = this->left;
            BiTree *r = this->right;
            if (l == nullptr && r == nullptr)
            {
                this->key = T1(0);
                this->data = T2(0);
                return true;
            }
            if (l == nullptr && r != nullptr)
            {
                *this = *r;
                delete r;
                return true;
            }
            BiTree *rightest = l;
            while (rightest->right != nullptr)
                rightest = rightest->right;
            rightest->right = r;
            *this = *l;
            delete l;
            return true;
        }
        char pos;
        BiTree *father = this->GetFather(e, pos);
        if (father == nullptr)
            return false;
        BiTree *tmp;
        BiTree **from;
        if (pos == 'L')
        {
            from = &(father->left);
            tmp = father->left;
        }
        if (pos == 'R')
        {
            from = &(father->right);
            tmp = father->right;
        }
        if (tmp->left != nullptr && tmp->right == nullptr)
        {
            *from = tmp->left;
            delete tmp;
        }
        else if (tmp->left == nullptr && tmp->right != nullptr)
        {
            *from = tmp->right;
            delete tmp;
        }
        else
        {
            *from = tmp->left;
            BiTree *tmp2 = tmp->left;
            while (tmp2->right != nullptr)
                tmp2 = tmp2->right;
            tmp2->right = tmp->right;
            delete tmp;
        }
        return true;
    }
    void PreorderTraverse(function<void(T1, T2)> visit)
    {
#if _TraverseByStack
        stack<BiTree *> st;
        st.push(this);
        while (!st.empty())
        {
            BiTree *bt = st.top();
            st.pop();
            visit(bt->key, bt->data);
            if (bt->right != nullptr)
                st.push(bt->right);
            if (bt->left != nullptr)
                st.push(bt->left);
        }
#else
        visit(this->key, this->data);
        if (this->left != nullptr)
            this->left->PreorderTraverse(visit);
        if (this->right != nullptr)
            this->right->PreorderTraverse(visit);
#endif
    }
    void InorderTraverse(function<void(T1, T2)> visit)
    {
#if _TraverseByStack
        stack<BiTree *> st;
        unordered_map<BiTree *, int> mp;
        mp[this] = 0;
        st.push(this);
        while (!st.empty())
        {
            BiTree *bt = st.top();
            if (bt == nullptr)
            {
                st.pop();
                continue;
            }
            if (mp[bt] == 0)
            {
                st.push(bt->left);
                mp[bt]++;
                continue;
            }
            if (mp[bt] == 1)
            {
                st.pop();
                visit(bt->key, bt->data);
                st.push(bt->right);
            }
        }
#else
        if (this->left != nullptr)
            this->left->InorderTraverse(visit);
        visit(this->key, this->data);
        if (this->right != nullptr)
            this->right->InorderTraverse(visit);
#endif
    }
    void PostorderTraverse(function<void(T1, T2)> visit)
    {
#if _TraverseByStack
        stack<BiTree *> st;
        unordered_map<BiTree *, int> mp;
        mp[this] = 0;
        st.push(this);
        while (!st.empty())
        {
            BiTree *bt = st.top();
            if (bt == nullptr)
            {
                st.pop();
                continue;
            }
            if (mp[bt] == 0)
            {
                st.push(bt->left);
                mp[bt]++;
                continue;
            }
            if (mp[bt] == 1)
            {
                st.push(bt->right);
                mp[bt]++;
                continue;
            }
            if (mp[bt] == 2)
            {
                st.pop();
                visit(bt->key, bt->data);
            }
        }
#else
        if (this->left != nullptr)
            this->left->PostorderTraverse(visit);
        if (this->right != nullptr)
            this->right->PostorderTraverse(visit);
        visit(this->key, this->data);
#endif
    }
    void LevelOrderTraverse(function<void(T1, T2)> visit)
    {
        queue<BiTree *> q;
        q.push(this);
        while (!q.empty())
        {
            BiTree *bt = q.front();
            q.pop();
            visit(bt->key, bt->data);
            if (bt->left != nullptr)
                q.push(bt->left);
            if (bt->right != nullptr)
                q.push(bt->right);
        }
    }
    T2 MaxPathSum()
    {
        if (this->left == nullptr && this->right == nullptr)
            return this->data;
        T2 left = this->left != nullptr ? this->left->MaxPathSum() : T2(0);
        T2 right = this->right != nullptr ? this->right->MaxPathSum() : T2(0);
        return max(left, right) + this->data;
    }
    BiTree *LowestCommonAncestor(const T1 &a, const T1 &b)
    {
        if (this->key == a || this->key == b)
            return this;
        BiTree *left = this->left != nullptr ? this->left->LowestCommonAncestor(a, b) : nullptr;
        BiTree *right = this->right != nullptr ? this->right->LowestCommonAncestor(a, b) : nullptr;
        if (left != nullptr && right != nullptr)
            return this;
        if (left != nullptr)
            return left;
        if (right != nullptr)
            return right;
        return nullptr;
    }
    void InvertTree()
    {
        if (this->left != nullptr)
            this->left->InvertTree();
        if (this->right != nullptr)
            this->right->InvertTree();
        swap(this->left, this->right);
    }
    bool save(const string &file)
    {
        BiTree nullnode;
#if _Bin
        ofstream out(file + ".btbin", ios::out | ios::binary);
#else
        ofstream out(file + ".txt", ios::out);
#endif
        if (!out.is_open())
            return false;
        stack<BiTree *> st;
        st.push(this);
        while (!st.empty())
        {
            BiTree *bt = st.top();
            st.pop();
            if (bt == nullptr)
            {
#if _Bin
                bstream<BiTree>::write(out, nullnode);
#else
                out << nullnode << " ";
#endif
            }
            else
            {
#if _Bin
                bstream<BiTree>::write(out, *bt);
#else
                out << *bt << " ";
#endif
                st.push(bt->right);
                st.push(bt->left);
            }
        }
        out.close();
        return true;
    }
    bool load(const string &file)
    {
        this->ClearBiTree();
#if _Bin
        ifstream in(file + ".btbin", ios::in | ios::binary);
#else
        ifstream in(file + ".txt", ios::in);
#endif
        if (!in.is_open())
            return false;
        BiTree *head = this;
        stack<BiTree **> st;
        st.push(&head);
        while (!st.empty())
        {
            BiTree **bt = st.top();
            st.pop();
            BiTree tmp;
#if _Bin
            bstream<BiTree>::read(in, tmp);
#else
            in >> tmp;
#endif
            if (tmp.key == 0)
            {
                continue;
            }
            else
            {
                if (*bt == nullptr)
                    *bt = new BiTree;
                **bt = tmp;
                st.push(&((*bt)->right));
                st.push(&((*bt)->left));
            }
        }
        in.close();
        return true;
    }
};
struct Node
{
    int value;
    string data;
    Node() : value(0), data("0") {}
    Node(int a) : value(a), data("0") {}
    Node(int a, string b) : value(a), data(b) {}
    Node operator+(const Node &b) const
    {
        return Node(this->value + b.value, this->data);
    }
    bool operator>(const Node &b) const
    {
        return this->value > b.value;
    }
    bool operator<(const Node &b) const
    {
        return this->value < b.value;
    }
    bool operator==(const Node &b) const
    {
        return this->value == b.value;
    }
    friend ostream &operator<<(ostream &out, Node nd)
    {
        out << nd.value << " " << nd.data;
        return out;
    }
    friend istream &operator>>(istream &in, Node &nd)
    {
        in >> nd.value >> nd.data;
        return in;
    }

#if _Bin
    void write(std::ostream &out) const
    {
        bstream<int>::write(out, value);
        bstream<std::string>::write(out, data);
    }

    void read(std::istream &in)
    {
        bstream<int>::read(in, value);
        bstream<std::string>::read(in, data);
    }
#endif
};
unordered_map<string, BiTree<int, Node> *> mp;
bool InitByPwithN(const string &name)
{
    if (mp.find(name) != mp.end())
    {
        return false;
    }
    mp[name] = new BiTree<int, Node>;
    cout << "Please input key(int) value(int) data(string) in order, 0 0 0 for null node, -1 0 0 for ending:\n";
    queue<pair<int, Node>> q;
    unordered_map<int, bool> keys;
    while (true)
    {
        int key, value;
        string data;
        cin >> key >> value >> data;
        if (key != 0 && keys[key] == true)
        {
            cout << "\nError: Duplicate keys!\n";
            return false;
        }
        keys[key] = true;
        if (key == -1)
            break;
        Node nd = {value, data};
        q.push(make_pair(key, nd));
    }
    if (mp[name]->InitByPreorderTraversalWithNullnode(q, 0) == false)
    {
        mp[name]->DestroyBiTree();
        mp.erase(name);
        return false;
    }
    return true;
}
bool InitByPreaI(const string &name)
{
    if (mp.find(name) != mp.end())
    {
        return false;
    }
    mp[name] = new BiTree<int, Node>;
    cout << "Please input key(int) value(int) data(string) in preorder, 0 0 0 for ending:\n";
    vector<pair<int, Node>> psq, isq;
    unordered_map<int, bool> keys;
    while (true)
    {
        int key, value;
        string data;
        cin >> key >> value >> data;
        if (keys[key] == true)
        {
            cout << "\nError: Duplicate keys!\n";
            return false;
        }
        keys[key] = true;
        if (key == 0)
            break;
        Node nd = {value, data};
        psq.push_back(make_pair(key, nd));
    }
    keys.clear();
    cout << "Please input key(int) value(int) data(string) in inorder, 0 0 0 for ending:\n";
    while (true)
    {
        int key, value;
        string data;
        cin >> key >> value >> data;
        if (keys[key] == true)
        {
            cout << "\nError: Duplicate keys!\n";
            return false;
        }
        keys[key] = true;
        if (key == 0)
            break;
        Node nd = {value, data};
        isq.push_back(make_pair(key, nd));
    }
    if (psq.size() != isq.size())
    {
        cout << "\nError: The number of nodes is not equal!\n";
        return false;
    }
    if (psq.size() == 0)
    {
        return true;
    }
    if (mp[name]->InitByPreorderAndInorderTraversal(psq, isq, 0, psq.size() - 1, 0, isq.size() - 1) == false)
    {
        mp[name]->DestroyBiTree();
        mp.erase(name);
        return false;
    }
    return true;
}
bool InitByPostaI(const string &name)
{
    if (mp.find(name) != mp.end())
    {
        return false;
    }
    mp[name] = new BiTree<int, Node>;
    cout << "Please input key(int) value(int) data(string) in postorder, 0 0 0 for ending:\n";
    vector<pair<int, Node>> psq, isq;
    unordered_map<int, bool> keys;
    while (true)
    {
        int key, value;
        string data;
        cin >> key >> value >> data;
        if (keys[key] == true)
        {
            cout << "\nError: Duplicate keys!\n";
            return false;
        }
        keys[key] = true;
        if (key == 0)
            break;
        Node nd = {value, data};
        psq.push_back(make_pair(key, nd));
    }
    keys.clear();
    cout << "Please input key(int) value(int) data(string) in inorder, 0 0 0 for ending:\n";
    while (true)
    {
        int key, value;
        string data;
        cin >> key >> value >> data;
        if (keys[key] == true)
        {
            cout << "\nError: Duplicate keys!\n";
            return false;
        }
        keys[key] = true;
        if (key == 0)
            break;
        Node nd = {value, data};
        isq.push_back(make_pair(key, nd));
    }
    if (psq.size() != isq.size())
    {
        cout << "\nError: The number of nodes is not equal!\n";
        return false;
    }
    if (psq.size() == 0)
    {
        return true;
    }
    if (mp[name]->InitByPostorderAndInorderTraversal(psq, isq, 0, psq.size() - 1, 0, isq.size() - 1) == false)
    {
        mp[name]->DestroyBiTree();
        mp.erase(name);
        return false;
    }
    return true;
}
bool InitAsEmpty(const string &name)
{
    if (mp.find(name) != mp.end())
        return false;
    mp[name] = new BiTree<int, Node>;
    return true;
}
void showTrees()
{
    if (mp.empty())
    {
        cout << "No Tree in memory";
        return;
    }
    cout << "Trees in memory:\n";
    for (auto it : mp)
    {
        cout << it.first << endl;
    }
}
inline void menu()
{
    const string title = "Welcome to the Binary Tree System!";
    size_t maxlength = 0;
    for (auto it : funcs)
    {
        maxlength = max(maxlength, it.length());
    }
    for (int i = 0; i < maxlength * 2 + 1; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < (maxlength * 2 + 1 - title.length()) / 2; i++)
    {
        cout << " ";
    }
    cout << title << endl;
    for (int i = 0; i < maxlength * 2 + 1; i++)
    {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < 12; i++)
    {
        cout << funcs[i];
        for (int j = 0; j < maxlength + 1 - funcs[i].length(); j++)
            cout << " ";
        cout << funcs[i + 12] << endl;
    }
    for (int i = 0; i < maxlength * 2 + 1; i++)
    {
        cout << "-";
    }
    cout << endl;
}
void color(const unsigned short color1, const unsigned short color2)
{
    /*第一个是字体颜色，第二个是背景颜色，颜色编码参考下表
    0=黑色		8=灰色
    1=蓝色		9=淡蓝色
    2=绿色		10=淡绿色
    3=湖蓝色	11=淡浅绿色
    4=红色		12=淡红色
    5=紫色		13=淡紫色
    6=黄色		14=淡黄色
    7=白色		15=亮白色*/
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (color2 * 16 + color1));
}
void cursor_move(short x, short y)
{
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
int choose()
{
    size_t maxlength = 0;
    for (auto it : funcs)
    {
        maxlength = max(maxlength, it.length());
    }
    int x = 0, y = 0;
    cursor_move(0, 0);
    color(10, 0);
    menu();
    cursor_move((maxlength + 1) * x, y + 3);
    color(9, 0);
    cout << funcs[x * 12 + y];
    while (1)
    {
        if (_kbhit())
        {
            int asc = _getch();
            cursor_move((maxlength + 1) * x, y + 3);
            color(10, 0);
            cout << funcs[x * 12 + y];
            if (asc == 72 && y > 0)
            { // up
                y--;
            }
            if (asc == 80 && y < 11)
            { // down
                // if(y==8) x=0;
                y++;
            }
            if (asc == 75 && x > 0)
            { // left
                x--;
            }
            if (asc == 77 && x < 1)
            { // right
                // if(y==9) y--;
                x++;
            }
            cursor_move((maxlength + 1) * x, y + 3);
            color(9, 0);
            cout << funcs[x * 12 + y];
            if (asc == 13)
            { // enter
                system("cls");
                cursor_move(0, 0);
                color(10, 0);
                menu();
                cursor_move((maxlength + 1) * x, y + 3);
                color(9, 0);
                cout << funcs[x * 12 + y];
                cursor_move(0, 3 + 12 + 1);
                color(10, 0);
                return x * 12 + y + 1;
            }
        }
    }
}
int main()
{
    system("cls");
    auto visit = [](int key, Node nd)
    {
        cout << key << " " << nd.value << " " << nd.data << endl;
    };
    while (true)
    {
        int cmd = choose();
        if (cmd == 1)
            break;
        if (cmd == 24)
        {
            showTrees();
            continue;
        }
        string name;
        cout << "Please input the name of the Binary Tree:";
        cin >> name;
        if (cmd >= 2 && cmd <= 6)
        {
            switch (cmd)
            {
            case 2:
            {
                if (mp.find(name) != mp.end())
                {
                    cout << "Error: Binary Tree \"" << name << "\" already exists!\n";
                    break;
                }
                if (InitByPwithN(name) == true)
                {
                    cout << "Initializing Binary Tree \"" << name << "\" success!\n";
                }
                else
                {
                    cout << "Error: Failed to initialize Binary Tree \"" << name << "\"!\n";
                }
                break;
            }
            case 3:
            {
                if (mp.find(name) != mp.end())
                {
                    cout << "Error: Binary Tree \"" << name << "\" already exists!\n";
                    break;
                }
                if (InitByPreaI(name) == true)
                {
                    cout << "Initializing Binary Tree \"" << name << "\" success!\n";
                }
                else
                {
                    cout << "Error: Failed to initialize Binary Tree \"" << name << "\"!\n";
                }
                break;
            }
            case 4:
            {
                if (mp.find(name) != mp.end())
                {
                    cout << "Error: Binary Tree \"" << name << "\" already exists!\n";
                    break;
                }
                if (InitByPostaI(name) == true)
                {
                    cout << "Initializing Binary Tree \"" << name << "\" success!\n";
                }
                else
                {
                    cout << "Error: Failed to initialize Binary Tree \"" << name << "\"!\n";
                }
                break;
            }
            case 5:
            {
                if (mp.find(name) != mp.end())
                {
                    cout << "Error: Binary Tree \"" << name << "\" already exists!\n";
                    break;
                }
                if (InitAsEmpty(name) == true)
                {
                    cout << "Initializing Binary Tree \"" << name << "\" success!\n";
                }
                else
                {
                    cout << "Error: Failed to initialize Binary Tree \"" << name << "\"!\n";
                }
                break;
            }
            case 6:
            {
                if (mp.find(name) == mp.end())
                {
                    cout << "Error: Binary Tree \"" << name << "\" does not exisit!\n";
                    break;
                }
                mp[name]->DestroyBiTree();
                mp.erase(name);
                cout << "Binary Tree \"" << name << "\" destroy success!\n";
                break;
            }
            }
        }
        else
        {
            if (mp.find(name) == mp.end())
            {
                cout << "Error: Binary Tree \"" << name << "\" does not exisit!\n";
                continue;
            }
            switch (cmd)
            {
            case 7:
            {
                mp[name]->ClearBiTree();
                cout << "Binary Tree \"" << name << "\" clear success!\n";
                break;
            }
            case 8:
            {
                if (mp[name]->BiTreeEmpty())
                    cout << "Binary Tree \"" << name << "\" is empty!\n";
                else
                    cout << "Binary Tree \"" << name << "\" is not empty\n";
                break;
            }
            case 9:
            {
                cout << "The depth of Binary Tree \"" << name << "\" is:" << mp[name]->BiTreeDepth();
                break;
            }
            case 10:
            {
                int e;
                cout << "Please input the key(int):";
                cin >> e;
                BiTree<int, Node> *bt = mp[name]->LocateNode(e);
                if (bt == nullptr)
                {
                    cout << "Error: key \"" << e << "\" not found!\n";
                    break;
                }
                cout << "Data of the node:\n";
                cout << *bt;
                break;
            }
            case 11:
            {
                int key, value;
                string data;
                cout << "Please input the key(int), value(int) and data(string):";
                cin >> key >> value >> data;
                if (mp[name]->Assign(key, Node(value, data)))
                {
                    cout << "Node of key \"" << key << "\" assign success!\n";
                }
                else
                {
                    cout << "Error: Key \"" << key << "\" not found!\n";
                }
                break;
            }
            case 12:
            {
                BiTree<int, Node> *bt;
                int key;
                cout << "Please input the key(int):";
                cin >> key;
                if (mp[name]->LocateNode(key) == nullptr)
                {
                    cout << "Error: Key \"" << key << "\" not found!\n";
                    break;
                }
                bt = mp[name]->GetSibling(key);
                if (bt == nullptr)
                {
                    cout << "No sibling!\n";
                    break;
                }
                cout << "Data of the node:\n"
                     << *bt;
                break;
            }
            case 13:
            {
                int key, e, value;
                string data;
                char mode;
                cout << "Please input the key(int):";
                cin >> key;
                if (mp[name]->LocateNode(key) == nullptr)
                {
                    cout << "Error: Key \"" << key << "\" not found!\n";
                    break;
                }
                cout << "Please input the insert mode(L for left, R for right, H for head):";
                cin >> mode;
                if (mode != 'L' && mode != 'R' && mode != 'H')
                {
                    cout << "Error: Invalid mode!";
                    break;
                }
                cout << "Please input the key(int), value(int), data(string) of new node:";
                cin >> e >> value >> data;
                if (mp[name]->LocateNode(e) != nullptr)
                {
                    cout << "Error: key \"" << e << "\" already exists!\n";
                    break;
                }
                if (mp[name]->InsertNode(key, mode, make_pair(e, Node(value, data))))
                {
                    cout << "Node insert success!\n";
                }
                else
                {
                    cout << "Error: Key \"" << key << "\" not found!\n";
                }
                break;
            }
            case 14:
            {
                int key;
                cout << "Please input the key(int):";
                cin >> key;
                if (mp[name]->DeleteNode(key))
                {
                    cout << "Node of key \"" << key << "\" delete success!\n";
                }
                else
                {
                    cout << "Error: Key \"" << key << "\" not found!\n";
                }
                break;
            }
            case 15:
            {
                cout << "Preorder traversal:\n";
                mp[name]->PreorderTraverse(visit);
                break;
            }
            case 16:
            {
                cout << "Inorder traversal:\n";
                mp[name]->InorderTraverse(visit);
                break;
            }
            case 17:
            {
                cout << "Postorder traversal:\n";
                mp[name]->PostorderTraverse(visit);
                break;
            }
            case 18:
            {
                cout << "LevelOrder traversal:\n";
                mp[name]->LevelOrderTraverse(visit);
                break;
            }
            case 19:
            {
                Node res = mp[name]->MaxPathSum();
                cout << "Max path sum:" << res.value << endl;
                break;
            }
            case 20:
            {
                BiTree<int, Node> *bt;
                int key1, key2;
                cout << "Please input two keys(int):";
                cin >> key1 >> key2;
                bt = mp[name]->LowestCommonAncestor(key1, key2);
                if (bt == nullptr)
                {
                    cout << "Error: At least one key not found!\n";
                }
                else
                {
                    cout << "Data of the node:\n"
                         << *bt;
                }
                break;
            }
            case 21:
            {
                mp[name]->InvertTree();
                cout << "Binary Tree \"" << name << "\" invert success!\n";
                break;
            }
            case 22:
            {
                if (mp[name]->save(name))
                {
                    cout << "Binary Tree \"" << name << "\" saved!\n";
                }
                else
                {
                    cout << "Error: Failed to save Binary Tree!\n";
                }
                break;
            }
            case 23:
            {
                if (mp[name]->load(name))
                {
                    cout << "Binary Tree \"" << name << "\" loaded!\n";
                }
                else
                {
                    cout << "Error: Failed to load Binary Tree!\n";
                }
                break;
            }
            }
        }
    }
    cout << "Thank you for using Binary Tree system\n";
    system("pause");
    return 0;
}