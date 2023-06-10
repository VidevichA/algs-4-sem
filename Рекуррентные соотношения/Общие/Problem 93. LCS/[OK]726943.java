package Rekkurentnie;

import java.io.BufferedInputStream;
import java.io.PrintStream;
import java.io.BufferedOutputStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;
import java.util.List;

public class Task93 {
    static ArrayList<Integer> result = new ArrayList<>();
    static ArrayList<Integer> result1 = new ArrayList<>();

    static void fillArray(int[] array, Scanner sc, int n){
        String[] a = sc.nextLine().split(" ");
        for (int i = 0; i < n; i++) {
            array[i + 1] = Integer.parseInt(a[i]);
        }
    }

    static int[][] getMatrix(int[] first, int[] second, int size){
        int[][] matrix = new int[size + 1][size + 1];

        for (int i = 0; i < size + 1; i++) {
            matrix[i][0] = 0;
            matrix[0][i] = 0;
        }

        for (int i = 1; i < size + 1; i++) {
            for (int j = 1; j < size + 1; j++) {
                if (first[i] == second[j]){
                    matrix[i][j] = matrix[i-1][j-1] + 1;
                }
                else{
                    matrix[i][j] = Math.max(matrix[i][j - 1], matrix[i - 1][j]);
                }
            }
        }

        return matrix;
    }

    static void getIndexes(int[][] matrix, int[] first, int[] second, int size){
        int i = size, j = size;

        while (i > -1 && j > -1 && matrix[i][j] != 0){
            if (first[i] == second[j]){
                result.add(i - 1);
                result1.add(j - 1);
                --i;
                --j;
            }else{
                if (matrix[i][j - 1] == matrix[i][j]){
                    --j;
                }
                else{
                    --i;
                }
            }
        }
    }

    static String printResults(List<Integer> list){
        String a ="";
        StringBuilder sb = new StringBuilder(a);
        for (int i = list.size() - 1; i > -1; --i) {
            sb.append(list.get(i)).append(" ");
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        PrintStream out = new PrintStream(new BufferedOutputStream(System.out));

        int n = Integer.parseInt(sc.nextLine());
        int[] first = new int[1001];
        int[] second = new int[1001];

        fillArray(first, sc, n);
        fillArray(second, sc, n);

        int[][] matrix = getMatrix(first, second, n);

        out.println(matrix[n][n]);

        getIndexes(matrix, first, second, n);

        out.println(printResults(result));
        out.println(printResults(result1));


        out.close();
    }
}