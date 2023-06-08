import java.io.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Scanner;


public class Ways {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(new InputStreamReader(new FileInputStream("in.txt")));
        FileWriter writer = new FileWriter("out.txt");
        int capacity, counter;
        int sum = 0;
        capacity = scan.nextInt();
        counter = scan.nextInt();
        //scan.next();
        for(int i =0;i < counter; i++){
            sum += scan.nextInt();
        }
        if(sum > capacity - counter + 1){
            writer.write("0");
            writer.flush();
        }
        else {
            int vPos = capacity - sum + 1;
            BigDecimal dp[][] = new BigDecimal[counter + 1][vPos + 1];
            for (int i = 0; i <= counter; i++) {
                dp[i][i] = BigDecimal.ONE;
            }
            for (int j = 1; j <= vPos; j++) {
                dp[0][j] = BigDecimal.ONE;
            }
            for (int i = 1; i < counter + 1; i++) {
                for (int j = i + 1; j < vPos + 1; j++) {
                    dp[i][j] = dp[i][j - 1].add(dp[i - 1][j - 1]);
                }
            }
            writer.write(dp[counter][vPos].toString());
            writer.flush();
        }
    }
}