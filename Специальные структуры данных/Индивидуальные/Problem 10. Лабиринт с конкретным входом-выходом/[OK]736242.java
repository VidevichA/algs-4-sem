import java.io.*;
import java.util.Stack;


public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("in.txt")));
        String line = reader.readLine();
        String[] lines = line.split(" ");
        n = Integer.parseInt(lines[0]);
        m = Integer.parseInt(lines[1]);
        maze = new int[n][m];
        for (int i = 0; i < n; i++) {
            line = reader.readLine();
            lines = line.split("");
            for (int j = 0; j < m; j++) {
                maze[i][j] = Integer.parseInt(lines[j]);
            }
        }
        int ways = 0;
        for (int k = 0; k < m; k++) {
            if (maze[0][k] == 0) {
                if(makeWay(new Cell(0, k), 2)){
                    ways++;
                } else {
                    ways = 0;
                    k = m;
                }
            } else if (maze[0][k] == 2) {
                ways = 0;
                k = m;
            }
        }

        File file = new File("out.txt");
        PrintWriter fileWriter = new PrintWriter(file);
        if (ways == 0) {
            fileWriter.write("Impossible");
        } else {
            fileWriter.write("Possible");
        }
        fileWriter.flush();
        fileWriter.close();
    }

    public static class Pair {
        public Cell first;
        public int second;
        Pair(Cell first, int second){
            this.first = first;
            this.second = second;
        }
    }
    public static class Cell {
        int posX;
        int posY;

        Cell(int posX, int posY) {
            if ((posX < 0) || (posY < 0) || (posX >= n) || (posY >= m)) {
                this.posX = -1;
                this.posY = -1;
            } else {
                this.posX = posX;
                this.posY = posY;
            }

        }
    }

    public static int n, m;
    public static int[][] maze;
    public static final int fromLeft = 0;
    public static final int fromDown = 1;
    public static final int fromRight = 2;
    public static final int fromUp = 3;
    public static Cell left;
    public static Cell down;
    public static Cell right;
    public static Cell upper;
    public static Cell current;
    public static Stack<Pair> stepStack;
    public static Pair pair;

    public static boolean makeWay(Cell startPoint, int way) {
        stepStack = new Stack<>();
        stepStack.push(new Pair(startPoint, fromUp));
        while (!stepStack.empty()) {
            pair = stepStack.peek();
            current = pair.first;
            maze[current.posX][current.posY] = way;
            if (current.posX == n - 1) {
                stepStack.clear();
                return true;
            }
            left = new Cell(current.posX, current.posY - 1);
            down = new Cell(current.posX + 1, current.posY);
            right = new Cell(current.posX, current.posY + 1);
            upper = new Cell(current.posX - 1, current.posY);
            if (pair.second == fromUp){
                if (left.posY != -1 && left.posX != -1 && maze[left.posX][left.posY] == 0) {
                    stepStack.push(new Pair(left, fromRight));
                }
                else if (down.posX != -1 && down.posY != -1 && maze[down.posX][down.posY] == 0) {
                    stepStack.push(new Pair(down, fromUp));
                }
                else if (right.posY != -1 && right.posX != -1 && maze[right.posX][right.posY] == 0) {
                    stepStack.push(new Pair(right, fromLeft));
                }
                else {
                    maze[current.posX][current.posY] = 1;
                    stepStack.pop();
                }
            } else if (pair.second == fromLeft) {
                if (down.posX != -1 && down.posY != -1 && maze[down.posX][down.posY] == 0) {
                    stepStack.push(new Pair(down, fromUp));
                }
                else if (right.posY != -1 && right.posX != -1 && maze[right.posX][right.posY] == 0) {
                    stepStack.push(new Pair(right, fromLeft));
                }
                else if (upper.posX != -1 && upper.posY != -1 && maze[upper.posX][upper.posY] == 0) {
                    stepStack.push(new Pair(upper, fromDown));
                }
                else {
                    maze[current.posX][current.posY] = 1;
                    stepStack.pop();
                }
            } else if (pair.second == fromDown) {
                if ((right.posY != -1 && right.posX != -1 && maze[right.posX][right.posY] == 0)) {
                    stepStack.push(new Pair(right, fromLeft));
                }
                else if (upper.posX != -1 && upper.posY != -1 && maze[upper.posX][upper.posY] == 0) {
                    stepStack.push(new Pair(upper, fromDown));
                }
                else if (left.posY != -1 && left.posX != -1 && maze[left.posX][left.posY] == 0) {
                    stepStack.push(new Pair(left, fromRight));
                }
                else {
                    maze[current.posX][current.posY] = 1;
                    stepStack.pop();
                }
            } else  if (pair.second == fromRight) {
                if (upper.posX != -1 && upper.posY != -1 && maze[upper.posX][upper.posY] == 0) {
                    stepStack.push(new Pair(upper, fromDown));
                }
                else if (left.posY != -1 && left.posX != -1 && maze[left.posX][left.posY] == 0) {
                    stepStack.push(new Pair(left, fromRight));
                }
                else if (down.posX != -1 && down.posY != -1 && maze[down.posX][down.posY] == 0) {
                    stepStack.push(new Pair(down, fromUp));
                }
                else {
                    maze[current.posX][current.posY] = 1;
                    stepStack.pop();
                }
            }
        }
        return false;
    }
}