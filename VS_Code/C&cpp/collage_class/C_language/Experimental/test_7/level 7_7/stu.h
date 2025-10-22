/*测试程序定义了如下结点类型
typedef struct c_node{
    char data;  struct c_node *next;
} C_NODE;
*******************************/
void createLinkList(C_NODE **headp, char s[]) 
{
/************************************* BEGIN *******************************************/
    int i = 0;
    C_NODE *p, *head = NULL, *tail = NULL;
    while (s[i] != '\0') {
        p = (C_NODE *)malloc(sizeof(C_NODE));
        p->data = s[i++];
        if (head == NULL)
            head = p;
        else
            tail->next = p;
        tail = p;
    }
    if (tail != NULL)
        tail->next = NULL;
    *headp = head;
/************************************* BEGIN *******************************************/
}

void judgePalindrome(C_NODE *head)
{
/************************************* BEGIN *******************************************/
    struct c_node *slow = head, *fast = head, *prev = NULL, *temp;
    
    while (fast && fast->next) {
        fast = fast->next->next;
        temp = slow;
        slow = slow->next;
        temp->next = prev;
        prev = temp;
    }
    
    if (fast)
        slow = slow->next;

    while (slow) {
        if (slow->data != prev->data) {
            printf("false\n");
            return;
        }
        slow = slow->next;
        prev = prev->next;
    }
    printf("true\n");
/************************************* BEGIN *******************************************/
}
