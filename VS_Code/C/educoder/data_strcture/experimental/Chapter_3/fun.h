#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#define OK 1
#define ERROR 0
typedef int Status;

template <class T1, class T2>
class BiTree
{
private:
    T1 key;
    T2 data;
    BiTree *left, *right;

public:
    BiTree() : key(0), data(0), left(nullptr), right(nullptr) {}

    // 根据前序和中序遍历构造二叉树
    Status CreateBiTreePreOrder_InOrder()
    {
        try
        {
            // 输入前序遍历和中序遍历数据
            std::vector<std::pair<T1, T2>> preorder, inorder;
            size_t n;

            std::cout << "请输入节点数量: ";
            std::cin >> n;

            std::cout << "请输入前序遍历 (key data):" << std::endl;
            for (size_t i = 0; i < n; ++i)
            {
                T1 key;
                T2 data;
                std::cin >> key >> data;
                preorder.emplace_back(key, data);
            }

            std::cout << "请输入中序遍历 (key data):" << std::endl;
            for (size_t i = 0; i < n; ++i)
            {
                T1 key;
                T2 data;
                std::cin >> key >> data;
                inorder.emplace_back(key, data);
            }

            // 调用递归函数构造二叉树
            CreateBiTreeHelper(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
            return OK; // 创建成功
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return ERROR; // 创建失败
        }
    }

    // 销毁二叉树
    void DestroyBiTree()
    {
        if (this->left)
        {
            this->left->DestroyBiTree();
            delete this->left;
            this->left = nullptr;
        }
        if (this->right)
        {
            this->right->DestroyBiTree();
            delete this->right;
            this->right = nullptr;
        }
    }

    // 清空二叉树
    void ClearBiTree()
    {
        if (this->left)
        {
            this->left->ClearBiTree();
            delete this->left;
            this->left = nullptr;
        }
        if (this->right)
        {
            this->right->ClearBiTree();
            delete this->right;
            this->right = nullptr;
        }
    }

    // 判定空二叉树
    bool IsEmpty() const
    {
        return this->left == nullptr && this->right == nullptr;
    }

    // 求二叉树深度
    int Depth() const
    {
        int leftDepth = this->left ? this->left->Depth() : 0;
        int rightDepth = this->right ? this->right->Depth() : 0;
        return std::max(leftDepth, rightDepth) + 1;
    }

    // 查找结点
    BiTree *FindNode(const T1 &key) const
    {
        if (this->key == key)
            return const_cast<BiTree *>(this); // 返回当前节点

        BiTree *foundNode = nullptr;
        if (this->left)
            foundNode = this->left->FindNode(key);
        if (!foundNode && this->right)
            foundNode = this->right->FindNode(key);

        return foundNode; // 返回找到的节点或nullptr
    }

    // 结点赋值
    void AssignNode(const T1 &key, const T2 &data)
    {
        BiTree *node = this->FindNode(key);
        if (node)
            node->data = data; // 更新数据
        else
            throw std::invalid_argument("Key not found in the tree.");
    }

    // 获得兄弟结点
    BiTree *GetSibling(const T1 &key) const
    {
        if (this->key == key)
            return nullptr; // 根节点没有兄弟节点

        if (this->left && this->left->key == key)
            return this->right; // 返回右子树作为兄弟节点
        if (this->right && this->right->key == key)
            return this->left; // 返回左子树作为兄弟节点

        BiTree *sibling = nullptr;
        if (this->left)
            sibling = this->left->GetSibling(key);
        if (!sibling && this->right)
            sibling = this->right->GetSibling(key);

        return sibling; // 返回找到的兄弟节点或nullptr
    }

    // 插入结点
    void InsertNode(const T1 &key, const T2 &data, bool isLeft)
    {
        if (isLeft)
        {
            if (!this->left)
            {
                this->left = new BiTree();
                this->left->key = key;
                this->left->data = data;
            }
            else
            {
                this->left->InsertNode(key, data, isLeft);
            }
        }
        else
        {
            if (!this->right)
            {
                this->right = new BiTree();
                this->right->key = key;
                this->right->data = data;
            }
            else
            {
                this->right->InsertNode(key, data, isLeft);
            }
        }
    }

    // 删除结点
    void DeleteNode(const T1 &key)
    {
        if (this->key == key)
        {
            DestroyBiTree(); // 销毁当前节点
            return;
        }

        if (this->left)
        {
            if (this->left->key == key)
            {
                delete this->left; // 删除左子树
                this->left = nullptr;
                return;
            }
            else
            {
                this->left->DeleteNode(key);
            }
        }

        if (this->right)
        {
            if (this->right->key == key)
            {
                delete this->right; // 删除右子树
                this->right = nullptr;
                return;
            }
            else
            {
                this->right->DeleteNode(key);
            }
        }
    }

    // 打印二叉树（前序遍历）
    void PreOrderPrint()
    {
        std::cout << this->key << ": " << this->data << " ";
        if (this->left)
            this->left->PreOrderPrint();
        if (this->right)
            this->right->PreOrderPrint();
    }

    // 打印二叉树（中序遍历）
    void InOrderPrint()
    {
        if (this->left)
            this->left->InOrderPrint();
        std::cout << this->key << ": " << this->data << " ";
        if (this->right)
            this->right->InOrderPrint();
    }

    // 打印二叉树（后序遍历）
    void PostOrderPrint()
    {
        if (this->left)
            this->left->PostOrderPrint();
        if (this->right)
            this->right->PostOrderPrint();
        std::cout << this->key << ": " << this->data << " ";
    }

    // 打印二叉树（按层遍历）
    void LevelOrderPrint()
    {
        std::vector<BiTree *> queue;
        queue.push_back(this); // 从根节点开始

        while (!queue.empty())
        {
            BiTree *current = queue.front();
            queue.erase(queue.begin()); // 移除队列的第一个元素
            std::cout << current->key << ": " << current->data << " ";

            if (current->left)
                queue.push_back(current->left);
            if (current->right)
                queue.push_back(current->right);
        }
    }

    // 最大路径和（从根节点到叶子节点的路径和）
    T2 MaxPathSum()
    {
        if (this->left == nullptr && this->right == nullptr)
            return this->data; // 叶子节点返回自身数据

        T2 leftSum = this->left ? this->left->MaxPathSum() : 0;
        T2 rightSum = this->right ? this->right->MaxPathSum() : 0;

        return this->data + std::max(leftSum, rightSum); // 返回当前节点数据加上最大路径和
    }

    // 最近公共祖先（假设二叉树中没有重复的key）
    BiTree *LowestCommonAncestor(const T1 &key1, const T1 &key2)
    {
        if (this->key == key1 || this->key == key2)
            return this; // 如果当前节点是其中一个key，返回当前节点

        BiTree *leftLCA = this->left ? this->left->LowestCommonAncestor(key1, key2) : nullptr;
        BiTree *rightLCA = this->right ? this->right->LowestCommonAncestor(key1, key2) : nullptr;

        if (leftLCA && rightLCA)
            return this; // 如果在左右子树中都找到了key，当前节点是最近公共祖先

        return leftLCA ? leftLCA : rightLCA; // 返回非空的子树
    }

    // 翻转二叉树
    InvertTree()
    {
        if (this == nullptr)
            return;

        // 交换左右子树
        BiTree *temp = this->left;
        this->left = this->right;
        this->right = temp;

        // 递归翻转左右子树
        if (this->left)
            this->left->InvertTree();
        if (this->right)
            this->right->InvertTree();
    }

    // 文件保存二叉树
    void SaveToFile(const std::string &filename)

        // 文件读取二叉树
        void LoadFromFile(const std::string &filename)
    {
        // 这里可以实现文件保存和读取的逻辑
        // 例如使用fstream库来读写文件
    }

    // 多二叉树管理

    // 添加二叉树
    void AddBiTree(BiTree *newTree)
    {
        // 这里可以实现添加二叉树的逻辑
        // 例如将新树添加到一个数组或链表中
    }

    // 删除二叉树
    void DeleteBiTree(const T1 &key)
    {
        // 这里可以实现删除二叉树的逻辑
        // 例如在数组或链表中查找并删除指定的树
    }

    // 打印出所有二叉树名称
    void PrintAllBiTreeNames()
    {
        // 这里可以实现打印所有二叉树名称的逻辑
        // 例如遍历数组或链表并输出每个树的名称
    }

    // 选择二叉树
    void SelectBiTree(int index)
    {
        // 这里可以实现选择二叉树的逻辑
        // 例如根据索引选择指定的树并进行操作
    }

    // 修改二叉树名称
    void ModifyBiTreeName(int index, const std::string &newName)
    {
        // 这里可以实现修改二叉树名称的逻辑
        // 例如在数组或链表中查找指定的树并修改其名称
    }

private:
    // 辅助递归函数
    void CreateBiTreeHelper(std::vector<std::pair<T1, T2>> &preorder, std::vector<std::pair<T1, T2>> &inorder,
                            size_t preStart, size_t preEnd, size_t inStart, size_t inEnd)
    {
        if (preStart > preEnd || inStart > inEnd)
            return;

        // 前序遍历的第一个节点是当前子树的根节点
        this->key = preorder[preStart].first;
        this->data = preorder[preStart].second;

        // 在中序遍历中找到根节点的位置
        size_t rootIndex = inStart;
        while (rootIndex <= inEnd && inorder[rootIndex].first != this->key)
            rootIndex++;

        if (rootIndex > inEnd)
            throw std::invalid_argument("Invalid input: Key not found in inorder traversal.");

        // 计算左子树的节点数量
        size_t leftTreeSize = rootIndex - inStart;

        // 构造左子树
        if (leftTreeSize > 0)
        {
            this->left = new BiTree();
            this->left->CreateBiTreeHelper(preorder, inorder, preStart + 1, preStart + leftTreeSize, inStart, rootIndex - 1);
        }

        // 构造右子树
        if (rootIndex < inEnd)
        {
            this->right = new BiTree();
            this->right->CreateBiTreeHelper(preorder, inorder, preStart + leftTreeSize + 1, preEnd, rootIndex + 1, inEnd);
        }
    }
};