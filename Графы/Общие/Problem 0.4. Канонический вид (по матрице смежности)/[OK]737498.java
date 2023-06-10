package Graphs;

import java.io.*;

public class Task0_4 {
    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        int size = Integer.parseInt(sc.readLine());

        int[][] matrix = new int[size][size];
        for (int i = 0; i < size; i++) {
            String[] str = sc.readLine().split(" ");
            for (int j = 0; j < size; j++) {
                matrix[i][j] = Integer.parseInt(str[j]);
            }
        }

        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < size; j++) {
                if (matrix[j][i] == 1){
                    out.print(j + 1 + " ");
                }else{
                    ++count;
                }
            }
            if (count == size){
                out.print(0 + " ");
            }
        }

        out.close();
    }
}