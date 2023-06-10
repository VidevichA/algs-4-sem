package Rekkurentnie;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.util.IllegalFormatCodePointException;
import java.util.Scanner;

public class Task20_1 {
    static String reverse(String st){
        return  new StringBuilder(st).reverse().toString();
    }

    static int[][] lcs(String string){
        int size = string.length();

        String reversed = reverse(string);

        int[][] matrix = new int[size + 1][size + 1];

        for (int i = 0; i < size + 1; i++) {
            matrix[i][0] = 0;
            matrix[0][i] = 0;
        }

        for (int i = 1; i < size + 1; i++) {
            for (int j = 1; j < size + 1 ; ++j) {
                if (string.charAt(i - 1) == reversed.charAt(j - 1)){
                    matrix[i][j] = matrix[i - 1][j - 1] + 1;
                }
                else matrix[i][j] = Math.max(matrix[i - 1][j], matrix[i][j - 1]);
            }
        }

        return matrix;
    }

    static String remake(int[][] matrix, String string, String reversed){
        StringBuilder result = new StringBuilder();

        int i = string.length(), j = string.length();

        while(i > -1 && j > -1 && matrix[i][j] != 0){
            if (string.charAt(i - 1) == reversed.charAt(j - 1)){
                result.append(string.charAt(i - 1));
                --i;
                --j;
            }
            else{
                if (matrix[i][j] == matrix[i - 1][j]){
                    --i;
                }
                else{
                    --j;
                }
            }
        }

        return result.reverse().toString();
    }

    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(new BufferedInputStream(new FileInputStream(new File("input.txt"))));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        String s = sc.nextLine();
        String reversed = reverse(s);

        int[][] matrix = lcs(s);
        out.println(
                matrix[s.length()][s.length()]
        );
        out.println(
                remake(matrix, s, reversed)
        );
        out.close();
    }
}