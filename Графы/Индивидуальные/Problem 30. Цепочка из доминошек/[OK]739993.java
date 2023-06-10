package Graphs;

import java.io.*;

public class Task30 {
    static int[][] matrix = new int[7][7];
    static boolean[] visited = new boolean[7];
    static boolean[] hasDots = new boolean[7];
    static int[] numberOfSuchDominoski = new int[7];
    static int N;


    static void fill(BufferedReader sc) throws IOException{
        N = Integer.parseInt(sc.readLine());
        RESULT = true;

        for (int i = 0; i < N; i++) {
            String[] str = sc.readLine().split(" ");
            matrix[Integer.parseInt(str[0])][Integer.parseInt(str[1])] = 1;
            matrix[Integer.parseInt(str[1])][Integer.parseInt(str[0])] = 1;
            hasDots[Integer.parseInt(str[0])] = true;
            ++numberOfSuchDominoski[Integer.parseInt(str[0])];
            hasDots[Integer.parseInt(str[1])] = true;
            ++numberOfSuchDominoski[Integer.parseInt(str[1])];
        }

        for (int i = 0; i < 7; i++) {
            visited[i] = false;
        }
    }

    static void DFS(int v){
        visited[v] = true;
        for (int i = 0; i < 7; i++) {
            if (matrix[v][i] == 1 && !visited[i]){
                DFS(i);
            }
        }
    }


    static boolean RESULT;

    static void getResult(){
        for (int i = 0; i < 7; i++) {
            if (!visited[i] && hasDots[i]){
                DFS(i);
                break;
            }
        }

        for (int i = 0; i < 7; i++) {
            if (!visited[i] && hasDots[i]){
                RESULT = false;
                break;
            }
        }
    }

    static void printResult(PrintStream out){
        if (RESULT){
            out.print("Yes");
        }
        else out.print("No");
    }

    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("output.txt")));

        fill(sc);
        sc.close();


        for (int i = 0; i < 7; i++) {
            if (numberOfSuchDominoski[i] % 2 != 0){
                RESULT = false;
                printResult(out);
                out.close();
                System.exit(0);
                break;
            }
        }

        getResult();
        printResult(out);
        out.close();
    }
}