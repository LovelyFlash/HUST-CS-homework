void iniQueue(QUEUE &Q)
//该函数实现初始化Q
{
/***************begin***************/
    Q.front = 0;
    Q.length = 0;
/*************** end ***************/
}

int enQueue(QUEUE &Q, ElemType e)
//将元素e入队Q。成功入队返回1，否则返回0
{
/***************begin***************/
    if (Q.length == MAXLENGTH) {
        return 0; // 队列满
    }
    int rear = (Q.front + Q.length) % MAXLENGTH;
    Q.elem[rear] = e;
    Q.length++;
    return 1;
/*************** end ***************/
}

int deQueue(QUEUE &Q, ElemType &e)
//将Q队首元素出队，赋值给e。成功出队返回1，否则返回0
{
/***************begin***************/
    if (Q.length == 0) {
        return 0; // 队列空
    }
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % MAXLENGTH;
    Q.length--;
    return 1;
/*************** end ***************/
}