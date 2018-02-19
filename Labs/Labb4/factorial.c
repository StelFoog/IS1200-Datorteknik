#include <stdio.h>

int multiply(int a, int b)
{
    int product = 0;
    
    for(int i = 1; i <= b ; i++)
    {
        product += a;
    }

    return product;
}

int main()
{
    int n = 5;
    int res = 1;
    for(int i =  1; i <n; i++){
        res += multiply(i, res);
    }
    printf("%d", res);
    return 0;
}