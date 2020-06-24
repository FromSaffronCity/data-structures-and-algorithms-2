package myPackage;


public class Node {
    private Node parent;
    private Node leftChild;
    private Node rightChild;

    private int keyValue;

    public Node(int keyValue) {
        this.keyValue = keyValue;
    }

    public int getKeyValue() {
        return keyValue;
    }

    public Node getParent() {
        return parent;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public Node getLeftChild() {
        return leftChild;
    }

    public void setLeftChild(Node leftChild) {
        this.leftChild = leftChild;
    }

    public Node getRightChild() {
        return rightChild;
    }

    public void setRightChild(Node rightChild) {
        this.rightChild = rightChild;
    }

    @Override
    public String toString() {
        return keyValue + "";  // NOTICE
    }
}
