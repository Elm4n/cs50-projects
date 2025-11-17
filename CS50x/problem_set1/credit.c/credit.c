#include <cs50.h>
#include <stdio.h>
int main(void)
{
    long number = get_long("Number : ");
    int count = 0;
    long temp = number;
    while (temp > 0){
        temp /= 10;
        count++;
    }
        if (count !=15 && count !=13 && count !=16){
            printf("INVALID\n");
            return 0;
        }
        int sum1 = 0;
        int sum2 = 0;
        int total = 0;
        int mod1, mod2;
        int d1, d2;
        long x = number;
        do {
            mod1 = x % 10;
            x /= 10;
            sum1 += mod1;

            mod2 = x % 10;
            x /= 10;
            mod2 *= 2;
            d1 = mod2 % 10;
            d2 = mod2 / 10;
            sum2 += d1 + d2;
        }
        while (x > 0);
        total = sum1 + sum2;
        if (total % 10 != 0){
            printf("INVALID\n");
            return 0;
        }
        long ct = number;
        do {
        ct /= 10;
        } while (ct > 100);
        if (count == 15 && (ct == 34 || ct == 37)){
            printf("AMEX\n");
        } else if (count == 16 && (ct >= 51 && ct <= 55)){
            printf("MASTERCARD\n");
        } else if ((count == 16 || count ==13) && (ct >= 40 && ct < 50)){
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
}
