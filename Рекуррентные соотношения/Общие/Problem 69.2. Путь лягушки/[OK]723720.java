package Rekkurentnie;

import java.util.*;
import java.util.stream.Collectors;

public class Task69_2 {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        ArrayList<Integer> mosquitoes = new ArrayList<>(n);

        for(String el : sc.nextLine().split(" ")){
            mosquitoes.add(Integer.parseInt(el));
        }

        ArrayList<Integer> indexes = new ArrayList<>(n);

        if (n != 1){
            mosquitoes.set(1, -1);
        }

        for (int i = 2; i < n; ++i) {
            if (i == 2){
                mosquitoes.set(i, mosquitoes.get(i) + mosquitoes.get(0));
            }else{
                mosquitoes.set(i, Math.max(mosquitoes.get(i-2), mosquitoes.get(i - 3)) + mosquitoes.get(i));
            }
        }

        indexes.add(n - 1);

        if (n > 4){
            for (int i = n - 1; i > 3;) {
                if (mosquitoes.get(i - 3) > mosquitoes.get(i - 2)){
                    indexes.add(i - 3);
                    i -= 3;
                }
                else{
                    indexes.add(i - 2);
                    i -= 2;
                }
            }
        }

        indexes.add(0);

        if (n == 1){
            indexes.clear();
            indexes.add(0);
        }
        if (n == 2){
            mosquitoes.set(n - 1, -1);
            indexes.clear();
        }

        System.out.println(mosquitoes.get(n - 1));
        for (int i = indexes.size() - 1; i > -1; --i){
            System.out.print(indexes.get(i) + 1 + " ");
        }
    }
}