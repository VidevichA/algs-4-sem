package Graphs;

import java.io.*;

public class Task0_2 implements Runnable{
    public static void main(String[] args) throws IOException{
        new Thread(null, new Task0_2(), "", 1024*1024*64).start();
    }

    @Override
    public void run() {
        try{
            BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
            PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

            int size = Integer.parseInt(sc.readLine());
            int[] list = new int[size];

//            String[] first = sc.readLine().split(" ");
//            list[Integer.parseInt(first[0]) - 1] = 0;
//            list[Integer.parseInt(first[1]) - 1]  = Integer.parseInt(first[0]);

            for (int i = 0; i < size - 1; i++) {
                String[] temp = sc.readLine().split(" ");
                list[Integer.parseInt(temp[1]) - 1]  = Integer.parseInt(temp[0]);
            }

            sc.close();

            for (int i = 0; i < size; i++) {
                out.print(list[i] + " ");
            }

            out.close();
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }
}