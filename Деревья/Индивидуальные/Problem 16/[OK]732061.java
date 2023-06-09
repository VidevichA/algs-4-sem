import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        BinaryTree binaryTree = new BinaryTree();
        Scanner scanner = new Scanner(new File("input.txt"));
        while (scanner.hasNext()) binaryTree.insert(scanner.nextLong());
        binaryTree.deleteRoot();
        binaryTree.preorderTreeWalk();
    }

    static class BinaryTree {
        private Node rootNode;
        private int maxLength = 0;
        long MSL = 0;

        public BinaryTree() {
            rootNode = null;
        }

        public class Node {
            long finalNum;
            long value;
            long semiPathsCount;
            long rootCountForSemiPath;
            long level;
            long leaves;
            Node left;
            long msl;
            Node right;

            public Node(long value) {
                this.value = value;
            }

            public Node() {
            }

            public long getValue() {
                return this.value;
            }

            public void setValue(long value) {
                this.value = value;
            }

            public Node getLeft() {
                return this.left;
            }

            public Node getRight() {
                return this.right;
            }

            public void setLeft(Node node) {
                this.left = node;
            }

            public void setRight(Node node) {
                this.right = node;
            }
        }

        public Node returnRootNode() {
            return this.rootNode;
        }

        public void insert(long x) {
            Node parent = null;
            Node node = rootNode;
            while (node != null) {
                parent = node;
                if (x < node.getValue()) {
                    node = node.left;
                } else if (x > node.getValue()) {
                    node = node.right;
                } else {
                    return;
                }
            }

            Node newNode = new Node(x);

            if (parent == null) {
                rootNode = newNode;
            } else if (x < parent.getValue()) {
                parent.left = newNode;
            } else if (x > parent.getValue()) {
                parent.right = newNode;
            }
        }

        public void deleteRoot() {
            delete(rootNode.getValue());
        }

        public void delete(long value) {
            if (rootNode == null) {
                return;
            }
            Node currentNode = rootNode;
            Node parentNode = rootNode;
            boolean isRight = false;
            while (value != currentNode.getValue()) {
                parentNode = currentNode;
                if (currentNode.getValue() > value) {
                    isRight = false;
                    currentNode = currentNode.getLeft();
                } else {
                    isRight = true;
                    currentNode = currentNode.getRight();
                }
                if (currentNode == null) {
                    return;
                }
            }
            if (currentNode.getLeft() == null && currentNode.getRight() == null) {
                if (currentNode == rootNode)
                    rootNode = null;
                if (isRight)
                    parentNode.setRight(null);
                else
                    parentNode.setLeft(null);
            } else if (currentNode.getLeft() == null) {
                if (currentNode == rootNode) {
                    rootNode = currentNode.getRight();
                } else if (isRight) {
                    parentNode.setRight(currentNode.getRight());
                } else {
                    parentNode.setLeft(currentNode.getRight());
                }
            } else if (currentNode.getRight() == null) {
                if (currentNode == rootNode)
                    rootNode = currentNode.getLeft();
                else if (isRight)
                    parentNode.setRight(currentNode.getLeft());
                else
                    parentNode.setLeft(currentNode.getLeft());
            } else {
                Node parent1Node = currentNode;
                Node newNode = currentNode;
                Node current1Node = currentNode.getRight();
                while (current1Node != null) {
                    parent1Node = newNode;
                    newNode = current1Node;
                    current1Node = current1Node.getLeft();
                }
                if (newNode != currentNode.getRight()) {
                    parent1Node.setLeft(newNode.getRight());
                    newNode.setRight(currentNode.getRight());
                }
                newNode.setLeft(currentNode.getLeft());
                if (currentNode == rootNode)
                    rootNode = newNode;
                else if (isRight)
                    parentNode.setRight(newNode);
                else
                    parentNode.setLeft(newNode);
            }
        }

        public void levelOrganizer() {
            levelOrganizer(rootNode);
        }

        public int count = 0;

        private void levelOrganizer(Node node) {
            if (node != null) {
                levelOrganizer(node.getLeft());
                levelOrganizer(node.getRight());
                if (node.getRight() == null && node.getLeft() == null) {
                    node.level = 0;
                    node.msl = 0;
                    node.leaves = 1;
                } else if (node.getRight() == null) {
                    node.leaves = node.getLeft().leaves;
                    node.level = node.getLeft().level + 1;
                    node.msl = node.getLeft().level + 1;
                } else if (node.getLeft() == null) {
                    node.leaves = node.getRight().leaves;
                    node.level = node.getRight().level + 1;
                    node.msl = node.getRight().level + 1;
                } else if (node.getRight().level > node.getLeft().level) {
                    node.level = node.getRight().level + 1;
                    node.leaves = node.getRight().leaves;
                    node.msl = node.getRight().level + 2 + node.getLeft().level;
                } else if (node.getRight().level < node.getLeft().level) {
                    node.level = node.getLeft().level + 1;
                    node.leaves = node.getLeft().leaves;
                    node.msl = node.getRight().level + 2 + node.getLeft().level;
                } else {
                    node.level = node.getLeft().level + 1;
                    node.leaves = node.getLeft().leaves + node.getRight().leaves;
                    node.msl = node.getRight().level + 2 + node.getLeft().level;
                }
                if (MSL < node.msl) MSL = node.msl;
            }
        }

        private long countMslRootCount(Node node) {
            long mslCount = 0;
            if (node != null) {
                if (node.msl == MSL) {
                    if (node.getRight() == null && node.getLeft() != null) {
                        mslCount = node.getLeft().leaves;
                    } else if (node.getLeft() == null && node.getRight() != null) {
                        mslCount = node.getRight().leaves;
                    } else if (node.getRight() != null && node.getLeft() != null) {
                        mslCount = node.getRight().leaves * node.getLeft().leaves;
                    }
                }
            }
            return mslCount;
        }

        public void semiPathCounterForEachNode() {
            semiPathCounterForEachNode(rootNode);
            if (MSL == 0) rootNode.semiPathsCount = 1;
        }

        private void semiPathCounterForEachNode(Node node) {
            if (node != null) {
                node.rootCountForSemiPath = countMslRootCount(node);
                if (node.getLeft() == null && node.getRight() == null) {
                } else if (node.getLeft() == null && node.getRight() != null) {
                    node.getRight().semiPathsCount = node.rootCountForSemiPath + node.semiPathsCount;
                } else if (node.getRight() == null && node.getLeft() != null) {
                    node.left.semiPathsCount = node.rootCountForSemiPath + node.semiPathsCount;
                } else {
                    if (node.getLeft().level > node.getRight().level) {
                        node.getLeft().semiPathsCount = node.rootCountForSemiPath + node.semiPathsCount;
                        node.getRight().semiPathsCount = node.rootCountForSemiPath;
                    } else if (node.getLeft().level < node.getRight().level) {
                        node.getRight().semiPathsCount = node.rootCountForSemiPath + node.semiPathsCount;
                        node.getLeft().semiPathsCount = node.rootCountForSemiPath;
                    } else {
                        node.getRight().semiPathsCount = node.rootCountForSemiPath + node.getRight().leaves * node.semiPathsCount / node.leaves;
                        node.getLeft().semiPathsCount = node.rootCountForSemiPath + node.getLeft().leaves * node.semiPathsCount / node.leaves;
                    }
                }
                semiPathCounterForEachNode(node.getLeft());
                semiPathCounterForEachNode(node.getRight());
            }
        }

        public void preorderTreeWalk() throws IOException {
            if (rootNode != null) {
                levelOrganizer();
                semiPathCounterForEachNode();
                FileWriter fileWriter = new FileWriter("output.txt");
                preorderTreeWalk(rootNode, fileWriter);
                fileWriter.close();
            }
        }

        private void preorderTreeWalk(Node node, FileWriter fileWriter) throws IOException {
            if (node != null) {
                node.finalNum = node.semiPathsCount + node.rootCountForSemiPath;
                fileWriter.write(node.getValue() + " " + node.finalNum + "\n");
                preorderTreeWalk(node.getLeft(), fileWriter);
                preorderTreeWalk(node.getRight(), fileWriter);
            }
        }
    }
}