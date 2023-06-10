package Graphs;

import java.io.*;
import java.util.ArrayList;

public class Task0_3 {
    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        String[] arr = sc.readLine().split(" ");
        int size = Integer.parseInt(arr[0]);
        int lines = Integer.parseInt(arr[1]);

        ArrayList<ArrayList<Integer>> matrix = new ArrayList<>(size);

        for (int i = 0; i < size; i++) {
            ArrayList<Integer> list = new ArrayList<>();
            list.add(0);
            matrix.add(list);
        }

        for (int i = 0; i < lines; i++) {
            String[] str = sc.readLine().split(" ");
            int parent = Integer.parseInt(str[0]);
            int child = Integer.parseInt(str[1]);

            ArrayList<Integer> number = matrix.get(parent - 1);
            number.set(0, number.get(0) + 1);
            number.add(child);

            ArrayList<Integer> reverse = matrix.get(child - 1);
            reverse.set(0, reverse.get(0) + 1);
            reverse.add(parent);
        }



        for (int i = 0; i < size; i++) {
            ArrayList<Integer> list = matrix.get(i);
            for (int j = 0; j < list.size(); j++) {
                out.print(list.get(j) + " ");
            }
            out.println();
        }

        out.close();
    }
}