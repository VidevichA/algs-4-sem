package Graphs;

import java.io.*;

public class Task0_1 {
    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        String[] arr = sc.readLine().split(" ");
        int size = Integer.parseInt(arr[0]);
        int lines = Integer.parseInt(arr[1]);

        int[][] matrix = new int[size][size];

        for (int i = 0; i < lines; i++) {
            String[] str = sc.readLine().split(" ");
            matrix[Integer.parseInt(str[0]) - 1][Integer.parseInt(str[1]) - 1] = 1;
            matrix[Integer.parseInt(str[1]) - 1][Integer.parseInt(str[0]) - 1] = 1;
        }
        
        sc.close();

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                out.print(matrix[i][j] + " ");
            }
            out.println();
        }

        out.close();
    }
}