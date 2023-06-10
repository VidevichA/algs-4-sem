package Graphs;

import java.io.*;
public class Task8 {

    static int N;
    static int[][] matrix;
    static int[] vershiniGroup;

    static boolean RESULT;
    static int group = 1;

    static void fill(BufferedReader sc) throws IOException{
        N = Integer.parseInt(sc.readLine());
        matrix = new int[N][N];
        vershiniGroup = new int[N];
        RESULT = true;

        for (int i = 0; i < N; i++) {
            String[] arr = sc.readLine().split(" ");
            for (int j = 0; j < N; j++) {
                matrix[i][j] = Integer.parseInt(arr[j]);
            }
        }
    }

    static void DFS(int v){
        vershiniGroup[v] = group;
        for (int i = 0; i < N; i++) {
            if (matrix[v][i] == 1 && vershiniGroup[i] == 0){
                if (group == 1){
                    group = 2;
                }
                else if (group == 2){
                    group = 1;
                }
                DFS(i);
            }
            if (matrix[v][i] == 1 && vershiniGroup[i] != 0){
                if (vershiniGroup[i] == group){
                    RESULT = false;
                    break;
                }
            }
        }
        if (group == 1){
            group = 2;
        }
        else if (group == 2){
            group = 1;
        }
    }

    static void getRes(){
        for (int i = 0; i < N; i++) {
            if (vershiniGroup[i] == 0){
                DFS(i);
            }
        }
    }

    static void printRes(PrintStream out){
        if (RESULT){
            out.println("Yes");
            for (int i = 0; i < N; i++) {
                if (vershiniGroup[i] == 1){
                    out.print((i+1) + " ");
                }
            }
        }else out.print("No");
    }
    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.in")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.out"))));

        fill(sc);
        sc.close();
        getRes();

//        out.println(N);
//        out.println();
//        for (int i = 0; i < N; i++) {
//            for (int j = 0; j < N; j++) {
//                out.print(matrix[i][j] + " ");
//            }
//            out.println();
//        }
//        out.println();

        printRes(out);
        out.close();
    }
}