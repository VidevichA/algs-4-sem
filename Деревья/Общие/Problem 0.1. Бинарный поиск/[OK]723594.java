package Trees;

import java.io.BufferedInputStream;
import java.util.ArrayList;
import java.util.Scanner;

public class Task0_1Binary {
    static int getL(ArrayList<Integer> numbers,int number){
        int right = numbers.size(), left = 0;
        while(left < right){
            int mid = (left + right)/2;

            if (number <= numbers.get(mid)){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }
        return left;
    }
    static int getR(ArrayList<Integer> numbers,int number){
        int right = numbers.size(), left = 0;
        while(left < right){
            int mid = (left + right)/2;

            if (number < numbers.get(mid)){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }
        return left;
    }
    static int getExist(ArrayList<Integer> numbers,int number){
        int right = numbers.size(), left = 0;
        while(left < right){
            int mid = (left + right)/2;
            if (numbers.get(mid) == number){
                return 1;
            }
            if (number < numbers.get(mid)){
                right = mid;
            }
            else{
                left = mid + 1;
            }
        }
        return 0;
    }

    static void fill(ArrayList<Integer> list, String string){
        for (String num : string.split(" ")){
            list.add(Integer.parseInt(num));
        }
    }

    public static void main(String[] args) throws NumberFormatException{
        Scanner sc = new Scanner(new BufferedInputStream(System.in));

        String N = sc.nextLine();

        if (Integer.parseInt(N) != 0){

            int n = Integer.parseInt(N);
            ArrayList<Integer> numbers = new ArrayList<>(n);
            fill(numbers, sc.nextLine());

            int k = Integer.parseInt(sc.nextLine());

            if (k == 0){
                String smth = sc.nextLine();
                System.out.print("");
                System.exit(0);
            }
            else{
                ArrayList<Integer> search = new ArrayList<>(k);
                fill(search, sc.nextLine());

                for (int searchNumber : search) {
                    System.out.print(getExist(numbers, searchNumber) + " " + getL(numbers, searchNumber) + " " + getR(numbers, searchNumber) + "\n");
                }
            }
        }
        else {
            String smth1 = sc.nextLine();
            ArrayList<Integer> numbers = new ArrayList<>(0);

            int k = Integer.parseInt(sc.nextLine());
            if (k == 0){
                String smth = sc.nextLine();
                System.out.print("");
                System.exit(0);
            }
            else{
                ArrayList<Integer> search = new ArrayList<>(k);
                fill(search, sc.nextLine());

                for (int searchNumber : search) {
                    System.out.print(0 + " " + 0 + " " + 0 + "\n");
                }
            }
        }

    }
}