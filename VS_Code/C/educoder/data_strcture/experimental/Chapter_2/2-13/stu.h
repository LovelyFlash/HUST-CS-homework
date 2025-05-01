status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L == NULL)
        return INFEASIBLE;
    FILE *file = fopen(FileName, "w");
    if (file == NULL)
        return INFEASIBLE;
    LinkList p = L->next;
    while (p != NULL)
    {
        fprintf(file, "%d ", p->data);
        p = p->next;
    }
    fclose(file);
    return OK;
    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (L != NULL)
        return INFEASIBLE;
    FILE *file = fopen(FileName, "r");
    if (file == NULL)
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if (L == NULL)
        return INFEASIBLE;
    L->next = NULL;
    LinkList tail = L;
    tail->next = NULL;
    int data;
    fscanf(file, "%d", &data);
    while (!feof(file))
    {
        LinkList newNode = (LinkList)malloc(sizeof(LNode));
        if (newNode == NULL)
            return INFEASIBLE;
        newNode->data = data;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        fscanf(file, "%d", &data);
    }
    fclose(file);
    return OK;
    /********** End 2 **********/
}
