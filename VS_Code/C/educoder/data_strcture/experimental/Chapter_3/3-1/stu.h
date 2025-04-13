status CreateBiTree(BiTree &T, TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = 0;
    TElemType e = definition[i++];
    if (e.key == -1) // 结束条件
    {
        T = NULL;
    }
    
    /********** End **********/
}
