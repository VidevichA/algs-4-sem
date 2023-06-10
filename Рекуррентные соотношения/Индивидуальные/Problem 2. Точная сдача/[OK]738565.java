package KR1;

import java.io.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;
public class Task2 {
    static int n, m, s;
    static ArrayList<Integer> moneyBuy;
    static int buySum;

    static ArrayList<Integer> moneyCell;
    static int cellSum;

    static void fill(Scanner sc) throws IOException{

        n = sc.nextInt();
        m = sc.nextInt();
        s = sc.nextInt();

        moneyBuy = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int el = sc.nextInt();
            moneyBuy.add(el);
            buySum += el;
        }

        moneyCell = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int el = sc.nextInt();
            moneyCell.add(el);
            cellSum += el;
        }
    }

    static boolean canGetChange(){
        boolean[] temp = new boolean[buySum - s + 1];
        temp[0] = true;
        for (int i = 0; i < moneyCell.size(); i++) {
            for (int j = buySum - s - moneyCell.get(i); j > -1; --j) {
                if (temp[j]){
                    temp[j + moneyCell.get(i)] = true;
                }
            }
        }
        return temp[buySum - s];
    }
    static String getResult(){

        if (buySum == s){
            return "Yes";
        }
        if (buySum > s){
            moneyCell.addAll(moneyBuy);
            moneyCell.sort(Comparator.naturalOrder());
            if (canGetChange()){
                return "Yes";
            }
        }

        return "No";
    }

    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(new File("input.txt"));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("output.txt")));

        fill(sc);
        sc.close();

        out.print(getResult());
        out.close();
    }
}