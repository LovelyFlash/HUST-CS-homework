#include<stdio.h>

#define MAX_CHANNELS 30

typedef struct {
    char item;
    int price;
    int quantity;
} VendingMachineItem;

VendingMachineItem vendingmachineitem[MAX_CHANNELS];

void init() {
    for (int n = 0; n < MAX_CHANNELS; n++) {
        vendingmachineitem[n].item = 0;
        vendingmachineitem[n].price = 0;
        vendingmachineitem[n].item = 0;
    }
}

void main() {
    char item;
    char state[5];
    int price, channels, quantity;
    
    printf("请输入装载货物信息（格式：名称 货道 数量 价格）（输入END退出）：");
    
    scanf_s("%s", &state);
    printf("停止装载");
    if (state == "END") {
        printf("停止装载");
        
    }
    scanf_s("%c %d %d %d", &item, &channels, &quantity, &price);
        
    vendingmachineitem[channels - 1].item = item;
    vendingmachineitem[channels - 1].price = price;
    vendingmachineitem[channels - 1].item = item;
    printf("AA");
    
}