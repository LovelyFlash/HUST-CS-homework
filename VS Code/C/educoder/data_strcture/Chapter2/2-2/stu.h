// void adjust(DuLinkList L)
// {
//     /**********Begin**********/
//     DuLinkList c1 = L->next;
//     while (1)
//     {
//         if (c1->next->next != L && c1->next != L)
//         {
//             c1->next = c1->next->next;
//             c1 = c1->next;
//         }
//         else
//             break;
//     }
//     if (c1->next == L)
//     {
//         c1->next = c1->prior;
//         c1 = c1->next;
//         while (c1->prior->prior != L)
//         {
//             c1->next = c1->prior->prior;
//             c1 = c1->next;
//         }
//     }
//     else
//     {
//         c1=c1->next;
//         while (c1->prior->prior != L)
//         {
//             c1->next = c1->prior->prior;
//             c1 = c1->next;
//         }
//     }
//     c1 = L->next;
//     while (c1->next->prior->prior != L)
//     {
//         c1->next->prior = c1;
//         c1 = c1->next;
//     }
//     c1->next->prior = c1;
//     c1->next->next = L;
//     L->prior = c1->next;
//     /**********End**********/
// }
void adjust(DuLinkList L)
{
    // 空链表或只有一个结点无需调整
    if(L->next == L || L->next->next == L)
        return;
        
    // 分离出奇数和偶数位置的结点（脱离原循环）
    DuLinkList oddHead = NULL, evenHead = NULL;
    DuLinkList oddTail = NULL, evenTail = NULL;
    DuLinkList cur = L->next;
    int index = 1;
    while(cur != L)
    {
        DuLinkList next = cur->next;  // 保存下一个结点
        // 脱离原链表（断开循环）
        cur->next = cur->prior = NULL;
        if(index % 2 == 1)  // 奇数位置
        {
            if(oddHead == NULL)
                oddHead = oddTail = cur;
            else
            {
                oddTail->next = cur;
                cur->prior = oddTail;
                oddTail = cur;
            }
        }
        else  // 偶数位置
        {
            if(evenHead == NULL)
                evenHead = evenTail = cur;
            else
            {
                evenTail->next = cur;
                cur->prior = evenTail;
                evenTail = cur;
            }
        }
        index++;
        cur = next;
    }
    
    // 逆置偶数链表
    DuLinkList revEven = NULL;
    cur = evenHead;
    while(cur)
    {
        DuLinkList next = cur->next;
        cur->next = revEven;
        if(revEven)
            revEven->prior = cur;
        cur->prior = NULL;
        revEven = cur;
        cur = next;
    }
    
    // 拼接奇数链表与逆置后的偶数链表
    if(oddTail)
    {
        oddTail->next = revEven;
        if(revEven)
            revEven->prior = oddTail;
    }
    
    // 重构成带头结点的循环双向链表
    L->next = oddHead;
    if(oddHead)
        oddHead->prior = L;
    // 找到新的尾结点
    DuLinkList tail = oddHead;
    while(tail && tail->next)
        tail = tail->next;
    if(tail)
    {
        tail->next = L;
        L->prior = tail;
    }
    else  // 如果链表为空（不应发生）
    {
        L->next = L;
        L->prior = L;
    }
}
