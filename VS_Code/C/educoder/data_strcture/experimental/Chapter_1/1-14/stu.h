#include <string.h>

status AddList(LISTS &Lists, char ListName[]) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (Lists.length >= 10) { // 假设 elem 数组的最大容量是 10
        return ERROR;
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.length = 0; // 初始化为空线性表
    Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!Lists.elem[Lists.length].L.elem) {
        return OVERFLOW;
    }
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    Lists.length++;
    return OK;
    /********** End **********/
}