#include <stdio.h>

typedef struct 
{
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
    int quantity;
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
            name = input;
            scanf("%d", &place);
            getchar ();
            scanf("%d", &price);
            getchar();
            scanf("%d", &quantity);
            getchar();
            SellingMachine[place - 1].name = name;
            SellingMachine[place - 1].place = place;
            SellingMachine[place - 1].price = price;
            SellingMachine[place - 1].quantity = quantity;
        
        }
        else
        {
            break;
        }
        
    };

    for(i = 0; i < place; i++) 
    {
        printf("在%d号通道，摆放了%d个%c货物，单价为%d元\n", SellingMachine[i].place, SellingMachine[i].quantity, SellingMachine[i].name, SellingMachine[i].price);
    }
    return 0;
}