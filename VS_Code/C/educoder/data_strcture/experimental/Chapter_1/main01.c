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
    LISTS Lists; // ����ͷָ��
    Lists.elem[0].L = L;
    strcpy(Lists.elem[0].name, "���Ա�1"); // ��ʼ��˳�������
    L.elem = NULL;
    int op = 1;
    while (op)
    {
        // system("cls"); // ������
        printf("\n\n");
        printf("      ˳�������˵� \n");
        printf("===============================================\n");
        printf("  ����������\n");
        printf("    1. ��ʼ��˳���           2. ����˳���\n");
        printf("    3. ���˳���             4. �ж�˳����Ƿ�Ϊ��\n");
        printf("    5. ��ȡ˳�����\n");
        printf("-----------------------------------------------\n");
        printf("  Ԫ�ز�����\n");
        printf("    6. ��ȡָ��λ��Ԫ��       7. ����Ԫ��λ��\n");
        printf("    8. ��ȡǰ��Ԫ��           9. ��ȡ���Ԫ��\n");
        printf("   10. ����Ԫ��              11. ɾ��Ԫ��\n");
        printf("-----------------------------------------------\n");
        printf("  ����������\n");
        printf("   12. ����˳���\n");
        printf("-----------------------------------------------\n");
        printf("  ���Ӳ�����\n");
        printf("   13. ����������������    14. ���Ϊ K �����������\n");
        printf("   15. ˳�������            16. �������Ա��ļ�\n");
        printf("   17. ���ļ��������Ա�\n");
        printf("-----------------------------------------------\n");
        printf("  �����Ա����\n");
        printf("   18. ���˳���           19. ɾ��˳���\n");
        printf("   20. ��λ˳���           21. �޸�˳�������\n");
        printf("    0. �˳�����\n");
        printf("===============================================\n");
        printf("  ���ڲ�����˳������ƣ�%s\n", Lists.elem[0].name);
        printf("  ��ѡ����Ĳ��� [0 ~ 21]: ");
        scanf("%d", &op);

        // �����Ӧ�Ĺ�������
        switch (op)
        {
        case 1:
            printf("\t��ʼ��˳���\n");
            break;
        case 2:
            printf("\t����˳���\n");
            break;
        case 3:
            printf("\t���˳���\n");
            break;
        case 4:
            printf("\t�ж�˳����Ƿ�Ϊ��\n");
            break;
        case 5:
            printf("\t��ȡ˳�����\n");
            break;
        case 6:
            printf("\t��ȡָ��λ��Ԫ��\n");
            break;
        case 7:
            printf("\t����Ԫ��λ��\n");
            break;
        case 8:
            printf("\t��ȡǰ��Ԫ��\n");
            break;
        case 9:
            printf("\t��ȡ���Ԫ��\n");
            break;
        case 10:
            printf("\t����Ԫ��\n");
            break;
        case 11:
            printf("\tɾ��Ԫ��\n");
            break;
        case 12:
            printf("\t����˳���\n");
            break;
        case 13:
            printf("\t����������������\n");
            break;
        case 14:
            printf("\t���Ϊ K �����������\n");
            break;
        case 15:
            printf("\t˳�������\n");
            break;
        case 16:
            printf("\t�������Ա��ļ�\n");
            break;
        case 17:
            printf("\t���ļ��������Ա�\n");
            break;
        case 18:
            printf("\t���˳���\n");
            break;
        case 19:
            printf("\tɾ��˳���\n");
            break;
        case 20:
            printf("\t��λ˳���\n");
            break;
        case 21:
            printf("\t�޸�˳�������\n");
            break;
        case 0:
            printf("\t�˳�����\n");
            break;
        default:
            printf("����������������룡\n");
            break;
        }

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
            printf("\t��������������Ϊ%d\n", MaxSubArray(L));
            break;
        case 14:
            // printf("\n----SubArrayNum���ܴ�ʵ�֣�\n");
            int k;
            printf("\t������Ҫ��ѯ��������ͣ�");
            scanf("%d", &k);
            int count;
            count = SubArrayNum(L, k);
            if (count)
                printf("\t�����Ϊk����������%d��\n", k);
            else
                printf("\tû������Ҫ��������飡\n");
            break;
        case 15:
            // printf("\n----sortList���ܴ�ʵ�֣�\n");
            sortList(L);
            printf("\t˳���������ϣ�");
            break;
        case 16:
            // printf("\n----saveListToFile���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ���浽���ļ����ƣ�");
            char filename_w[40];
            scanf("%s", filename_w);
            saveListToFile(L, filename_w);
            break;
        case 17:
            // printf("\n----loadListFromFile���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ��ȡ���ļ����ƣ�");
            char filename_r[40];
            scanf("%s", filename_r);
            loadListFromFile(L, filename_r);
            break;
        case 18:
            // printf("\n----AddList���ܴ�ʵ�֣�\n");

            char listname[40];
            AddList(Lists, listname);
            break;
        case 19:
            // printf("\n----RemoveList���ܴ�ʵ�֣�\n");
            printf("\t������Ҫɾ����˳������ƣ�");
            scanf("%s", listname);
            if (RemoveList(Lists, listname))
                printf("\t���Ա�ɹ�ɾ����\n");
            else
                printf("\tδ�ҵ������Ƶ�˳���\n");
            break;
        case 20:
            // printf("\n----LocateList���ܴ�ʵ�֣�\n");
            printf("\t������Ҫ���ҵ�˳������ƣ�");
            scanf("%s", listname);
            int num;
            num = LocateList(Lists, listname);
            if (num)
            {
                printf("\t���ҵ���˳���Ϊ��%d��\n", num);
                L = Lists.elem[num - 1].L;
                printf("\t�ѽ�������������˳����Ϊ��˳���\n");
            }
            else
                printf("\tδ�ҵ������Ƶ�˳���\n");
            break;
        case 21:
            printf("\t������Ҫ�޸ĵ�˳������ƣ�");
            scanf("%s", listname);
            num = LocateList(Lists, listname);
            printf("\t����������ȡ�����֣�");
            scanf("%s", listname);
            if (strcpy(Lists.elem[num - 1].name, listname))
                printf("\t�޸ĳɹ���\n");
            else
                printf("\t�޸�ʧ�ܣ�\n");
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