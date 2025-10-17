#include <stdio.h>
#include <stdbool.h>

int sum = 0, current_sum = 0;

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

void combination(int *nums, int start, int n, int k, int count)
{
    if (count == k)
    {
        if (is_prime(current_sum))
            sum++;
        return;
    }
    for (int i = start; i < n; i++)
    {
        current_sum += nums[i];
        combination(nums, i + 1, n, k, count + 1);
        current_sum -= nums[i];
    }
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    combination(arr, 0, n, k, 0);
    printf("%d", sum);
    return 0;
}