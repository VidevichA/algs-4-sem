package Rekkurentnie;

import java.io.FileNotFoundException;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.File;
import java.io.PrintStream;
import java.util.MissingFormatArgumentException;
import java.util.Scanner;
import java.io.IOException;

public class Task25 {
    static int x, y, z;
    static String A, B;

    static void setParms(Scanner sc){
        x = Integer.parseInt(sc.nextLine()); // удалить символ
        y = Integer.parseInt(sc.nextLine()); // вставить символ
        z = Integer.parseInt(sc.nextLine()); // заменить символ

        A = sc.nextLine();
        B = sc.nextLine();
    }

    static Character[] setArrays(String string){
        Character[] array = new Character[string.length() + 1];
        for (int i = 1; i < string.length() + 1; i++) {
            array[i] = string.charAt(i-1);
        }
        return array;
    }

    static int getResult(Character[] A, Character[] B){
        int[][] matrix = new int[A.length][B.length];
        int delta;

        for (int i = 0; i < A.length; i++) {
            matrix[i][0] = i*x;
        }

        for (int i = 0; i < B.length; i++) {
            matrix[0][i] = i*y;
        }

        for (int i = 1; i < A.length; i++) {
            for (int j = 1; j < B.length; j++) {
                if (A[i] == B[j]){
                    delta = 0;
                }else delta = 1;

                matrix[i][j] = Math.min(
                        Math.min(matrix[i-1][j] + x, matrix[i][j-1] + y),
                        matrix[i-1][j-1] + delta*z
                );
            }
        }

        return matrix[A.length - 1][B.length - 1];
    }

    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(new BufferedInputStream(new FileInputStream(new File("in.txt"))));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("out.txt"))));

        setParms(sc);
        out.println(getResult(setArrays(A), setArrays(B)));
        out.close();
    }
}