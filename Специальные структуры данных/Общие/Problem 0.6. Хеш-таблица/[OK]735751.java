package Structures;

import java.io.*;

public class Task0_6 {
    static int m, c, n;

    static int func(int x, int i) {
        return ((x % m) + (c * i)) % m;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

        String[] str = sc.readLine().split(" ");
        m = Integer.parseInt(str[0]);
        c = Integer.parseInt(str[1]);
        n = Integer.parseInt(str[2]);

        int[] cells = new int[m];
        for (int i = 0; i < m; i++) {
            cells[i] = -1;
        }

        int i;
        int number = 0;
        for (int k = 0; k < n; k++) {
            number = Integer.parseInt(sc.readLine());
            i = 0;
            for (int j = 0; j < m; j++) {
                if (cells[func(number, i)] == -1 || cells[func(number, i)] == number){
                    cells[func(number, i)] = number;
                    break;
                }
                i++;
            }
        }

        sc.close();

        for (int z = 0; z < m; z++) {
            out.print(cells[z] + " ");
        }

        out.close();
    }
}