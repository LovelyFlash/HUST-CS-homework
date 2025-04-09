// ���ݽṹʵ��һ��˳�����ʾ
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"  // ����������͵Ķ���
#include "func.h" // ��ع��ܵĶ���

int main(void)
{
    SqList L;
    L.elem = NULL;
    int op = 1;
    while (op)
    {
        system("cls"); // ������
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       9. NextElem\n");
        printf("    	  2. DestroyList    10. ListInsert\n");
        printf("    	  3. ClearList      11. ListDelete \n");
        printf("    	  4. ListEmpty      12. ListTrabverse\n");
        printf("    	  5. ListLength     13. MaxSubArray\n");
        printf("    	  6. GetElem        14. SubArrayNum\n");
        printf("    	  7. LocateElem     15. sortList\n");
        printf("    	  8. PriorElem      16. .������\n");
        printf("    	  9. PriorElem      17. .������\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ��� [0 ~ 16]: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // printf("\n----IntiList���ܴ�ʵ�֣�\n");
            if (InitList(L) == OK)
                printf("\t���Ա����ɹ���\n");
            else
                printf("\t���Ա���ʧ�ܣ�\n");
            break;
        case 2:
            // printf("\n----DestroyList���ܴ�ʵ�֣�\n");
            if (DestroyList(L) == OK)
                printf("\t���Ա����ٳɹ���\n");
            else
                printf("\t���Ա�����ʧ�ܣ�\n");
            break;
        case 3:
            // printf("\n----ClearList���ܴ�ʵ�֣�\n");
            if (ClearList(L) == OK)
                printf("\t���Ա���ճɹ���\n");
            else
                printf("\t���Ա����ʧ�ܣ�\n");
            break;
        case 4:
            // printf("\n----ListEmpty���ܴ�ʵ�֣�\n");
            if (ListEmpty(L) == OK)
                printf("\t���Ա��ǿձ�\n");
            else
                printf("\t���Ա��ǿձ�\n");
            break;
        case 5:
            // printf("\n----ListLength���ܴ�ʵ�֣�\n");
            if (ListLength(L) == OK)
                printf("\t���Ա�ĳ���Ϊ��%d\n", ListLength(L));
            else
                printf("\t���Ա�ĳ��Ȼ�ȡʧ�ܣ�\n");

            break;
        case 6:
            // printf("\n----GetElem���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ��ȡ��Ԫ�ص���ţ�");
            int i;
            ElemType e0;
            scanf("%d", &i);
            if (GetElem(L, i, e0) == OK)
                printf("\t���Ա�ĵ�%d��Ԫ��Ϊ��%d\n", i, GetElem(L, i, e0));
            else
                printf("\t���Ա�ĵ�%d��Ԫ�ػ�ȡʧ�ܣ�\n", i);
            break;
        case 7:
            // printf("\n----LocateElem���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ���ҵ�Ԫ�أ�");
            int e;
            scanf("%d", &e);
            if (LocateElem(L, e) == OK)
                printf("\t���Ա���Ԫ��%d�����Ϊ��%d\n", e, LocateElem(L, e));
            else
                printf("\t���Ա���Ԫ��%d�Ĳ���ʧ�ܣ�\n", e);
            break;
        case 8:
            // printf("\n----PriorElem���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ���ҵ�Ԫ�أ�");
            int e1;
            ElemType next;
            scanf("%d", &e1);
            if (PriorElem(L, e1, next) == OK)
                printf("\t���Ա���Ԫ��%d��ǰ��Ԫ��Ϊ��%d\n", e1, PriorElem(L, e1, next));
            else
                printf("\t���Ա���Ԫ��%d��ǰ��Ԫ�ز���ʧ�ܣ�\n", e1);
            break;
        case 9:
            // printf("\n----NextElem���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ���ҵ�Ԫ�أ�");
            int e2;
            ElemType pre;
            scanf("%d", &e2);
            if (NextElem(L, e2, pre) == OK)
                printf("\t���Ա���Ԫ��%d�ĺ��Ԫ��Ϊ��%d\n", e2, NextElem(L, e2, pre));
            else
                printf("\t���Ա���Ԫ��%d�ĺ��Ԫ�ز���ʧ�ܣ�\n", e2);
            break;
        case 10:
            // printf("\n----ListInsert���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ�����Ԫ�أ�");
            ElemType e3;
            scanf("%d", &e3);
            printf("\t������Ҫ�����λ�ã�");
            int i1;
            scanf("%d", &i1);
            if (ListInsert(L, i1, e3) == OK)
                printf("\t���Ա���Ԫ��%d����ɹ���\n", e3);
            else
                printf("\t���Ա���Ԫ��%d����ʧ�ܣ�\n", e3);
            break;
        case 11:
            // printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            ElemType e4;
            printf("\t������Ҫɾ����λ�ã�");
            int i2;
            scanf("%d", &i2);
            if (ListDelete(L, i2, e4) == OK)
                printf("\t���Ա���Ԫ��%dɾ���ɹ���\n", e4);
            else
                printf("\t���Ա���Ԫ��%dɾ��ʧ�ܣ�\n", e4);
            break;
        case 12:
            // printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");
            if (ListTraverse(L) == OK)
                printf("\t���Ա�����ɹ���\n");
            else
                printf("\t���Ա����ʧ�ܣ�\n");
            break;
        case 13:
            // printf("\n----MaxSubArray���ܴ�ʵ�֣�\n");
            
            break;
        case 14:
            printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            break;
        case 15:
            printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            break;
        case 16:
            printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            break;
        case 17:
            printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            break;
        default:
            printf("����������������룡\n");
            break;
        }
        printf("\t�밴�س�������...");
        getchar();
        getchar();
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}