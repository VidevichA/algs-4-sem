package Structures;

import java.io.*;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Task14 {
    static int n, m;
    static int[][] squares;
    static boolean[][] visitedSquares;

    static int k;
    static int x1, y1;
    static int x2, y2;

    static void fillSizes(BufferedReader sc) throws IOException{
        String[] str = sc.readLine().split(" ");
        n = Integer.parseInt(str[0]);
        m = Integer.parseInt(str[1]);
    }

    static void fillSquares(BufferedReader sc) throws IOException{
        squares = new int[n][m];
        visitedSquares = new boolean[n][m];

        for (int i = 0; i < n; i++) {
            String[] str = sc.readLine().split(" ");
            for (int j = 0; j < m; j++) {
                squares[i][j] = Integer.parseInt(str[j]);
                visitedSquares[i][j] = false;
            }
        }
    }

    static void fillOther(BufferedReader sc) throws IOException{
        k = Integer.parseInt(sc.readLine());

        String[] coords = sc.readLine().split(" ");
        x1 = Integer.parseInt(coords[0]) - 1;
        y1 = Integer.parseInt(coords[1]) - 1;
        x2 = Integer.parseInt(coords[2]) - 1;
        y2 = Integer.parseInt(coords[3]) - 1;
    }

    static class Pair{
        private int x,  y,  pathLength;

        public Pair(int x, int y, int pathLength) {
            this.x = x;
            this.y = y;
            this.pathLength = pathLength;
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public int getCount() {
            return pathLength;
        }
    }

    static Pair RESULT_PAIR;

    static void getRes(){
        Queue<Pair> queue = new LinkedList<>();
        queue.add(new Pair(x1,y1,0));
        visitedSquares[x1][y1] = true;

        while(!queue.isEmpty()){
            Pair point = queue.remove();
            if (point.getX() > 0){
                if (Math.abs( squares[point.getX()-1][point.getY()] - squares[point.getX()][point.getY()] ) <= k && !visitedSquares[point.getX() - 1][point.getY()]){
                    if (point.getX()-1 == x2 && point.getY() == y2){
                        RESULT_PAIR = new Pair(point.getX()-1, point.getY(), point.pathLength + 1);
                        break;
                    }
                    visitedSquares[point.getX()-1][point.getY()] = true;
                    queue.add(new Pair(point.getX()-1, point.getY(), point.pathLength + 1));
                }
            }
            if (point.getX() < n-1){
                if (Math.abs( squares[point.getX()+1][point.getY()] - squares[point.getX()][point.getY()] ) <= k && !visitedSquares[point.getX()+1][point.getY()]){
                    if (point.getX()+1 == x2 && point.getY() == y2){
                        RESULT_PAIR = new Pair(point.getX()+1, point.getY(), point.pathLength + 1);
                        break;
                    }
                    visitedSquares[point.getX()+1][point.getY()] = true;
                    queue.add(new Pair(point.getX()+1, point.getY(), point.pathLength + 1));
                }
            }
            if (point.getY() > 0){
                if (Math.abs( squares[point.getX()][point.getY() - 1] - squares[point.getX()][point.getY()] ) <= k && !visitedSquares[point.getX()][point.getY()-1]){
                    if (point.getX() == x2 && point.getY() - 1 == y2){
                        RESULT_PAIR = new Pair(point.getX(),point.getY() - 1, point.pathLength + 1);
                        break;
                    }
                    visitedSquares[point.getX()][point.getY() - 1] = true;
                    queue.add(new Pair(point.getX(),point.getY() - 1, point.pathLength + 1));
                }
            }
            if (point.getY() < m-1){
                if (Math.abs( squares[point.getX()][point.getY() + 1] - squares[point.getX()][point.getY()] ) <= k && !visitedSquares[point.getX()][point.getY() + 1]){
                    if (point.getX() == x2 && point.getY() + 1 == y2){
                        RESULT_PAIR = new Pair(point.getX(), point.getY() + 1, point.pathLength + 1);
                        break;
                    }
                    visitedSquares[point.getX()][point.getY() + 1] = true;
                    queue.add(new Pair(point.getX(), point.getY() + 1, point.pathLength + 1));
                }
            }
        }
    }

    static void printRes(PrintStream out){
        if (RESULT_PAIR != null){
            out.println("Yes");
            out.print(RESULT_PAIR.getCount());
        }
        else{
            out.print("No");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("in.txt")));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("out.txt"))));

        fillSizes(sc);
        fillSquares(sc);
        fillOther(sc);

        sc.close();

        getRes();
        printRes(out);

        out.close();
    }
}