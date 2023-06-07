import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class BinaryTree {
    static ArrayList<Node> elems = new ArrayList<>();
    static ArrayList<Node> ansList = new ArrayList<>();
    static int k;

    class Node {
        long value;
        Node rightChild;
        Node leftChild;
        long wayLength;
        ArrayList<Integer> leftList;
        ArrayList<Integer> rightList;

        public Node(long value) {
            this.value = value;
            rightChild = null;
            leftChild = null;
            wayLength = 0;
            leftList = new ArrayList<>();
            rightList = new ArrayList<>();
        }
    }

    private Node root;

    public BinaryTree() throws IOException {
        root = null;
    }

    public void insertNode(long value1) {
        Node newNode = new Node(value1);
        Node currentNode = root;
        Node parentNode;
        elems.add(newNode);
        if (root == null) {
            root = newNode;
        } else {
            while (true) {
                newNode.wayLength++;
                parentNode = currentNode;
                if (parentNode.value == value1) {
                    return;
                } else if (parentNode.value > value1) {
                    currentNode = parentNode.leftChild;
                    if (currentNode == null) {
                        parentNode.leftChild = newNode;
                        return;
                    }
                } else {
                    currentNode = parentNode.rightChild;
                    if (currentNode == null) {
                        parentNode.rightChild = newNode;
                        return;
                    }
                }
            }
        }
    }

    public void CallRootLeftRight(FileWriter writer) throws IOException {
        RootLeftRight(root, writer);
    }

    public void CallLeftRootRight(int k) {
        LeftRootRight(root, k);
    }

    public void RootLeftRight(Node rlrNode, FileWriter writer) throws IOException {
        if (rlrNode == null) {
            return;
        }
        writer.write(rlrNode.value + "\n");
        RootLeftRight(rlrNode.leftChild, writer);
        RootLeftRight(rlrNode.rightChild, writer);
    }

    public void LeftRootRight(Node lr, int k) {
        if (lr == null) {
            return;
        }
        LeftRootRight(lr.leftChild, k);
        LeftRootRight(lr.rightChild, k);
        if (lr.leftChild == null && lr.rightChild == null) {
            lr.rightList.add(1);
            lr.leftList.add(1);
        } else if (lr.rightChild == null) {
            lr.leftList.add(0);
            if (lr.leftChild.leftList.size() == 1 && lr.leftChild.rightList.size() == 1) {
                lr.leftList.add(1);
            } else {
                if (lr.leftChild.leftList.size() < k - 1)
                    lr.leftList.addAll(lr.leftChild.leftList);
                else {
                    for (int i = 0; i < k - 1; i++) {
                        lr.leftList.add(lr.leftChild.leftList.get(i));
                    }
                }
                for (int i = 0; i < lr.leftChild.rightList.size() && i < k - 1; i++) {
                    if (i + 1 < lr.leftList.size()) {
                        if (lr.leftList.get(i + 1) == 0 && lr.leftChild.rightList.get(i) == 1)
                            lr.leftList.set(i + 1, 1);
                    } else {
                        lr.leftList.add(lr.leftChild.rightList.get(i));
                    }
                }
            }
        } else if (lr.leftChild == null) {
            lr.rightList.add(0);
            if (lr.rightChild.leftList.size() == 1 && lr.rightChild.rightList.size() == 1) {
                lr.rightList.add(1);
            } else {
                if (lr.rightChild.leftList.size() < k - 1)
                    lr.rightList.addAll(lr.rightChild.leftList);
                else {
                    for (int i = 0; i < k - 1; i++) {
                        lr.rightList.add(lr.rightChild.leftList.get(i));
                    }
                }
                for (int i = 0; i < lr.rightChild.rightList.size() && i < k - 1; i++) {
                    if (i + 1 < lr.rightList.size()) {
                        if (lr.rightList.get(i + 1) == 0 && lr.rightChild.rightList.get(i) == 1)
                            lr.rightList.set(i + 1, 1);
                    } else {
                        lr.rightList.add(lr.rightChild.rightList.get(i));
                    }
                }
            }
        } else {
            lr.rightList.add(0);
            if (lr.rightChild.leftList.size() == 1 && lr.rightChild.rightList.size() == 1) {
                lr.rightList.add(1);
            } else {
                if (lr.rightChild.leftList.size() < k - 1)
                    lr.rightList.addAll(lr.rightChild.leftList);
                else {
                    for (int i = 0; i < k - 1; i++) {
                        lr.rightList.add(lr.rightChild.leftList.get(i));
                    }
                }
                for (int i = 0; i < lr.rightChild.rightList.size() && i < k - 1; i++) {
                    if (i + 1 < lr.rightList.size()) {
                        if (lr.rightList.get(i + 1) == 0 && lr.rightChild.rightList.get(i) == 1)
                            lr.rightList.set(i + 1, 1);
                    } else {
                        lr.rightList.add(lr.rightChild.rightList.get(i));
                    }
                }
            }
            lr.leftList.add(0);
            if (lr.leftChild.leftList.size() == 1 && lr.leftChild.rightList.size() == 1) {
                lr.leftList.add(1);
            } else {
                if (lr.leftChild.leftList.size() < k)
                    lr.leftList.addAll(lr.leftChild.leftList);
                else {
                    for (int i = 0; i < k - 1; i++) {
                        lr.leftList.add(lr.leftChild.leftList.get(i));
                    }
                }
                for (int i = 0; i < lr.leftChild.rightList.size() && i < k - 1; i++) {
                    if (i + 1 < lr.leftList.size()) {
                        if (lr.leftList.get(i + 1) == 0 && lr.leftChild.rightList.get(i) == 1)
                            lr.leftList.set(i + 1, 1);
                    } else {
                        lr.leftList.add(lr.leftChild.rightList.get(i));
                    }
                }
            }
        }
    }

    public void DeleteNode(long valueToDelete) {
        if (root == null) {
            System.out.println("Empty tree");
            return;
        }
        Node currentNode = root;
        Node parentNode = root;
        boolean isRight = false;
        while (valueToDelete != currentNode.value) {
            parentNode = currentNode;
            if (currentNode.value > valueToDelete) {
                isRight = false;
                currentNode = currentNode.leftChild;
            } else {
                isRight = true;
                currentNode = currentNode.rightChild;
            }
            if (currentNode == null) {
                System.out.println("No such element");
                return;
            }
        }
        if (currentNode.leftChild == null && currentNode.rightChild == null) {
            if (currentNode == root)
                root = null;
            if (isRight)
                parentNode.rightChild = null;
            else
                parentNode.leftChild = null;
        } else if (currentNode.leftChild == null) {
            if (currentNode == root) {
                root = currentNode.rightChild;
            } else if (isRight) {
                parentNode.rightChild = currentNode.rightChild;
            } else {
                parentNode.leftChild = currentNode.rightChild;
            }
        } else if (currentNode.rightChild == null) {
            if (currentNode == root)
                root = currentNode.leftChild;
            else if (isRight)
                parentNode.rightChild = currentNode.leftChild;
            else
                parentNode.leftChild = currentNode.leftChild;
        } else {
            Node parent1Node = currentNode;
            Node newNode = currentNode;
            Node current1Node = currentNode.leftChild;
            while (current1Node != null) {
                parent1Node = newNode;
                newNode = current1Node;
                current1Node = current1Node.rightChild;
            }
            if (newNode != currentNode.leftChild) {
                parent1Node.rightChild = newNode.leftChild;
                newNode.leftChild = currentNode.leftChild;
            }
            newNode.rightChild = currentNode.rightChild;
            if (currentNode == root)
                root = newNode;
            else if (isRight)
                parentNode.rightChild = newNode;
            else
                parentNode.leftChild = newNode;
        }
    }

    public static void main(String[] args) throws IOException {
        BinaryTree tree = null;
        try {
            tree = new BinaryTree();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        Scanner scanner = null;
        try {
            scanner = new Scanner(new File("in.txt"));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        k = scanner.nextInt();
        while (scanner.hasNext())
            tree.insertNode(scanner.nextInt());
        tree.CallLeftRootRight(k);
        for (int i = 0; i < elems.size(); i++) {
            boolean isWay = false;
            if (elems.get(i).rightChild != null && elems.get(i).leftChild != null)
                for (int j = 1; j < elems.get(i).leftList.size(); j += 1) {
                        if (k-j < elems.get(i).rightList.size() && elems.get(i).leftList.get(j) + elems.get(i).rightList.get(k - j) == 2) {
                            isWay = true;
                            ansList.add(elems.get(i));
                            break;
                        }
                    if (isWay)
                        break;
                }
        }
        long min = Long.MAX_VALUE;
        for (int i = 0; i < ansList.size(); i++) {
            if (ansList.get(i).wayLength < min) min = ansList.get(i).wayLength;
        }
        ArrayList<Node> ans2 = new ArrayList<>();
        for (int i = 0; i < ansList.size(); i++) {
            if (ansList.get(i).wayLength == min) ans2.add(ansList.get(i));
        }
        if (ans2.size() % 2 == 1) {
            ans2.sort(new Comparator<Node>() {
                @Override
                public int compare(Node o1, Node o2) {
                    if (o1.value < o2.value) {
                        return 1;
                    } else return 0;
                }
            });
            tree.DeleteNode(ans2.get(ans2.size() / 2).value);
        }
        try (FileWriter writer = new FileWriter("out.txt")) {
            tree.CallRootLeftRight(writer);
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
}