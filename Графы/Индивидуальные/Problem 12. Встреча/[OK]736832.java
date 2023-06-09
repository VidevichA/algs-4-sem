import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("input.in"));
        int n = Integer.parseInt(scanner.next());
        int m = Integer.parseInt(scanner.next());
        int[][] city = new int[n][n];
        int minSum = 0;
        int houseNumber = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                city[i][j] = Integer.MAX_VALUE/2 -1;
            }
        }
        for (int i = 0; i < m; i++) {
            int x = scanner.nextInt() - 1;
            int y = scanner.nextInt() - 1;
            city[x][y] = city[y][x] = scanner.nextInt();
        }

        for (int j = 0; j < n; j++) {
            city[j][j] = 0;
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (city[i][j] > city[i][k] + city[k][j]) {
                        city[i][j] = city[i][k] + city[k][j];
                    }
                }
            }
        }

        for (int i = 0; i < n; i++){
            minSum += city[0][i];
            houseNumber = 1;
        }
        for (int i = 1; i < n; i++){
            int temp = 0;
            for (int j = 0; j < n; j++){
                temp += city[i][j];
            }
            if (temp <= minSum){
                minSum = temp;
                houseNumber = i+1;
            }
        }

        FileWriter fileWriter = new FileWriter(new File("output.out"));
        fileWriter.write(houseNumber + " ");
        fileWriter.write(String.valueOf(minSum));
        fileWriter.close();
    }
}