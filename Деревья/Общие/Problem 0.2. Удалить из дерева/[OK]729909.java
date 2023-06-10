package Trees;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Task0_2 implements Runnable{
    static List<Long> keys = new ArrayList<>();
    static Long keyToDelete;

    private static class Node{
        private Node left, rigth;
        private long key;

        public Node(long key){
            this.key = key;
        }
    }

    static class BST{
        private Node root;

        public BST(){
            this.root = null;
        }

        public void insert(long key){
            this.root = insertRec(root, key);
        }

        private Node insertRec(Node root, long key){
            if (root == null){
                return new Node(key);
            }
            if (key > root.key){
                root.rigth = insertRec(root.rigth, key);
            }
            if (key < root.key){
                root.left = insertRec(root.left, key);
            }
            return root;
        }

        public void deleteKey(Long key){
            this.root = deleteRec(root, key);
        }

        private Node deleteRec(Node current, Long key){
            if (current == null){
                return null;
            }
            if (key < current.key){
                current.left = deleteRec(current.left, key);
                return current;
            }
            if (key == current.key){
                if (current.left == null && current.rigth == null){
                    return null;
                }
                if (current.rigth == null){
                    return current.left;
                }
                if (current.left == null){
                    return current.rigth;
                }
                else{
                    current.key = getSmallestValue(current.rigth);
                    current.rigth = deleteRec(current.rigth, key);
                    return current;
                }
            }
            current.rigth = deleteRec(current.rigth, key);
            return current;
        }

        private Long getSmallestValue(Node root){
            return root.left == null ? root.key : getSmallestValue(root.left);
        }

        public void PreOrderTraversal(Node root){
            if (root != null){
                keys.add(root.key);
                PreOrderTraversal(root.left);
                PreOrderTraversal(root.rigth);
            }
        }

    }

    static void fillFromFile(BufferedReader reader, BST tree) throws IOException{
        List<String> lines = reader.lines().filter(line -> !line.equals("")).collect(Collectors.toList());
        keyToDelete = Long.parseLong(lines.get(0));
        for (int i = 1; i < lines.size(); i++) {
            tree.insert(Long.parseLong(lines.get(i)));
        }
    }

    static void doTraversal(PrintStream writer, BST tree) throws IOException{
        tree.PreOrderTraversal(tree.root);
        keys = deleteSimilar();
        for (int i = 0; i < keys.size(); i++){
            writer.println(keys.get(i));
        }
    }

    static List<Long> deleteSimilar(){
        return keys.stream().distinct().collect(Collectors.toList());
    }

    public static void main(String[] args) throws IOException{
        new Thread(null, new Task0_2(), "", 64*1024*1024).start();
    }

    @Override
    public void run() {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
            PrintStream writer = new PrintStream(new BufferedOutputStream(new FileOutputStream("output.txt")));

            BST tree = new BST();
            fillFromFile(reader,tree);
            reader.close();
            tree.deleteKey(keyToDelete);
            doTraversal(writer, tree);

            writer.close();
        }catch (IOException e){
            System.exit(-1000);
        }
    }
}