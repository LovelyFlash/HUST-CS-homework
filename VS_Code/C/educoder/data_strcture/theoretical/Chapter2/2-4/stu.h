void TriLinkList(LinkList A, LinkList B, LinkList C)
{
    /**********Begin**********/
    NODE *tem = (NODE *)malloc(sizeof(NODE)), *p;
    p = tem;
    NODE *p1 = A->next, *p2 = B->next, *p3 = C->next;
    while (p2 != NULL && p3 != NULL)
    {
        if (p2->data < p3->data)
        {
            p2 = p2->next;
        }
        else if (p2->data == p3->data)
        {
            p->next = (NODE *)malloc(sizeof(NODE));
            p = p->next;
            p->data = p2->data;
            p2 = p2->next;
            p3 = p3->next;
        }
        else
        {
            p3 = p3->next;
        }
    }
    p->next = NULL;
    p = tem->next;
    p1 = A;
    while (p1 != nullptr)
    {
        if (p == NULL)
        {
            p1 = p1->next;
            p = tem->next;
        }
        else if (p1->next != nullptr && p1->next->data == p->data)
        {
            p1->next = p1->next->next;
        }

        else
            p = p->next;
    }
    /***********End**********/
}