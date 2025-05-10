template <class T1, class T2>
class BiTree
{
public:
    T1 key;
    T2 data;
    BiTree *left, *right;
    BiTree() : key(0), data(0), left(nullptr), right(nullptr) {}

    // 根据后序和中序遍历构造二叉树
    status CreateBiTreePostOrder_InOrder()
    {
        try
        {
            // 输入后序遍历和中序遍历数据
            std::vector<std::pair<T1, T2>> postorder, inorder;
            size_t n;

            std::cout << "\t请输入节点数量: ";
            std::cin >> n;

            std::cout << "\t请输入后序遍历 (key data):";
            for (size_t i = 0; i < n; ++i)
            {
                T1 key;
                T2 data;
                std::cin >> key >> data;
                postorder.emplace_back(key, data);
            }

            std::cout << "\t请输入中序遍历 (key data):";
            for (size_t i = 0; i < n; ++i)
            {
                T1 key;
                T2 data;
                std::cin >> key >> data;
                inorder.emplace_back(key, data);
            }

            // 调用递归函数构造二叉树
            CreateBiTreeHelper(postorder, inorder, 0, postorder.size() - 1, 0, inorder.size() - 1);
            return OK; // 创建成功
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return ERROR; // 创建失败
        }
    }

    // 根据带空节点的中序遍历构造二叉树
    status CreateBiTreeInOrderWithNull()
    {
        try
        {
            // 输入中序遍历数据
            std::vector<std::string> inorder;
            size_t n;

            std::cout << "\t请输入节点数量（包括空节点）: ";
            std::cin >> n;

            std::cout << "\t请输入中序遍历 (key 或 # 表示空节点):";
            for (size_t i = 0; i < n; ++i)
            {
                std::string value;
                std::cin >> value;
                inorder.push_back(value);
            }

            size_t index = 0;
            CreateBiTreeInOrderWithNullHelper(inorder, index);
            return OK; // 创建成功
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return ERROR; // 创建失败
        }
    }

