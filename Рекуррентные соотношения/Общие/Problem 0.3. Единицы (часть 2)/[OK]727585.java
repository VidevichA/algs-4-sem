package Rekkurentnie;

import java.util.Scanner;

public class Task0_3 {
    static long binpow (long a,long n) {
        if (n == 0)
            return 1;
        if (n % 2 == 1)
            return binpow (a, n-1) * a;
        else {
            long b = binpow (a, n/2);
            return b * b;
        }
    }

    static long coef = (long) (10e9 + 7);

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();

        long num = 1;
        long den = 1;

        for (int i = n; i > n - k; i--) {
            num = (num * i)%coef;
        }

        for (int i = 1; i <= k ; i++) {
            den = (den*i)%coef;
        }

        System.out.println( (num*binpow(den, coef - 2)) % coef);
    }
}