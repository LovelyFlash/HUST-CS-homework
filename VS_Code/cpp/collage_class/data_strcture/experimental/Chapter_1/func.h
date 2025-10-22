status InitList(SqList &L)
{
    if (L.elem != NULL)
        return INFEASIBLE; 
    
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        return OVERFLOW;
    
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}

status DestroyList(SqList& L)
{
    if (L.elem != NULL)
    {
        free(L.elem);
        L.elem = NULL; // 将指针设置为NULL
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else
    {
        return INFEASIBLE;
    }
}

status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem != NULL)
    {
        L.elem[0] = '\0';
        L.length = 0;
        return OK;
    }
    else
    {
        return INFEASIBLE;
    }
    /********** End **********/
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L.elem == NULL)
    {
        return INFEASIBLE;
    }
    else
    {
        if(L.length == 0)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    /********** End **********/
}

status ListLength(SqList &L)
{
    // 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem==NULL) {
        return INFEASIBLE;
    }
    return L.length;
    /********** End **********/
}

status GetElem(SqList L, int i, ElemType &e)
{
    // 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length) {
        return ERROR;
    }
    e = L.elem[i - 1];
    return OK;
    /********** End **********/
}

int LocateElem(SqList L, ElemType e)
{
    // 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1; // 返回位置序号，从1开始
        }
    }
    return 0; // 元素e不存在
    /********** End **********/
}

status PriorElem(SqList L, ElemType e, ElemType &pre)
{
    // 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 1; i < L.length; i++) {
        if (L.elem[i] == e) {
            pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR; // 没有前驱
    /********** End **********/
}

status NextElem(SqList L, ElemType e, ElemType &next)
{
    // 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) {
            next = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR; // 没有后继
    /********** End **********/
}

status ListInsert(SqList &L, int i, ElemType e)
{
    // 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length + 1) {
        return ERROR;
    }
    if (L.length >= L.listsize) {
        // 动态增加内存分配
        ElemType *newBase = (ElemType *) realloc(L.elem, (L.listsize + 10) * sizeof(ElemType));
        if (!newBase) {
            return OVERFLOW;
        }
        L.elem = newBase;
        L.listsize += 10;
    }
    for (int j = L.length; j >= i; j--) {
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i - 1] = e;
    L.length++;
    return OK;
    /********** End **********/
}

status ListDelete(SqList &L, int i, ElemType &e)
{
    // 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length) {
        return ERROR;
    }
    e = L.elem[i - 1];
    for (int j = i; j < L.length; j++) {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;
    return OK;
    /********** End **********/
}

status ListTraverse(SqList L)
{
    // 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    printf("\t");
    for (int i = 0; i < L.length; i++)
    {
        printf("%d", L.elem[i]);
        if (i != L.length - 1)
            printf(" ");
    }
    printf("\n");
    return OK;
    /********** End **********/
}


// 最大连续子数组和
int MaxSubArray(SqList L)
{
    int maxSum = L.elem[0], currentSum = 0;
    for (int i = 0; i < L.length; i++)
    {
        currentSum = (currentSum > 0) ? currentSum + L.elem[i] : L.elem[i];
        if (currentSum > maxSum)
        {
            maxSum = currentSum;
        }
    }
    return maxSum;
}

// 和为 K 的子数组个数
int SubArrayNum(SqList L, int k)
{
    int count = 0, sum = 0;
    for (int i = 0; i < L.length; i++)
    {
        sum = 0;
        for (int j = i; j < L.length; j++)
        {
            sum += L.elem[j];
            if (sum == k)
            {
                count++;
            }
        }
    }
    return count;
}

// 顺序表排序
void sortList(SqList &L)
{
    for (int i = 0; i < L.length - 1; i++)
    {
        for (int j = 0; j < L.length - i - 1; j++)
        {
            if (L.elem[j] > L.elem[j + 1])
            {
                int temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }
}

// 保存线性表到文件
void saveListToFile(SqList L, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("\t文件打开失败！\n");
        return;
    }
    fprintf(file, "%d\n", L.length); // 保存线性表长度
    for (int i = 0; i < L.length; i++)
    {
        fprintf(file, "%d ", L.elem[i]); // 保存线性表元素
    }
    fclose(file);
    printf("\t线性表已保存到文件：%s\n", filename);
}

// 从文件加载线性表
void loadListFromFile(SqList &L, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("\t文件打开失败！\n");
        return;
    }
    fscanf(file, "%d", &L.length); // 读取线性表长度
    L.elem = (ElemType *)malloc(L.length * sizeof(ElemType));
    for (int i = 0; i < L.length; i++)
    {
        fscanf(file, "%d", &L.elem[i]); // 读取线性表元素
    }
    fclose(file);
    printf("\t线性表已从文件加载：%s\n", filename);
}

// 多个线性表管理
void manageMultipleLists(LISTS &Lists)
{
    printf("\t当前共有 %d 个线性表：\n", Lists.length);
    for (int i = 0; i < Lists.length; i++)
    {
        printf("\t%d. %s\n", i + 1, Lists.elem[i].name);
    }
}

status AddList(LISTS &Lists, char ListName[])
{
    int n, e;
    printf("\t请输入要添加的顺序表数量：");
    scanf("%d", &n);
    while (n--)
    {
        printf("\t请输入要添加的顺序表名称：");
        scanf("%s", ListName);
        for (int i = 0; i <= Lists.length; i++)
        {
            if (strcmp(Lists.elem[i].name, ListName) == 0)
            {
                printf("\t顺序表名称已存在，请重新输入！\n");
                printf("\t请输入要添加的顺序表名称：");
                scanf("%s", ListName);
                i = 0;
            }
        }
        if (Lists.length >= 10)
        { // 假设 elem 数组的最大容量是 10
            printf("\t顺序表数量已达上限，无法添加更多顺序表！\n");
            return ERROR;
        }
        strcpy(Lists.elem[Lists.length].name, ListName);
        Lists.elem[Lists.length].L.length = 0; // 初始化为空线性表
        Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
        if (!Lists.elem[Lists.length].L.elem)
        {
            printf("\t内存分配失败！\n");
            return OVERFLOW;
        }
        Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
        Lists.length++;
        printf("\t请输入要添加的顺序表元素（以 0 结束）：");
        scanf("%d", &e);
        while (e)
        {
            if (ListInsert(Lists.elem[Lists.length - 1].L, Lists.elem[Lists.length - 1].L.length + 1, e) != OK)
            {
                printf("\t插入元素失败！\n");
                return ERROR;
            }
            scanf("%d", &e);
        }
        printf("\t插入顺序表成功！\n");
    }
    return OK;
}

status RemoveList(LISTS &Lists, char ListName[])
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i, j;
    for (i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            // 释放线性表的内存
            free(Lists.elem[i].L.elem);
            // 将后面的元素前移
            for (j = i; j < Lists.length - 1; j++)
            {
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR; // 未找到名称为 ListName 的线性表
    /********** End **********/
}

int LocateList(LISTS Lists, char ListName[])
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            return i + 1; // 返回逻辑序号
        }
    }
    return 0; // 未找到名称为 ListName 的线性表
    /********** End **********/
}