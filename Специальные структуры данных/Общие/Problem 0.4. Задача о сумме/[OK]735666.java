package Structures;

import java.io.*;
import java.util.ArrayList;

public class Task0_4 {
    static int n, q;
    static ArrayList<Long> numbers;
    static ArrayList<Long> sums;
    static int k;

    static void fillNumbers(BufferedReader sc) throws IOException {
        numbers = new ArrayList<>(n);
        String[] str = sc.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            numbers.add(Long.parseLong(str[i]));
        }

        k = (int) Math.sqrt(n);
        sums = new ArrayList<>(k);
        for (int i = 0; i < n; i += k) {
            long temp = 0;
            for (int j = i; j < i + k; j++) {
                if (j >= n){
                    temp += 0;
                }
                else {
                    temp += numbers.get(j);
                }
            }
            sums.add(temp);
        }
    }

    static void add(int index, int value){
        numbers.set(index, numbers.get(index) + value);
        sums.set(index/k, sums.get(index/k) + value);
    }

    static int findSum(int beg, int end){
        int jl = beg/k;
        int jr = end/k;

        if (jl == jr){
            return sum(beg, end, numbers);
        }else {
            return sum(beg, (jl + 1)*k, numbers) + sum((jl + 1), jr, sums) + sum(jr*k, end, numbers);
        }
    }

    static int sum(int left, int right, ArrayList<Long> list){
        int sum = 0;
        for (int i = left; i < right; i++) {
            sum += list.get(i);
        }
        return sum;
    }

    static void doActions(BufferedReader sc,PrintStream out) throws IOException {
        for (int i = 0; i < q; i++) {
            String[] str = sc.readLine().split(" ");
            if (str[0].equals("Add")){
                add(Integer.parseInt(str[1]), Integer.parseInt(str[2]));
            }
            else{
                out.println(findSum(Integer.parseInt(str[1]), Integer.parseInt(str[2])));
            }
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        PrintStream out = new PrintStream(new BufferedOutputStream(System.out));

        n = Integer.parseInt(sc.readLine());
        fillNumbers(sc);
        q = Integer.parseInt(sc.readLine());

        doActions(sc, out);

        sc.close();
        out.close();
    }
}