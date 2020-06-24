package myPackage;

import java.util.Collections;
import java.util.List;
import java.util.ArrayList;

public class SplayTree {
    private Node root;

    public SplayTree() {
        this.root = null;
    }

    public SplayTree(Node root) {
        this.root = root;
    }

    private Node getRoot() {
        return root;
    }

    private void setRoot(Node root) {
        this.root = root;
    }

    /* auxiliary functionality */
    private void leftRotate(Node rotateAt) {
        Node grandParent = rotateAt.getParent();
        Node child = rotateAt.getRightChild();

        child.setParent(grandParent);
        rotateAt.setParent(child);
        rotateAt.setRightChild(child.getLeftChild());
        child.setLeftChild(rotateAt);

        if(grandParent != null && grandParent.getLeftChild() == rotateAt) {
            grandParent.setLeftChild(child);
        }

        if(grandParent != null && grandParent.getRightChild() == rotateAt) {
            grandParent.setRightChild(child);
        }

        return ;
    }

    private void rightRotate(Node rotateAt) {
        Node grandParent = rotateAt.getParent();
        Node child = rotateAt.getLeftChild();

        child.setParent(grandParent);
        rotateAt.setParent(child);
        rotateAt.setLeftChild(child.getRightChild());
        child.setRightChild(rotateAt);

        if(grandParent != null && grandParent.getLeftChild() == rotateAt) {
            grandParent.setLeftChild(child);
        }

        if(grandParent != null && grandParent.getRightChild() == rotateAt) {
            grandParent.setRightChild(child);
        }

        return ;
    }

    public Node findMax() {
        Node temp = root;

        if(temp == null) {
            return null;  // tree is empty
        }

        while(temp.getRightChild() != null) {
            temp = temp.getRightChild();
        }

        return temp;
    }

    private void printWhitespaces(int count) {
        for(int i=0; i<count; i++) {
            System.out.print(" ");
        }

        return ;
    }

    private int getMaxLevel(Node node) {
        if (node == null) {
            return 0;  // invalid node
        }

        return Math.max(getMaxLevel(node.getLeftChild()), getMaxLevel(node.getRightChild())) + 1;
    }

    private <T> boolean isAllElementsNull(List<T> list) {
        for(Object object: list) {
            if (object != null) {
                return false;
            }
        }

        return true;
    }

    // NOTICE
    private void printNodeInternal(List<Node> list, int level, int maxLevel) {
        if(list.isEmpty() || isAllElementsNull(list)) {
            return ;
        }

        int floor = maxLevel-level;
        int edgeLines = (int) Math.pow(2, (Math.max(floor-1, 0)));
        int firstSpaces = (int) Math.pow(2, (floor))-1;
        int betweenSpaces = (int) Math.pow(2, (floor+1))-1;

        printWhitespaces(firstSpaces);

        List<Node> newList = new ArrayList<>();

        for(Node node: list) {
            if(node != null) {
                System.out.print(node);
                newList.add(node.getLeftChild());
                newList.add(node.getRightChild());
            } else {
                newList.add(null);
                newList.add(null);
                System.out.print(" ");
            }

            printWhitespaces(betweenSpaces);
        }

        System.out.println("");

        for(int i=1; i<=edgeLines; i++) {
            for(int j=0; j<list.size(); j++) {
                printWhitespaces(firstSpaces - i);

                if(list.get(j) == null) {
                    printWhitespaces(edgeLines + edgeLines + i + 1);
                    continue;
                }

                if(list.get(j).getLeftChild() != null) {
                    System.out.print("/");
                } else {
                    printWhitespaces(1);
                }

                printWhitespaces(i + i - 1);

                if(list.get(j).getRightChild() != null) {
                    System.out.print("\\");
                } else {
                    printWhitespaces(1);
                }

                printWhitespaces(edgeLines + edgeLines - i);
            }

            System.out.println("");
        }

        printNodeInternal(newList, level + 1, maxLevel);
        return ;
    }

    /* main functionality */
    public void print() {
        int maxLevel = getMaxLevel(root);

        printNodeInternal(Collections.singletonList(root), 1, maxLevel);
        return ;
    }

    public Node splay(Node node) {
        Node parent = node.getParent();
        Node grandParent = null;

        while(parent != null) {
            grandParent = parent.getParent();

            if(grandParent == null) {
                if(parent.getKeyValue() > node.getKeyValue()) {
                    rightRotate(parent);
                } else {
                    leftRotate(parent);
                }
            } else {
                if(grandParent.getKeyValue() < parent.getKeyValue() && parent.getKeyValue() < node.getKeyValue()) {
                    // case of zig-zig: top-down double left rotations
                    leftRotate(grandParent);
                    leftRotate(parent);
                } else if (grandParent.getKeyValue() < parent.getKeyValue() && parent.getKeyValue() > node.getKeyValue()) {
                    // case of zig-zag: bottom-up right-left rotations
                    rightRotate(parent);
                    leftRotate(grandParent);
                } else if (grandParent.getKeyValue() > parent.getKeyValue() && parent.getKeyValue() > node.getKeyValue()) {
                    // case of zag-zag: top-down double right rotations
                    rightRotate(grandParent);
                    rightRotate(parent);
                } else {
                    // case of zag-zig: bottom-up left-right rotations
                    leftRotate(parent);
                    rightRotate(grandParent);
                }
            }

            parent = node.getParent();
        }

        setRoot(node);
        return node;
    }

    public boolean search(int keyValue) {
        Node temp = root;
        Node parent = null;

        while(temp != null && temp.getKeyValue() != keyValue) {
            parent = temp;

            if(temp.getKeyValue() < keyValue) {
                temp = temp.getRightChild();
            } else {
                temp = temp.getLeftChild();
            }
        }

        if(temp != null) {
            splay(temp);
        } else if(temp == null && parent != null){
            splay(parent);
        } else {
            return false;  // tree is empty
        }

        return (root.getKeyValue() == keyValue);
    }

    public void insert(int keyValue) {
        if(search(keyValue) == true) {
            return ;  // this node already exists
        }

        Node temp = root;
        Node parent = null;

        while(temp != null) {
            parent = temp;

            if(temp.getKeyValue() < keyValue) {
                temp = temp.getRightChild();
            } else {
                temp = temp.getLeftChild();
            }
        }

        temp = new Node(keyValue);
        temp.setParent(parent);

        if(parent != null) {
            if(parent.getKeyValue() < keyValue) {
                parent.setRightChild(temp);
            } else {
                parent.setLeftChild(temp);
            }
        }

        splay(temp);
        return ;
    }

    public void delete(int keyValue) {
        if(search(keyValue) == false) {
            return ;  // this node does not exist in the tree
        }

        Node rightChild = root.getRightChild();
        Node leftChild = root.getLeftChild();

        root.setRightChild(null);
        root.setLeftChild(null);

        if(rightChild != null) {
            rightChild.setParent(null);
        }
        if(leftChild != null) {
            leftChild.setParent(null);
        }

        root = null;

        if(leftChild == null && rightChild == null) {
            // do nothing
        } else if(leftChild != null && rightChild == null) {
            root = leftChild;
        } else if(leftChild == null && rightChild != null) {
            root = rightChild;
        } else {
            SplayTree leftSubTree = new SplayTree(leftChild);
            leftSubTree.splay(leftSubTree.findMax());

            /* Join(L, R) */
            root = leftSubTree.getRoot();
            root.setRightChild(rightChild);
            rightChild.setParent(root);
        }

        return ;
    }
}
