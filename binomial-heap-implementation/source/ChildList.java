package myPacakge;

public class ChildList {
    private int length;
    private int capacity;

    private BinomialTree[] array;

    public ChildList() {
        capacity = 2;
        array = new BinomialTree[capacity];
    }

    private void expand() {
        capacity *= 2;
        BinomialTree[] tempArray = new BinomialTree[capacity];

        for(int i=0; i<length; i++) {
            tempArray[i] = array[i];
        }

        array = tempArray;
        return ;
    }

    public void insert(BinomialTree btNode) {
        if(length == capacity) {
            expand();
        }

        array[length++] = btNode;
        return ;
    }

    public void delete(int index) {
        if(index >= length) {
            return ;  // deletion failed
        }

        array[index] = array[--length];
        return ;
    }


    public int getLength() {
        return length;  // returns the order of the binomial tree
    }

    public BinomialTree getBTNode(int index) {
        if(index >= length) {
            return null;
        }

        return array[index];
    }
}
