package myPacakge;

import java.lang.String;

public class BinomialTree {
    private int nodeValue;
    private ChildList children;

    public BinomialTree(int nodeValue) {
        this.nodeValue = nodeValue;
        children = new ChildList();
    }

    public int getNodeValue() {
        return nodeValue;
    }

    public ChildList getChildren() {
        return children;
    }
}
