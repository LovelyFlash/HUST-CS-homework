void inistack(TWSTACK &S)
//该函数实现初始化S，得到2个空栈。根据双向栈的示意图，理解初始化要求。
{
/***************begin***************/
    S.top1 = 0;
    S.top2 = N - 1;
/*************** end ***************/
}

int push(TWSTACK &S, int i, ElemType e)
//i取值1或2，分别对应左或右栈，将元素e压入S的对应栈。成功入栈返回1，否则返回0
{
/***************begin***************/
    if (S.top1 > S.top2) {
        return 0; // 栈满
    }
    if (i == 1) {
        S.elem[S.top1++] = e;
    } else if (i == 2) {
        S.elem[S.top2--] = e;
    } else {
        return 0; // 非法的栈编号
    }
    return 1;
/*************** end ***************/
}

int pop(TWSTACK &S, int i, ElemType &e)
//i取值1或2，分别对应左或右栈，将S对应栈的栈顶元素出栈，赋值给e。成功出栈返回1，否则返回0
{
/***************begin***************/
    if (i == 1) {
        if (S.top1 == 0) {
            return 0; // 栈1空
        }
        e = S.elem[--S.top1];
    } else if (i == 2) {
        if (S.top2 == N - 1) {
            return 0; // 栈2空
        }
        e = S.elem[++S.top2];
    } else {
        return 0; // 非法的栈编号
    }
    return 1;
/*************** end ***************/
}