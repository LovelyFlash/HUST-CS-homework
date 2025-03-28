int LocateList(LISTS Lists, char ListName[]) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            return i + 1; // 返回逻辑序号
        }
    }
    return 0; // 未找到名称为 ListName 的线性表
    /********** End **********/
}