package Rekkurentnie;
import java.util.Formatter;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.PrintStream;

public class Task29{
    static double[] fillRadiuses(Scanner sc, int numberOfDisks){ // Просто функция для заполнения массива
        double[] array = new double[numberOfDisks];
        int index = 0;
        while(index < array.length){
            array[index] = Double.parseDouble(sc.nextLine());
            ++index;
        }
        return array;
    }

    static double getLength(double radius1, double radius2){ // Это расстояние между центрами
        return Math.sqrt(Math.pow(radius1 + radius2, 2) - Math.pow(radius1 - radius2, 2));
    }

    static double[] getCoordinates(double[] radiuses){ // Это для координат
        double[] disksCoordinates = new double[radiuses.length]; // У нас число координат совпадает с числов радиусов

        disksCoordinates[0] = radiuses[0]; // Первая коорд - это первый радиус

        for (int i = 0; i < radiuses.length - 1; i++) { // Проходимся по массиву и заполняем координаты
            double centersDistance = getLength(radiuses[i], radiuses[i+1]); // Вот это для расстояния между
            disksCoordinates[i + 1] = disksCoordinates[i] + centersDistance; // Заполняем послед коорд как прошлую + расст
            for (int j = 0; j < i; j++) { // Цикл нужен для того чтобы проверить правильно ли у нас расчитывались расст
                centersDistance = getLength(radiuses[i+1], radiuses[j]);
                if (disksCoordinates[i+1] < disksCoordinates[j] + centersDistance){
                    disksCoordinates[i+1] = disksCoordinates[j] + centersDistance;
                }
            }
        }

        return disksCoordinates;
    }

    static double getResult(double[] radiuses, double[] disksCoordinates){ //для того чтобы получить максимальную длину коробки
        double leftB = radiuses[0] - disksCoordinates[0];   //Может быть случай когда у нас очень маленький i-ый и очень большой i-ый
        double rigthB = radiuses[0] + disksCoordinates[0];
        for (int i = 0; i < radiuses.length; i++) {
            if (radiuses[i] - disksCoordinates[i] > leftB){
                leftB = radiuses[i] - disksCoordinates[i];
            }
            if (radiuses[i] + disksCoordinates[i] > rigthB){
                rigthB = radiuses[i] + disksCoordinates[i];
            }
        }

        return leftB + rigthB;
    }

    static void print(Formatter formatter, PrintStream out, double result){
        formatter.format("%.5f", result);
        out.println(formatter);
        out.close();
    }

    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(new BufferedInputStream(new FileInputStream(new File("in.txt"))));
        PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream(new File("out.txt"))));

        int numberOfDisks = Integer.parseInt(sc.nextLine());

        if (numberOfDisks <= 0){
            out.println(0);
            out.close();
            System.exit(0);
        }

        double[] radiuses = fillRadiuses(sc, numberOfDisks);
        sc.close();
        double[] disksCoordinates = getCoordinates(radiuses);

        print(new Formatter(), out, getResult(radiuses, disksCoordinates));
    }
}