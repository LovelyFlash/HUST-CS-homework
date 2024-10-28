/********** Begin **********/
#include<stdio.h>
#include<math.h>

int main() {
    char real[100];
    scanf("%s", real);
    int i = 0;
    for(; i<=101; i++)
    {
        if(real[i] != 0)
        {
            char temp = ( ( (real[i]&0x2a )>>1 ) | ( (real[i]&0x15)<<1) );//0,2,4与1,3,5位交换
            real[i] = (real[i]&0xc0) | (( temp<<(int)( (real[i]&0xc0)>>6 ) & 0x3f ) | (temp<<(int)( 8 - (real[i]&0xc0)>>6 ) & 0x3f));
        }
    }
    printf("%s", real);
    return 0;
}
/**********  End **********/