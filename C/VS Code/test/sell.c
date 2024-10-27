#include <stdio.h>

typedef struct 
{
    /*建立列表*/
    char name;
    int place;
    int price;
    int quantity;
}SellingMachine;

int main()
{
    char name;
    int place;
    int price;
    int quantity;/*引入暂存数据*/
    int i = 0;
    SellingMachine SellingMachine[100];
    while(i++ <= 100)
    {
        printf("请依次输入货物名称、通道、单价、个数(每输入一个请按回车确定),全部完成后输入F并回车\n");
        char input;
        scanf("%c", &input);
        getchar();
        if(input != 'F')
        {
            int n = 0, m = 0;
            name = input;
            scanf("%d", &place);
            getchar ();
            scanf("%d", &price);
            getchar();
            scanf("%d", &quantity);
            getchar();
            SellingMachine[place - 1].name = name;              /*将暂存数据转移到格式表*/
            SellingMachine[place - 1].place = place;
            SellingMachine[place - 1].price = price;
            SellingMachine[place - 1].quantity = quantity;
            if(place > n)
            {
                n = place;                                      /*为后续顺序读取做准备*/
            }
            else
            {
                m = 0;
            }
        
        }
        else
        {
            break;
        }
        
    };

    for(i = 0; i < place; i++) 
    {
        printf("在%d号通道，摆放了%d个%c货物，单价为%d元\n", SellingMachine[i].place, SellingMachine[i].quantity, SellingMachine[i].name, SellingMachine[i].price);
        /*按货道顺序输出*/
    }
    return 0;
}