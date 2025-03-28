status RemoveList(LISTS &Lists, char ListName[]) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i, j;
    for (i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            // 释放线性表的内存
            free(Lists.elem[i].L.elem);
            // 将后面的元素前移
            for (j = i; j < Lists.length - 1; j++) {
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR; // 未找到名称为 ListName 的线性表
    /********** End **********/
}