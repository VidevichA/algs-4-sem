package Rekkurentnie;

import java.io.IOException;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.File;
import java.io.PrintStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Arrays;
import java.util.Scanner;


public class Task0_1 {
    static int getNumber(int[] dim){
        int n = dim.length - 1;

        int[][] m = new int[n][n];

        for (int i = 0; i < n; i++) {
            m[i][i] = 0;
        }

        for (int l = 1; l < n; l++) {
            for (int i = 0; i < n - l; i++) {
                int j = i + l;
                m[i][j] = Integer.MAX_VALUE;
                for (int k = i;k < j; k++) {
                    m[i][j] = Math.min(m[i][j] , m[i][k] + m[k+1][j] + dim[i]*dim[k+1]*dim[j+1]);
                }
            }
        }

        return m[0][n-1];
    }

    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(new BufferedInputStream(new FileInputStream(new File("input.txt"))));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));


        int s = Integer.parseInt(sc.nextLine());

        int[] sizes = new int[s+1];
        sizes[0] = Integer.parseInt(sc.next());
        int index = 1;
        while(sc.hasNextLine() && index < s+1){
            String a = sc.nextLine();
            if (!a.equals("")){
                sizes[index] = Integer.parseInt(a.split(" ")[1]);
                ++index;
            }
        }

        sc.close();

        out.println(getNumber(sizes));
        out.close();
    }
}