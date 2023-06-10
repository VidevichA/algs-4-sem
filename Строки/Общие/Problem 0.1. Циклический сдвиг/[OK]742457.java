package Stroki;

import java.io.*;

public class Task0_1 {
    static int[] mas;
    static String s1, s2;
    static int n, temp;

    static void fill(BufferedReader sc) throws IOException{
        n = Integer.parseInt(sc.readLine());
        s1 = sc.readLine();
        s2 = sc.readLine();

        s1 += s1;
        s2 +="#" + s1;

        mas = new int[3*n + 1];
        mas[0] = 0;

        temp = 0;

        RESULT = false;
    }


    static void calculate(){
        for (int i = 1; i < s2.length(); i++) {
            temp = mas[i-1];
            while(temp > 0 && s2.charAt(i) != s2.charAt(temp)){
                temp = mas[temp - 1];
            }
            if (s2.charAt(i) == s2.charAt(temp)){
                mas[i] = temp + 1;
            }else mas[i] = temp;
        }
    }

    static boolean RESULT;

    static void getResult(PrintStream out){
        for (int i = 0; i < mas.length; i++) {
            if (mas[i] == n){
                out.print(i - 2*n);
                RESULT = true;
                break;
            }
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        fill(sc);
        sc.close();
        calculate();
        getResult(out);
        if (!RESULT){
            out.print(-1);
        }
        out.close();
    }
}