    // 根据前序和中序遍历构造二叉树
    status CreateBiTreePreOrder_InOrder()
    {
        try
        {
            // 输入前序遍历和中序遍历数据
            std::vector<std::pair<T1, T2>> preorder, inorder;
            size_t n;

            std::cout << "\t请输入节点数量: ";
            std::cin >> n;

            std::cout << "\t请输入前序遍历 (key data):";
            for (size_t i = 0; i < n; ++i)
            {
                T1 key;
                T2 data;
                std::cin >> key >> data;
                preorder.emplace_back(key, data);
            }

            std::cout << "\t请输入中序遍历 (key data):";
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
    status DestroyBiTree()
    {
        if (this == nullptr)
            return ERROR; // 空树直接返回
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
        return OK; // 销毁成功
    }

    // 清空二叉树
    status ClearBiTree()
    {
        if (this == nullptr)
            return ERROR; // 空树直接返回
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
        this->key = 0; // 清空当前节点
        this->data = 0;
        return OK; // 清空成功
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
    status AssignNode(const T1 &key, const T2 &data)
    {
        if (this->key == key)
        {
            this->data = data; // 更新数据
            return OK;         // 赋值成功
        }
        BiTree *node = this->FindNode(key);
        if (node)
            node->data = data; // 更新数据
        else
            throw std::invalid_argument("Key not found in the tree.");
        return OK; // 赋值成功
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
    status InsertNode(const T1 &key, const T2 &data, bool isLeft)
    {
        if (this->key == key)
            return ERROR; // 不能插入到已存在的节点上

        BiTree *newNode = new BiTree();
        newNode->key = key;
        newNode->data = data;

        if (isLeft)
        {
            if (this->left == nullptr)
                this->left = newNode; // 插入到左子树
            else
                return ERROR; // 左子树已存在
        }
        else
        {
            if (this->right == nullptr)
                this->right = newNode; // 插入到右子树
            else
                return ERROR; // 右子树已存在
        }

        return OK; // 插入成功
    }

    // 删除结点
    status DeleteNode(const T1 &key)
    {
        if (this->key == key)
        {
            delete this; // 删除当前节点
            return OK;
        }

        if (this->left && this->left->key == key)
        {
            delete this->left; // 删除左子树
            this->left = nullptr;
            return OK;
        }
        if (this->right && this->right->key == key)
        {
            delete this->right; // 删除右子树
            this->right = nullptr;
            return OK;
        }

        status leftStatus = ERROR, rightStatus = ERROR;
        if (this->left)
            leftStatus = this->left->DeleteNode(key);
        if (this->right)
            rightStatus = this->right->DeleteNode(key);

        return leftStatus == OK || rightStatus == OK ? OK : ERROR; // 返回删除结果
    }

    // 打印二叉树（前序遍历）
    status PreOrderPrint()
    {
        if (this == nullptr)
            return ERROR; // 空树直接返回
        std::cout << this->key << "->" << this->data << " ";
        if (this->left)
            this->left->PreOrderPrint();
        if (this->right)
            this->right->PreOrderPrint();
        return OK;
    }

    // 打印二叉树（中序遍历）
    status InOrderPrint()
    {
        if (this == nullptr)
            return ERROR; // 空树直接返回
        if (this->left)
            this->left->InOrderPrint();
        std::cout << this->key << "->" << this->data << " ";
        if (this->right)
            this->right->InOrderPrint();
        return OK;
    }

    // 打印二叉树（后序遍历）
    status PostOrderPrint()
    {
        if (this == nullptr)
            return ERROR; // 空树直接返回
        if (this->left)
            this->left->PostOrderPrint();
        if (this->right)
            this->right->PostOrderPrint();
        std::cout << this->key << "->" << this->data << " ";
        return OK;
    }

    // 打印二叉树（按层遍历）
    status LevelOrderPrint()
    {
        if (this == nullptr)
            return ERROR; // 空树直接返回
        std::vector<BiTree *> queue;
        queue.push_back(this); // 从根节点开始

        while (!queue.empty())
        {
            BiTree *node = queue.front();
            queue.erase(queue.begin()); // 弹出队首元素
            std::cout << node->key << "->" << node->data << " ";

            if (node->left)
                queue.push_back(node->left); // 添加左子树
            if (node->right)
                queue.push_back(node->right); // 添加右子树
        }
        return OK;
    }

    // 最大路径和（从根节点到叶子节点的路径和）
    int MaxPathSum()
    {
        if (this->left == nullptr && this->right == nullptr)
            return this->data; // 叶子节点返回自身数据

        int leftSum = this->left ? this->left->MaxPathSum() : 0;
        int rightSum = this->right ? this->right->MaxPathSum() : 0;

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
    status InvertTree()
    {
        if (this == nullptr)
            return ERROR;

        // 交换左右子树
        BiTree *temp = this->left;
        this->left = this->right;
        this->right = temp;

        // 递归翻转左右子树
        if (this->left)
            this->left->InvertTree();
        if (this->right)
            this->right->InvertTree();
        return OK;
    }

    // 文件保存二叉树
    status SaveToFile(const std::string &filename)
    {
        std::ofstream outFile(filename, std::ios::out | std::ios::trunc);
        if (!outFile)
        {
            throw std::ios_base::failure("文件保存失败！");
            return ERROR; // 保存失败
        }

        // 使用前序遍历保存二叉树
        std::function<void(BiTree *)> saveHelper = [&](BiTree *node)
        {
            if (!node)
            {
                outFile << "# "; // 使用#表示空节点
                return;
            }
            outFile << node->key << " " << node->data << " ";
            saveHelper(node->left);
            saveHelper(node->right);
        };

        saveHelper(this);
        outFile.close();
        return OK; // 保存成功
    }

    // 文件读取二叉树
    status LoadFromFile(const std::string &filename)
    {
        std::ifstream inFile(filename, std::ios::in);
        if (!inFile)
        {
            throw std::ios_base::failure("文件读取失败！");
            return ERROR; // 读取失败
        }

        // 使用前序遍历读取二叉树
        std::function<BiTree *(std::ifstream &)> loadHelper = [&](std::ifstream &file) -> BiTree *
        {
            std::string token;
            file >> token;
            if (token == "#")
            {
                return nullptr; // 空节点
            }

            T1 key;
            T2 data;
            key = static_cast<T1>(std::stoi(token));
            file >> data;

            BiTree *node = new BiTree();
            node->key = key;
            node->data = data;
            node->left = loadHelper(file);
            node->right = loadHelper(file);

            return node;
        };

        BiTree *newTree = loadHelper(inFile);
        if (newTree)
        {
            this->key = newTree->key;
            this->data = newTree->data;
            this->left = newTree->left;
            this->right = newTree->right;
        }

        inFile.close();
        return OK; // 读取成功
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
    void CreateBiTreeInOrderWithNullHelper(const std::vector<std::string> &inorder, size_t &index)
    {
        if (index >= inorder.size() || inorder[index] == "#")
        {
            index++;
            return;
        }

        // 当前节点
        this->key = static_cast<T1>(std::stoi(inorder[index]));
        this->data = 0; // 默认数据为 0，可以根据需要修改
        index++;

        // 构造左子树
        this->left = new BiTree();
        this->left->CreateBiTreeInOrderWithNullHelper(inorder, index);

        // 构造右子树
        this->right = new BiTree();
        this->right->CreateBiTreeInOrderWithNullHelper(inorder, index);
    }
};

template <class List>
class BitreeList
{
private:
    List *Treelist;
    char **Treename;
    int listsize;

public:
    BitreeList() : Treelist(nullptr), Treename(nullptr), listsize(0)
    {
        Treename=(char **)malloc(20*sizeof(char *)); // 初始化Treename
        for (int i = 0; i < 20; ++i)
        {
            Treename[i] = (char *)malloc(20 * sizeof(char)); // 初始化每个Treename元素
        }
        strcpy(Treename[0], "未选择");
    }

    // 多二叉树管理
    // 添加二叉树
    status AddBiTree(List &newTree)
    {
        if (!Treelist)
        {
            Treelist = new List();
        }

        if (!Treename)
        {
            Treename = new char *[1];
            Treename[0] = new char[20];
            std::cout << "\t请输入二叉树名称: ";
            std::cin >> Treename[0];
        }
        else
        {
            char tempName[20];
            bool isDuplicate;
            do
            {
                isDuplicate = false;
                std::cout << "\t请输入二叉树名称: ";
                std::cin >> tempName;

                // 检查名称是否重复
                for (int i = 0; i < listsize; ++i)
                {
                    if (strcmp(Treename[i], tempName) == 0)
                    {
                        isDuplicate = true;
                        std::cout << "\t二叉树名称重复，请重新输入。" << std::endl;
                        break;
                    }
                }
            } while (isDuplicate);

            char **newTreename = new char *[listsize + 1];
            for (int i = 0; i < listsize; ++i)
            {
                newTreename[i] = Treename[i];
            }
            newTreename[listsize] = new char[20];
            strcpy(newTreename[listsize], tempName);
            delete[] Treename;
            Treename = newTreename;
        }

        Treelist[listsize] = newTree;
        listsize++;
        return OK; // 添加成功
    }

    // 删除二叉树
    status DeleteBiTree(const char *Delname)
    {
        if (!Treelist || !Treename)
        {
            std::cout << "\t没有可删除的二叉树。" << std::endl;
            return ERROR;
        }

        for (int i = 0; i < listsize; ++i)
        {
            if (strcmp(Treename[i], Delname) == 0)
            {

                // 移动后续元素覆盖当前元素
                for (int j = i; j < listsize - 1; ++j)
                {
                    Treelist[j] = Treelist[j + 1];
                    Treename[j] = Treename[j + 1];
                }

                // 调整列表大小
                listsize--;


                std::cout << "\t二叉树 " << Delname << " 已删除。" << std::endl;
                return OK;
            }
        }

        std::cout << "\t未找到名称为 " << Delname << " 的二叉树。" << std::endl;
        return ERROR; // 删除失败
    }
    // 打印出所有二叉树名称
    status PrintAllBiTreeNames()
    {
        if (!Treename)
        {
            std::cout << "\t没有可打印的二叉树名称。" << std::endl;
            return ERROR;
        }

        for (int i = 0; i < listsize; ++i)
        {
            std::cout << "\t二叉树名称 " << i + 1 << ": " << Treename[i] << std::endl;
        }
        return OK; // 打印成功
    }

    // 选择二叉树
    int SelectBiTree(char *name)
    {
        if (!Treename)
        {
            std::cout << "\t没有可选择的二叉树。" << std::endl;
            return -1;
        }

        for (int i = 0; i < listsize; ++i)
        {
            if (strcmp(Treename[i], name) == 0)
            {
                std::cout << "\t选择的二叉树名称: " << Treename[i] << std::endl;
                return i + 1; // 选择成功
            }
        }

        std::cout << "\t未找到名称为 " << name << " 的二叉树。" << std::endl;
        return -1; // 选择失败
    }

    // 修改二叉树名称
    status ModifyBiTreeName(char *name, const std::string &newName)
    {
        if (!Treename)
        {
            std::cout << "\t没有可修改的二叉树名称。" << std::endl;
            return ERROR;
        }

        for (int i = 0; i < listsize; ++i)
        {
            if (strcmp(Treename[i], name) == 0)
            {
                delete[] Treename[i]; // 删除旧名称
                Treename[i] = new char[newName.length() + 1];
                strcpy(Treename[i], newName.c_str()); // 复制新名称
                std::cout << "\t二叉树名称已修改为: " << Treename[i] << std::endl;
                return OK;
            }
        }

        std::cout << "\t未找到名称为 " << name << " 的二叉树。" << std::endl;
        return ERROR; // 修改失败
    }
};