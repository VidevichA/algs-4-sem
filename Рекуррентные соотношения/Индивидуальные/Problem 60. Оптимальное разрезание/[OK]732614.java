package Rekkurentnie;

import java.io.*;
import java.util.Scanner;

public class Task60 {

    static int x, y, x1, y1, x2, y2;

    static void fillSizes(BufferedReader sc) throws IOException{
        String[] str = sc.readLine().split(" ");
        x = Integer.parseInt(str[0]); y = Integer.parseInt(str[1]);
        x1 = Integer.parseInt(str[2]); y1 = Integer.parseInt(str[3]);
        x2 = Integer.parseInt(str[4]); y2 = Integer.parseInt(str[5]);
        sc.close();
    }

    static boolean isOneOfRectangles(int i, int j){
        return i == x1 - 1 && j == y1 - 1
            || i == y1 - 1 && j == x1 - 1
            || i == x2 - 1 && j == y2 - 1
            || i == y2 - 1 && j == x2 - 1;
    }

    static int getResult(){
        int[][] field = new int[x][y];

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (isOneOfRectangles(i,j)){
                    field[i][j] = 0;
                }
                else{
                    field[i][j] = (i + 1)*(j+1);

                    int sum = 1;
                    for (int k = 0; k < i; ++k) {
                        sum = field[k][j] + field[i - 1 - k][j];
                        if (sum < field[i][j]){
                            field[i][j] = sum;
                        }
                    }
                    for (int k = 0; k < j; ++k) {
                        sum = field[i][k] + field[i][j - 1 - k];
                        if (sum < field[i][j]){
                            field[i][j] = sum;
                        }
                    }
                }
            }
        }

        return field[x-1][y-1];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));
        fillSizes(sc);
        out.print(getResult());
        out.close();
    }
}