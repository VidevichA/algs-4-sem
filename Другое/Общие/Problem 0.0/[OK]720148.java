package Rekkurentnie;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;


public class Task0_0 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new File("in.txt"));
        Set<Long> numbers = new HashSet<>();
        while(sc.hasNextLine())
            numbers.add(Long.parseLong(sc.nextLine()));
        FileWriter writer = new FileWriter("out.txt");
        writer.write(String.valueOf(numbers.stream().mapToLong(Long::longValue).sum()));
        writer.flush();
    }
}