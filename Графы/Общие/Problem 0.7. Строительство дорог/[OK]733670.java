package Graphs;

import java.io.*;
import java.util.ArrayList;

public class Task0_7 {
    static int[] mas;

    static int repr(int n){
        if (mas[n] < 0){
            return n;
        }
        mas[n] = repr(mas[n]);
        return mas[n];
    }

    static void union(int x, int y){
        x = repr(x);
        y = repr(y);
        if (x != y){
            if (Math.abs(mas[x]) < Math.abs(mas[y])){
                int temp = x;
                x = y;
                y = temp;
            }
        }
        mas[x] = (mas[y] + mas[x]);
        mas[y] = x;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        String[] firstLine = sc.readLine().split(" ");

        int n = Integer.parseInt(firstLine[0]);
        int q = Integer.parseInt(firstLine[1]);

        int[][] paths = new int[2][q+1];

        paths[0][0] = paths[1][0] = Integer.MIN_VALUE;

        for (int i = 0; i < q; i++) {
            String[] line = sc.readLine().split(" ");
            paths[0][i] = Integer.parseInt(line[0]); // begin
            paths[1][i] = Integer.parseInt(line[1]); // end
        }

        sc.close();


        mas = new int[n+1];
        mas[0] = Integer.MIN_VALUE;

        for (int i = 0; i < n + 1; i++) {
            mas[i] = -1;
        }

        int count = n;

        if (q == 0){
            out.println(0);
            out.close();
            System.exit(0);
        }

        for (int i = 0; i < q; i++) {
            if (count == 1){
                out.println(count);
                continue;
            }
            if (mas[paths[0][i]] != -1 && mas[paths[1][i]] != -1 && repr(paths[0][i]) == repr(paths[1][i])){
                out.println(count);
            }else {
                union(paths[0][i], paths[1][i]);
                out.println(--count);
            }
        }

        out.close();
    }
}