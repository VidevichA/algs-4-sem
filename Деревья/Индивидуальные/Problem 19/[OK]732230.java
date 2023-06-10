package Trees;

import java.io.*;
import java.util.Scanner;

public class Task19 implements Runnable{

    static class Node{
        private Node left;
        private Node right;
        private long key;
        private int height;
        private int msl;

        public Node(long key){
            this.key = key;
            this.left = this.right = null;
            this.height = 0;
            this.msl = 0;
        }
    }

    static class BST{
        private Node root;
        static Node maximumHeightNode = new Node(Long.MIN_VALUE);
        private long biggestMsl;

        public BST(){
            this.root = null;
        }

        public void insert(long val){
            this.root = insertRec(root, val);
        }

        private Node insertRec(Node node, long val){
            if (node == null){
                return new Node(val);
            }
            if (val < node.key){
                node.left = insertRec(node.left, val);
            }
            if (val > node.key){
                node.right = insertRec(node.right, val);
            }
            return node;
        }

        public void doTraversal(PrintStream out, Node node){
            if (node != null){
                out.println(node.key);
                doTraversal(out, node.left);
                doTraversal(out, node.right);
            }
        }

        public void delete(long val){
            this.root =  deleteRec(this.root, val);
        }

        private Node deleteRec(Node node, long val){
            if (node == null){
                return null;
            }
            if (val < node.key){
                node.left = deleteRec(node.left, val);
            }
            else if(val > node.key){
                node.right = deleteRec(node.right, val);
            }
            else{
                if (node.left == null && node.right == null){
                    return null;
                }
                if (node.right == null){
                    return node.left;
                }
                if (node.left == null){
                    return node.right;
                }
                else{
                    node.key = getSmallestValue(node.right);
                    node.right = deleteRec(node.right, node.key);
                }
            }
            return node;
        }

        private Long getSmallestValue(Node root){
            return root.left == null ? root.key : getSmallestValue(root.left);
        }

        public void setMaximumHeightNode(Node node){
            if (node != null){
                setMaximumHeightNode(node.left);
                setMaximumHeightNode(node.right);
                if (node.right == null && node.left == null){
                    node.height = 0;
                    node.msl = 0;
                }
                else if (node.right == null){
                    node.height = node.left.height + 1;
                    node.msl = node.left.height + 1;
                }
                else if (node.left == null){
                    node.height = node.right.height + 1;
                    node.msl = node.right.height + 1;
                }
                if (node.left != null && node.right != null){
                    if (node.right.height > node.left.height){
                        node.height = node.right.height + 1;
                        node.msl = node.right.height + node.left.height + 2;
                    }
                    else if (node.left.height > node.right.height){
                        node.height = node.left.height + 1;
                        node.msl = node.right.height + node.left.height + 2;
                    }
                    else {
                        node.height = node.right.height + 1;
                        node.msl = 2*node.right.height + 2;
                    }
                }

                if (node.msl >= biggestMsl){
                    biggestMsl = node.msl;
                    if (node.height >= maximumHeightNode.height){
                        maximumHeightNode = node;
                    }
                }
            }
        }

        public void setMax(Node node){
            if (node != null){
                if (node.msl >= biggestMsl){
                    biggestMsl = node.msl;
                    if (node.height >= maximumHeightNode.height){
                        maximumHeightNode = node;
                    }
                }
                setMax(node.left);
                setMax(node.right);
            }
        }

    }

    static void printTree(BST bst, PrintStream out){
        bst.doTraversal(out, bst.root);
    }

    static void fillFromFile(Scanner reader, BST bst) throws IOException{
        while (reader.hasNextLine()) {
            bst.insert(Long.parseLong(reader.nextLine()));
        }
    }

    public static void main(String[] args){
        new Thread(null, new Task19(), "", 64*1024*1024).start();
    }

    @Override
    public void run() {
        try {
            Scanner reader = new Scanner(new InputStreamReader(new FileInputStream("in.txt")));
            PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("out.txt")));

            BST tree = new BST();
            fillFromFile(reader, tree);
            reader.close();

            tree.setMaximumHeightNode(tree.root);
            tree.setMax(tree.root);

            tree.delete(BST.maximumHeightNode.key);

            printTree(tree, out);
            out.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}