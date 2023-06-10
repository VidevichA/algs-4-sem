package Rekkurentnie;

import java.math.BigInteger;
import java.util.Scanner;

public class Task0_2 {
    static BigInteger fact(BigInteger n){
        BigInteger res = BigInteger.valueOf(1);
        for (int i = 1; i <= n.intValue(); i++) {
            res = res.multiply(BigInteger.valueOf(i));
        }
        return res;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        BigInteger numberN = sc.nextBigInteger();
        BigInteger numberK = sc.nextBigInteger();
        long coef = (long)(10e9 + 7);
        System.out.println(
               ( fact(numberN).divide( fact(numberK).multiply( fact(numberN.subtract(numberK) ) ) ) ).mod( BigInteger.valueOf(coef) )
        );
    }
}