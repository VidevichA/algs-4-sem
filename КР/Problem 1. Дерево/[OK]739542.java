package KR3;

import java.io.*;

public class Task1 {

    static int N;
    static int[][] matrix;

    static int rebra;
    static boolean RESULT;
    static BufferedReader sc;
    static PrintStream out;

    static boolean[] visited;

    static void DFS(int v){
        visited[v] = true;
        for (int i = 0; i < N; i++) {
            if (matrix[v][i] == 1 && !visited[i]){
                DFS(i);
            }
        }
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

    static void printResult(){
        if (RESULT){
            out.print("Yes");
        }else out.print("No");
    }
    static void fill(BufferedReader sc) throws IOException{
        N = Integer.parseInt(sc.readLine());

        rebra = 0;
        RESULT = true;
        matrix = new int[N][N];
        visited = new boolean[N];

        for (int i = 0; i < N; i++) {
            String[] str = sc.readLine().split(" ");
            for (int j = 0; j < N; j++) {
                matrix[i][j] = Integer.parseInt(str[j]);
                if (matrix[i][j] == 1){
                    ++rebra;
                }
            }
        }
    }
    public static void main(String[] args) throws IOException {
        sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        fill(sc);
        sc.close();

//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; j++) {
//                out.print(matrix[i][j] + " ");
//            }
//            out.println();
//        }
//        out.println();
//        out.print(N);
//        out.println();

        if (rebra/2 != N-1){
            out.print("No");
        }else {
            getResult();
            printResult();
        }

        out.close();
    }
}