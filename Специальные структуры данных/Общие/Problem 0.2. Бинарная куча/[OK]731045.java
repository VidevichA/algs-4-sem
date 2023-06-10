ackage Structures;

import java.io.PrintStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Task0_2 {

    static void fillArray(BufferedReader sc, int size, Long[] array) throws IOException{
        array[0] = Long.MIN_VALUE;
        String[] values = sc.readLine().split(" ");
        for (int i = 1; i <= size; i++) {
            array[i] = Long.parseLong(values[i - 1]);
        }
        sc.close();
    }

    static String ifHeap(Long[] array, int size){

        for (int i = 1; i <= size/2; i++) {
            if ( 2*i <= size && array[i] > array[2*i]){
                return "NO";
            }
            if ( 2*i + 1 <= size && array[i] > array[2*i + 1]){
                return "NO";
            }
        }

        return "YES";
    }

    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("output.txt")));

        int size = Integer.parseInt(sc.readLine());
        Long[] array = new Long[size + 1];
        fillArray(sc, size, array);

        out.println(ifHeap(array, size));
        out.close();
    }
}