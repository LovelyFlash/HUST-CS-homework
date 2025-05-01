#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, a, b;
    if(scanf("%d %d %d", &N, &a, &b) != 3){
        return 1;
    }
    
    long long total_area = 0;
    
    for (int i = 0; i < N; i++){
        int x1, y1, x2, y2;
        if(scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4){
            return 1;
        }
        
        int L = 0, R = 0;
        int lx = (x1 > 0 ? x1 : 0);
        int rx = (a < x2 ? a : x2);
        if(rx > lx){
            L = rx - lx;
        } else {
            L = 0;
        }
        
        int B = 0, T = 0;
        int by = (y1 > 0 ? y1 : 0);
        int ty = (b < y2 ? b : y2);
        if(ty > by){
            B = by;
            T = ty;
        }
        int H = (ty > by ? ty - by : 0);
        
        long long area = (long long)L * H;
        total_area += area;
    }
    
    printf("%lld\n", total_area);
    
    return 0;
}
