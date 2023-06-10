package Graphs;

import java.io.*;

public class Task0_9 {
    static int N;
    static int[][] matrix;
    static int[] order;
    static int index;
    static boolean[] visited;

    static void DFS(int v){
        visited[v] = true;
        order[v] = index;
        ++index;
        for (int i = 0; i < N; i++) {
            if (matrix[v][i] == 1 && !visited[i]){
                DFS(i);
            }
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("output.txt")));

        N = Integer.parseInt(sc.readLine());
        matrix = new int[N][N];
        order = new int[N];
        visited = new boolean[N];
        index = 0;
        for (int i = 0; i < N; i++) {
            String[] arr = sc.readLine().split(" ");
            for (int j = 0; j < N; j++) {
                matrix[i][j] = Integer.parseInt(arr[j]);
            }
        }
        sc.close();

        for (int i = 0; i < N; i++) {
            if (!visited[i]){
                DFS(i);
            }
        }

        for (int i = 0; i < N; i++) {
            out.print((order[i] + 1) + " ");
        }
        out.close();
    }
}