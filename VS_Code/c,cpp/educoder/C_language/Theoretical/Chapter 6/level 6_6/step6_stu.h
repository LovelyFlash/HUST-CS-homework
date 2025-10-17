
/**
  按任务要求补全该函数
  用递归实现辗转相除法
 **/
int gcd(int x, int  y)
{
	/**********  Begin  **********/
    if(x != 0 && y != 0)
    {
        printf("%d %d\n", x, y);
        return gcd(y, x%y);
    }
    else 
    {
        printf("%d %d\n", x, y);
        return x;
    }
    /**********  End  **********/
}