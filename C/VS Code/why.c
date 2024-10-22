/********** Begin **********/
#include<stdio.h>
#include<math.h>

int main() {
    int n, a, b, c;
    scanf("%d", &n);

    for (a=1; a*a <= n; a++) {
        
        for (b=1; b < a; b++){
            int x = a*a - 10*b*b;
            
            if (x >= 0) {
                int c = sqrt(x);

                if (c) {
                    printf("%d=%d*%d=%d*%d*10+%d*%d\n", a*a, a, a, b, b, c, c);
                    break;
                }
            }
        }

    }
    return 0;
}
/**********  End **********/