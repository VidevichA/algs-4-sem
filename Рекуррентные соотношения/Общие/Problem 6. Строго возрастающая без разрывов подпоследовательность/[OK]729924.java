package Rekkurentnie;

import java.io.*;
import java.util.Scanner;

public class Task6 implements Runnable{
    static void getLength(int[] array, PrintStream out, int n){
        int[] f = new int[n + 1];

        int L = 0;

        for (int i = 0; i < array.length; i++) {
            int begin = 1;
            int end = L;
            while(begin <= end){
                int mid = (int)Math.ceil((double) (begin+end)/2);
                if (array[f[mid]] < array[i]){
                    begin = mid + 1;
                }
                else end = mid - 1;
            }
            if (begin > L){
                L = begin;
            }
            f[begin] = i;
        }

        out.println(L);
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new Thread(null, new Task6(), "", 64*1024).start();
    }

    @Override
    public void run() {
        try{
            BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
            PrintStream out = new PrintStream(new FileOutputStream(new File("output.txt")));

            int n = Integer.parseInt(sc.readLine());

            int[] array = new int[n];
            String[] numbers = sc.readLine().split(" ");
            for (int i = 0; i < n; i++) {
                array[i] = Integer.parseInt(numbers[i]);
            }

            sc.close();
            getLength(array, out, n);
        }catch (IOException e){
            System.exit(-1000);
        }
    }
}