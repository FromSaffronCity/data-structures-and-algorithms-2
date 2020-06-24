package myPacakge;

public class QueueNode {
    private BinomialTree btNode;
    private int level;

    public QueueNode(BinomialTree btNode, int level) {
        this.btNode = btNode;
        this.level = level;
    }

    public BinomialTree getBTNode() {
        return btNode;
    }

    public int getLevel() {
        return level;
    }
}
