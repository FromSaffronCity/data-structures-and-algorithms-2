package myPacakge;

public class RootList {
    private int maxBound;
    private BinomialTree[] array;

    public RootList() {
        maxBound = 0;
        array = new BinomialTree[maxBound];

        for(int i=0; i<maxBound; i++) {
            array[i] = null;
        }
    }

    private void expand(int maxBound) {
        int prevBound = maxBound;
        this.maxBound = maxBound+1;
        BinomialTree[] tempArray = new BinomialTree[this.maxBound];

        for(int i=0; i<this.maxBound; i++) {
            if(i<prevBound) {
                tempArray[i] = array[i];
            } else {
                tempArray[i] = null;
            }
        }

        array = tempArray;
        return ;
    }

    public void insert(BinomialTree btNode, int index) {
        if(index >= maxBound) {
            expand(index);
        }

        array[index] = btNode;
        return ;
    }

    public void delete(int index) {
        if(array[index] != null) {
            array[index] = null;
        }

        return ;
    }

    public int getMaxBound() {
        return maxBound;
    }

    public BinomialTree getBTNode(int index) {
        if(index >= maxBound) {
            return null;  // unavailable btNode
        }

        return array[index];
    }
}
