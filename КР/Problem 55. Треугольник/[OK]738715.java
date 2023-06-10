package KR1;

import java.io.*;
public class Task55 {
    static int k;
    static int[][] triangle;
    static int[][] dp;

    static void fill(BufferedReader sc) throws IOException{
        k = Integer.parseInt(sc.readLine());

        triangle = new int[k][k];

        for (int i = 0; i < k; i++) {
            String[] str = sc.readLine().split(" ");
            for (int j = 0; j <= i; j++) {
                triangle[i][j] = Integer.parseInt(str[j]);
            }
        }

        dp = new int[k][k];
        dp[0][0] = triangle[0][0];
    }

    static int getResult(){

        for (int i = 0; i < k - 1; i++) {
            for (int j = 0; j <= i; j++) {
                dp[i+1][j] = Math.max(dp[i+1][j], triangle[i+1][j] + dp[i][j]);
                dp[i+1][j+1] = Math.max(dp[i+1][j+1], triangle[i+1][j+1] + dp[i][j]);
            }
        }

        int res = 0;

        for (int i = 0; i < k; i++) {
            if (dp[k-1][i] > res){
                res = dp[k-1][i];
            }
        }

        return res;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("output.txt")));

        fill(sc);
        sc.close();

//        out.println();
//        for (int i = 0; i < k; i++) {
//            for (int j = 0; j < k; j++) {
//                out.print(triangle[i][j] + " ");
//            }
//            out.println();
//        }
//        out.println();
//        for (int i = 0; i < k; i++) {
//            for (int j = 0; j < k; j++) {
//                out.print(dp[i][j] + " ");
//            }
//            out.println();
//        }
//        out.println();
        out.print(getResult());

        out.close();
    }
}