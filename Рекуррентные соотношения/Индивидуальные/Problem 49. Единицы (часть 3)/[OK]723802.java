import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("input.txt"));

        long A = scanner.nextLong();
        long B = scanner.nextLong();
        int n = scanner.nextInt();

        char[] AStr = Long.toBinaryString(A).toCharArray();
        char[] BStr = Long.toBinaryString(B).toCharArray();

        ArrayList<Integer> A1Indexes = new ArrayList<>();
        ArrayList<Integer> B1Indexes = new ArrayList<>();

        int ASize = AStr.length;
        int BSize = BStr.length;

        long result = 0;

        for (int i = 0; i < ASize; i++){
            if (AStr[i] == '1') A1Indexes.add(ASize - i -1);
        }
        for (int i = 0; i < BSize; i++){
            if (BStr[i] == '1') B1Indexes.add(BSize - i -1);
        }
        if (B1Indexes.equals(A1Indexes)) {
            if (n == B1Indexes.size()) {
                result = 1;
            }
        }else {
            long temp;
            int s1 = B1Indexes.size();
            for (int j = 0; j < s1; j++){
                if (B1Indexes.get(j) >= n-j){
                    temp = 1;
                    for (int i = 1; i <= B1Indexes.get(j) - n + j; i++){
                        if (B1Indexes.get(j) - i + 1 > n - j) temp *= B1Indexes.get(j) - i + 1 ;
                        temp /= i;
                    }
                    result += temp;
                }

            }

            s1 = A1Indexes.size();
            for (int j = 0; j < s1; j++){
                if (A1Indexes.get(j) >= n - j){
                    temp = 1;
                    for (int i = 1; i <= A1Indexes.get(j) - n + j; i++){
                        if (A1Indexes.get(j) - i + 1 > n - j) temp *= A1Indexes.get(j) - i + 1 ;
                        temp /= i;
                    }
                    result -= temp;
                }
            }
            if (B1Indexes.size() == n) result++;
        }



        FileWriter fileWriter = new FileWriter(new File("output.txt"));
        fileWriter.write(String.valueOf(result));
        fileWriter.flush();
        fileWriter.close();
    }
}