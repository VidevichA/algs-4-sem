package approximation;

import java.io.*;
import java.util.*;

public class Task_1 implements Runnable {
    static int n, m;

    static class Part {
        private long income;
        private long processing;
        private long outcome;

        private int number;

        public Part(long income, long processing, long outcome, int partNumber) {
            this.income = income;
            this.processing = processing;
            this.outcome = outcome;
            this.number = partNumber;
        }

        public long getTime(){
            return income + processing + outcome;
        }
    }

    static class Stanok{
        private int number;
        private long time;

        private long finishTime;

        public Stanok(int number) {
            this.number = number;
            this.finishTime = 0;
            this.time = 0;
        }
    }

    static ArrayList<Part> parts;

    static PriorityQueue<Stanok> stanki;

    static ArrayList<ArrayList<Integer>> result;
    static long resultTime;

    static void fill(BufferedReader sc, PrintStream out) throws IOException {
        String[] parms = sc.readLine().split(" ");
        n = Integer.parseInt(parms[0]);
        m = Integer.parseInt(parms[1]);

        parts = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            String[] str = sc.readLine().split(" ");
            parts.add(new Part(Long.parseLong(str[0]), Long.parseLong(str[1]), Long.parseLong(str[2]), i));
        }

        resultTime = 0;

        if (m == 0){
            out.println(0);
            for (int i = 1; i <= n; i++) {
                out.println(i + " " + 0);
            }
            out.close();
            System.exit(0);
        }

        if (n == 0){
            out.println(0);
            out.close();
            System.exit(0);
        }

        stanki = new PriorityQueue<>(
                ((o1, o2) -> Long.compare(o1.finishTime, o2.finishTime))
        );
        for (int i = 1; i <= m; i++) {
            stanki.add(new Stanok(i));
        }

        result = new ArrayList<>();
    }

    static void getResult() {
        parts.sort(new Comparator<Part>() {
            @Override
            public int compare(Part o1, Part o2) {
                return (int) (o1.getTime() - o2.getTime());
            }
        });

        for (Part part : parts){
            Stanok current = stanki.remove();

            current.time = Math.max(current.time + part.processing, part.income + part.processing);
            current.finishTime = Math.max(current.finishTime, current.time + part.outcome);

            ArrayList<Integer> temp = new ArrayList<>();
            temp.add(part.number);
            temp.add(current.number);
            result.add(temp);

            stanki.offer(current);
        }

        for (Stanok stanok: stanki){
            if (stanok.finishTime > resultTime){
                resultTime = stanok.finishTime;
            }
        }
    }

    static void printRes(PrintStream out) {
        out.println(resultTime);

        for (ArrayList<Integer> list : result) {
            out.println(list.get(0) + " " + list.get(1));
        }
    }

    public static void main(String[] args) throws IOException {
        new Thread(null, new Task_1(), "", 64 * 1024 * 1024).start();
    }

    @Override
    public void run() {
        try {
            BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
            PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("output.txt"))));

            fill(sc, out);
            getResult();
            printRes(out);

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}