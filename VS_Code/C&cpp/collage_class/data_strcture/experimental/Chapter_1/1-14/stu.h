#include <string.h>

status AddList(LISTS &Lists, char ListName[]) {
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (Lists.length >= 10) { // ���� elem �������������� 10
        return ERROR;
    }
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L.length = 0; // ��ʼ��Ϊ�����Ա�
    Lists.elem[Lists.length].L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!Lists.elem[Lists.length].L.elem) {
        return OVERFLOW;
    }
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;
    Lists.length++;
    return OK;
    /********** End **********/
}