package Trees;

import java.io.PrintStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.List;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.stream.Collectors;


public class Task0_1 implements Runnable{

    static ArrayList<Long> list = new ArrayList<>();

    private static class Node{
        Node left;
        Node right;
        long key;

        public Node(long key) {
            this.key = key;
        }
    }

    static class BST{
        private Node root;

        public BST() {
            this.root = null;
        }

        public void insert(long key){
            Node node = new Node(key);

            if (root == null){
                root = node;
                return;
            }

            Node prev = null;
            Node current = root;

            while(current != null){
                if (key < current.key){
                    prev = current;
                    current = current.left;
                }
                else if (key > current.key){
                    prev = current;
                    current = current.right;
                }
            }

            if (key < prev.key){
                prev.left = node;
            }
            if (key > prev.key){
                prev.right = node;
            }
        }

        private void PreOrderTraversal(Node root){
            if (root != null){
                list.add(root.key);
                PreOrderTraversal(root.left);
                PreOrderTraversal(root.right);
            }
        }
    }

    static void fillFromFile(BST tree, BufferedReader reader) throws IOException{
        List<String> lines = reader.lines().distinct().collect(Collectors.toList());
        for(String el : lines){
            tree.insert(Long.parseLong(el));
        }
    }

    static void writeResult(BST tree, PrintStream out){
        tree.PreOrderTraversal(tree.root);
        for (int i = 0; i < list.size(); i++) {
            out.println(list.get(i));
        }
    }

    public static void main(String[] args){

        new Thread(null, new Task0_1(), "", 64*1024).start();


    }

    public void run(){
        try{
            BufferedReader sc = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
            PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("output.txt")));

            BST tree = new BST();
            fillFromFile(tree, sc);
            sc.close();
            writeResult(tree, out);
            out.close();

        }catch (IOException e){
            System.exit(-1000);
        }

    }
}