package Structures;

import java.io.*;
public class Task0_3 implements Runnable{
    public static void main(String[] args) throws IOException{
        new Thread(null, new Task0_3(), "", 64*1024*1024).start();
    }
    @Override
    public void run() {
        try{
            BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
            PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

            long num = Long.parseLong(sc.readLine());

            int i = 0;
            while (num > 0){
                if (num%2 == 1){
                    out.println(i);
                }
                i++;
                num /= 2;
            }

            out.close();}
        catch (IOException e){
            e.printStackTrace();
        }
    }
}