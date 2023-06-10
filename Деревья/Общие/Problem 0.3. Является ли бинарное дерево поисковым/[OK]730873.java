package Trees;

import java.io.PrintStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Task0_3 implements Runnable{
    static void fillArrays(Long[] values, Long[] mins, Long[] maxs, BufferedReader sc, int size) throws IOException{
        values[0] = Long.parseLong(sc.readLine());
        mins[0] = Long.MIN_VALUE;
        maxs[0] = Long.MAX_VALUE;

        for (int i = 1; i < size; i++) {
            String[] line = sc.readLine().split(" ");
            values[i] = Long.parseLong(line[0]);
            fillBorders(values, mins, maxs, i, line[2], Integer.parseInt(line[1]));
        }
    }

    static void fillBorders(Long[] values, Long[] mins, Long[] maxs, int i, String direction, int parentLine){
        if (direction.equals("L")){
            maxs[i] = values[parentLine - 1];
            mins[i] = mins[parentLine - 1];
        }
        if (direction.equals("R")){
            maxs[i] = maxs[parentLine - 1];
            mins[i] = values[parentLine - 1];
        }
    }

    static String isBST(Long[] values, Long[] mins, Long[] maxs){
        for (int i = 0; i < values.length; i++) {
            if (!( (values[i] < maxs[i] && values[i] > mins[i]) || (values[i] >= mins[i] && values[i] < maxs[i]))){
                return "NO";
            }
        }

        return "YES";
    }

    public static void main(String[] args) throws IOException{
        new Thread(null, new Task0_3(), "", 64*1024*1024).start();
    }

    @Override
    public void run() {
        try{
            BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("bst.in")));
            PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("bst.out")));

            int size = Integer.parseInt(sc.readLine());

            Long[] values = new Long[size];
            Long[] mins = new Long[size];
            Long[] maxs = new Long[size];

            fillArrays(values, mins, maxs, sc, size);
            out.println(isBST(values, mins, maxs));
            out.close();
        }
        catch (IOException e){
            System.exit(-1000);
        }
    }
}