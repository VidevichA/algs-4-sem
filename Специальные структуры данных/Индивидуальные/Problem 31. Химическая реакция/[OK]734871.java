package Structures;

import java.io.*;
import java.util.Stack;

public class Task31 {

    static void fillSizes(BufferedReader sc) throws IOException{
        String[] str = sc.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
    }

    static int[][] fillMatrix(BufferedReader sc) throws IOException{
        int[][] matrix = new int[n][n];
        String[] str;
        for (int i = 0; i < n; i++) {
            str = sc.readLine().split(" ");
            for (int j = 0; j < n; j++) {
                matrix[i][j] = Integer.parseInt(str[j]);
            }
        }
        return matrix;
    }

    static int[] fillElements(BufferedReader sc) throws IOException{
        String[] str = sc.readLine().split(" ");
        int[] elements = new int[m];
        for (int i = 0; i < m; i++) {
            elements[i] = Integer.parseInt(str[i]);
        }
        return elements;
    }

    static void doReactions(int[][] matrix, int[] elements){
        probirka = new Stack<>();

        probirka.push(elements[0]);

        for (int i = 1; i < m; i++) {
            if ( matrix[probirka.peek() - 1][elements[i] - 1] != 0){
                int element = matrix[elements[i] - 1][probirka.pop() - 1];
                while (!probirka.isEmpty() && matrix[probirka.peek() - 1][element - 1] != 0){
                    probirka.push( matrix[element - 1][probirka.pop() - 1] );
                    element = probirka.pop();
                }
                probirka.push( element );
            }
            else{
                probirka.push(elements[i]);
            }
        }
    }

    static void printProbirka(PrintStream out){
        while(!probirka.empty()){
            out.print(probirka.pop());
            if (!probirka.empty()){
                out.print(" ");
            }
        }
    }

    static int n, m;
    static Stack<Integer> probirka;

    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("in.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("out.txt"))));

        fillSizes(sc);
        int[][] matrix = fillMatrix(sc);
        int[] elements = fillElements(sc);
        sc.close();

        doReactions(matrix, elements);

        printProbirka(out);

        out.close();
    }
}