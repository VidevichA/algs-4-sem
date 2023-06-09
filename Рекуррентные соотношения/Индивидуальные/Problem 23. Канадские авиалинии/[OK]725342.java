import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("in.txt"));
        int citiesCount = scanner.nextInt();
        int routsCount = scanner.nextInt();

        ArrayList<String> cities = new ArrayList<>(citiesCount);
        boolean routs[][] = new boolean[citiesCount][citiesCount];

        for (int i = 0; i < citiesCount; i++){
            cities.add(scanner.next());
        }

        int index1;
        int index2;

        for (int i = 0; i < routsCount; i++){
            index1 = cities.indexOf(scanner.next());
            index2 = cities.indexOf(scanner.next());
            routs[index2][index1] = true;
            routs[index1][index2] = true;
        }

        int[] fromEastToWest = new int[citiesCount];

        fromEastToWest[0] = 1;
        for (int i = 1; i < citiesCount; i++){
            for (int j = 0; j < i; j++){
                if(routs[i][j] && fromEastToWest[j] + 1 > fromEastToWest[i] && (fromEastToWest[j] != 0 || j == 0)) {
                    fromEastToWest[i] = fromEastToWest[j] + 1;
                }
            }
        } // (n^2)/2

        int[][] dp = new int[citiesCount][citiesCount];
        dp[0][0] = 1;
        for (int i = 0; i < citiesCount; i++){
            dp[i][0] = fromEastToWest[i];
            dp[0][i] = fromEastToWest[i];
        }

        for (int i = 1; i < citiesCount; i++){
            for (int j = 1; j <= i; j++){
                if (i == j){
                    for (int k = 0; k < i; k++) {
                        if (routs[k][j] && dp[k][j] > dp[i][j]){
                            dp[i][j] = dp[k][j];
                        }
                    }
                } else {
                    for (int k = 0; k < i; k++) {
                        if (k != j && routs[i][k]) {
                            if (dp[k][j] + 1 > dp[i][j] && dp[k][j] != 0) {
                                dp[i][j] = dp[k][j] + 1;
                                dp[j][i] = dp[i][j];
                            }

                        }
                    }
                }
            }
        }

        FileWriter fileWriter = new FileWriter(new File("out.txt"));
        if (dp[citiesCount-1][citiesCount-1] == 0) {
            fileWriter.write("No solution");
        } else {
            fileWriter.write(String.valueOf(dp[citiesCount-1][citiesCount-1]));
        }
        fileWriter.flush();
        fileWriter.close();
    }
}