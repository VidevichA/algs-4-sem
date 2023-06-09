import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static boolean[][] matrix;
    public static Rectangle[] cards;
    public static int n;
    public static Rectangle[] letters;
    public static boolean[] used;
    public static int[] met;
    public static int count;

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File("input.in"));
        FileWriter fileWriter = new FileWriter(new File("output.out"));
        n = scanner.nextInt();
        met = new int[n];
        used = new boolean[n];
        cards = new Rectangle[n];
        letters = new Rectangle[n];
        matrix = new boolean[n][n];
        count = 0;

        for (int i = 0; i < n; i++) {
            letters[i] = new Rectangle(scanner.nextLong(), scanner.nextLong());
        }
        for (int i = 0; i < n; i++) {
            cards[i] = new Rectangle(scanner.nextLong(), scanner.nextLong());
        }

        for (int indexCard = 0; indexCard < n; indexCard++) {
            met[indexCard] = -1;
            for (int indexLetters = 0; indexLetters < n; indexLetters++) {
                isSuitable(indexCard, indexLetters);
            }
        }

        kunAlgo();

        if (count == n) {
            fileWriter.write("YES");
        } else {
            fileWriter.write("NO" + "\n" + count);
        }
        fileWriter.close();
    }

    public static class Rectangle {
        long x, y;

        Rectangle(long x, long y) {
            this.x = x;
            this.y = y;
        }

        long min() {
            return Math.min(this.x, this.y);
        }

        long max() {
            return Math.max(this.x, this.y);
        }
    }

    public static void isSuitable(int indexCard, int indexLetters) {
        double A = cards[indexCard].max();
        double B = cards[indexCard].min();
        double a = letters[indexLetters].max();
        double b = letters[indexLetters].min();
        double sqrt = Math.sqrt(A * A + B * B);

        if (a <= A && b <= B) {
            matrix[indexCard][indexLetters] = true;
            return;
        }

        if ((Math.sqrt(a * a + b * b) > sqrt || (A * B < a * b))) {
            matrix[indexCard][indexLetters] = false;
            return;
        }

        double diagonal = a * a + b * b;
        matrix[indexCard][indexLetters] = (A * B - Math.sqrt((diagonal - B * B) * (diagonal - A * A)) >= a * b * 2);
    }

    static void  kunAlgo() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                used[j] = false;
            }
            if (kunAlgoRec(i)) {
                count++;
            }
        }
    }

    static boolean kunAlgoRec(int v) {
        if (used[v]){
            return false;
        }
        used[v] = true;
        for (int i = 0; i < n; ++i) {
            if (matrix[v][i] && (met[i] == -1 || kunAlgoRec(met[i]))) {
                met[i] = v;
                return true;
            }

        }
        return false;
    }
}