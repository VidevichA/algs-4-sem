package KR3;

import java.io.*;

public class Task9 {
    static int N;
    static int[][] matrix;

    static boolean[] visited;

    static void DFS(int v){
        visited[v] = true;
        for (int i = 0; i < N; i++) {
            if (matrix[v][i] == 1 && !visited[i]){
                DFS(i);
            }
        }
    }

    static boolean RESULT;

    static void printRes(PrintStream out){
        if (RESULT){
            out.print("YES");
        }else out.print("NO");
    }

    static void getResult(){
        DFS(0);
        for (int i = 0; i < N; i++) {
            if (!visited[i]){
                RESULT = false;
                break;
            }
        }
    }

    static void fill(BufferedReader sc) throws IOException{
        N = Integer.parseInt(sc.readLine());

        visited = new boolean[N];
        RESULT = true;

        matrix = new int[N][N];
        for (int i = 0; i < N; i++) {
            String[] str = sc.readLine().split(" ");
            for (int j = 0; j < N; j++) {
                matrix[i][j] = Integer.parseInt(str[j]);
            }
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.in")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.out"))));

        fill(sc);
        sc.close();

        getResult();
        printRes(out);

//        out.println();
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; j++) {
//                out.print(matrix[i][j] + " ");
//            }
//            out.println();
//        }
//        out.println();
//        out.print(N);

        out.close();

    }
}