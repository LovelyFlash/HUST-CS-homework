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
    Status CreateBiTree()
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

    // 打印二叉树（中序遍历）
    void InOrderPrint()
    {
        if (this->left)
            this->left->InOrderPrint();
        std::cout << this->key << ": " << this->data << " ";
        if (this->right)
            this->right->InOrderPrint();
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