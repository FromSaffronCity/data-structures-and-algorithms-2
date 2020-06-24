package myPacakge;

public class BinomialHeap {
    /* min heap property is maintained here */
    private RootList roots;

    public BinomialHeap() {
        roots = new RootList();
    }

    /* main functionality */
    public BinomialTree findMin() {
        /* this works in O(logn) time */
        int min = 999999;
        int idx = -1;

        for(int i=0; i<roots.getMaxBound(); i++) {
            if(roots.getBTNode(i) != null && roots.getBTNode(i).getNodeValue() < min) {
                min = roots.getBTNode(i).getNodeValue();
                idx = i;
            }
        }

        return roots.getBTNode(idx);
    }

    public BinomialTree extractMin() {
        BinomialTree temp = findMin();

        roots.delete(temp.getChildren().getLength());  // NOTICE - deleting the min Node

        BinomialHeap tempHeap = new BinomialHeap();

        for(int i=0; i<temp.getChildren().getLength(); i++) {
            tempHeap.getRoots().insert(temp.getChildren().getBTNode(i), temp.getChildren().getBTNode(i).getChildren().getLength());
        }

        union(tempHeap);

        return temp;
    }

    public void insert(BinomialTree btNode) {
        BinomialHeap tempHeap = new BinomialHeap();
        tempHeap.getRoots().insert(btNode, 0);  // NOTICE

        union(tempHeap);

        return ;
    }


    public void union(BinomialHeap bHeap) {
        /* IMPORTANT - merge function */
        int idx = 0;

        BinomialTree carry = null;
        BinomialTree temp;

        while(true) {
            if(roots.getMaxBound() == 0 && bHeap.getRoots().getMaxBound() == 0) {
                // merging two empty heaps
                return ;
            }

            if(roots.getMaxBound() <= idx && bHeap.getRoots().getMaxBound() <= idx) {
                roots.insert(carry, idx);
                return ;
            }

            if(roots.getMaxBound() <= idx && bHeap.getRoots().getMaxBound() > idx) {
                if(carry == null) {
                    roots.insert(bHeap.getRoots().getBTNode(idx), idx);
                } else if(bHeap.getRoots().getBTNode(idx) == null){
                    roots.insert(carry, idx);
                    carry = null;
                } else {
                    if(carry.getNodeValue() >= bHeap.getRoots().getBTNode(idx).getNodeValue()) {
                        temp = bHeap.getRoots().getBTNode(idx);
                        temp.getChildren().insert(carry);
                    } else {
                        temp = carry;
                        temp.getChildren().insert(bHeap.getRoots().getBTNode(idx));
                    }

                    carry = temp;
                    roots.insert(null, idx);
                }

                idx++;
                continue;
            }

            if(roots.getMaxBound() > idx && bHeap.getRoots().getMaxBound() <= idx) {
                if(carry == null) {
                    roots.insert(roots.getBTNode(idx), idx);
                } else if(roots.getBTNode(idx) == null){
                    roots.insert(carry, idx);
                    carry = null;
                } else {
                    if(carry.getNodeValue() >= roots.getBTNode(idx).getNodeValue()) {
                        temp = roots.getBTNode(idx);
                        temp.getChildren().insert(carry);
                    } else {
                        temp = carry;
                        temp.getChildren().insert(roots.getBTNode(idx));
                    }

                    carry = temp;
                    roots.insert(null, idx);
                }

                idx++;
                continue;
            }

            if(roots.getMaxBound() > idx && bHeap.getRoots().getMaxBound() > idx) {
                if(roots.getBTNode(idx) == null && bHeap.getRoots().getBTNode(idx) == null) {
                    roots.insert(carry, idx);
                    carry = null;
                } else if(roots.getBTNode(idx) != null && bHeap.getRoots().getBTNode(idx) == null) {
                    if(carry == null) {
                        roots.insert(roots.getBTNode(idx), idx);
                    } else {
                        if(carry.getNodeValue() >= roots.getBTNode(idx).getNodeValue()) {
                            temp = roots.getBTNode(idx);
                            temp.getChildren().insert(carry);
                        } else {
                            temp = carry;
                            temp.getChildren().insert(roots.getBTNode(idx));
                        }

                        carry = temp;
                        roots.insert(null, idx);
                    }
                } else if(roots.getBTNode(idx) == null && bHeap.getRoots().getBTNode(idx) != null) {
                    if(carry == null) {
                        roots.insert(bHeap.getRoots().getBTNode(idx), idx);

                    } else {
                        if(carry.getNodeValue() >= bHeap.getRoots().getBTNode(idx).getNodeValue()) {
                            temp = bHeap.getRoots().getBTNode(idx);
                            temp.getChildren().insert(carry);
                        } else {
                            temp = carry;
                            temp.getChildren().insert(bHeap.getRoots().getBTNode(idx));
                        }

                        carry = temp;
                        roots.insert(null, idx);
                    }
                } else {
                    if(bHeap.getRoots().getBTNode(idx).getNodeValue() <= roots.getBTNode(idx).getNodeValue()) {
                        temp = bHeap.getRoots().getBTNode(idx);
                        temp.getChildren().insert(roots.getBTNode(idx));
                    } else {
                        temp = roots.getBTNode(idx);
                        temp.getChildren().insert(bHeap.getRoots().getBTNode(idx));
                    }

                    roots.insert(carry, idx);
                    carry = temp;
                }

                idx++;
            }
        }
    }

    public void print() {
        MyQueue myQueue = new MyQueue();
        QueueNode temp;
        int order, level;

        for(int i=0; i<roots.getMaxBound(); i++) {
            if(roots.getBTNode(i) == null) {
                continue;
            }

            /* BFS part */
            level = 0;
            order = roots.getBTNode(i).getChildren().getLength();
            myQueue.enqueue(new QueueNode(roots.getBTNode(i), level));

            System.out.println("");

            System.out.println("For B" + order + ":");
            System.out.print("Level-" + level + ": ");

            while(myQueue.isEmpty() == false) {
                temp = myQueue.dequeue();

                if(temp.getLevel() == level) {
                    System.out.print(temp.getBTNode().getNodeValue() + " ");
                } else {
                    level = temp.getLevel();

                    System.out.println("");
                    System.out.print("Level-" + level + ": " + temp.getBTNode().getNodeValue() + " ");
                }

                for(int ii=0; ii<temp.getBTNode().getChildren().getLength(); ii++) {
                    myQueue.enqueue(new QueueNode(temp.getBTNode().getChildren().getBTNode(ii), temp.getLevel()+1));
                }
            }

            System.out.println("");
        }

        return ;
    }

    /* auxiliary functionality */
    public RootList getRoots() {
        return roots;
    }
}
