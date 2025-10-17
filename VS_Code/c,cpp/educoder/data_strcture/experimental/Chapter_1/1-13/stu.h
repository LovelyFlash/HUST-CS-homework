status SaveList(SqList L, char FileName[])
{
    // 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    FILE *fp = fopen(FileName, "wb");
    if (!fp) {
        return INFEASIBLE;
    }
    fwrite(&L.length, sizeof(int), 1, fp);
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
    /********** End **********/
}

status LoadList(SqList &L, char FileName[])
{
    // 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        return INFEASIBLE;
    }
    FILE *fp = fopen(FileName, "rb");
    if (!fp) {
        return INFEASIBLE;
    }
    fread(&L.length, sizeof(int), 1, fp);
    L.elem = (ElemType *)malloc(L.length * sizeof(ElemType));
    if (!L.elem) {
        fclose(fp);
        return INFEASIBLE;
    }
    fread(L.elem, sizeof(ElemType), L.length, fp);
    fclose(fp);
    return OK;
    /********** End **********/
}