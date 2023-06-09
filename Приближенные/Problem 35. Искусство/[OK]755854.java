import java.io.*;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new FileReader("input.txt"));
        String s2 = bufferedReader.readLine();
        StringTokenizer stringTokenizer2 = new StringTokenizer(s2," ");
        int n = Integer.parseInt(stringTokenizer2.nextToken());
        int m = Integer.parseInt(stringTokenizer2.nextToken());
        int gok = 0;
        int m1 = m;
        while (m1 > 0) {
            String s1 = bufferedReader.readLine();
            StringTokenizer stringTokenizer = new StringTokenizer(s1," ");
            int temp1 = Integer.parseInt(stringTokenizer.nextToken());
            int temp2 = Integer.parseInt(stringTokenizer.nextToken());
            int kok = Integer.parseInt(stringTokenizer.nextToken());
            if (temp1 < temp2) {
                if (kok == 1) {
                    gok++;
                }
            } else {
                if (kok == 2) {
                    gok++;
                }
            }
            m1--;
        }
        bufferedReader.close();
        FileWriter fileWriter = new FileWriter(new File("output.txt"));
        if ((int)m/2 <= gok) {
            fileWriter.write(gok + "\n");
            for (int i = 1; i <= n; i++) {
                fileWriter.write(i + " ");
            }
        } else {
            fileWriter.write(m - gok + "\n");
            for (int i = n; i > 0; i--) {
                fileWriter.write(i + " ");
            }
        }
        fileWriter.close();
    }
}