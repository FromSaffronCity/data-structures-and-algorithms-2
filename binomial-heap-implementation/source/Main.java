package myPacakge;

public class Main {
    public static void main(String[] args) {
        BinomialHeap bHeap1 = new BinomialHeap();
        BinomialHeap bHeap2 = new BinomialHeap();

        /* insertion */
        for(int i=5; i<=45; i+=5) {
            bHeap1.insert(new BinomialTree(i));
        }

        for(int i=9; i<=63; i+=9) {
            bHeap2.insert(new BinomialTree(i));
        }

        bHeap1.print();
        bHeap2.print();

        /* union of two binomial heaps */
        bHeap1.union(bHeap2);

        bHeap1.print();

        /* finding and extracting minimum node */
        System.out.println("");
        System.out.println("minNode of Heap-1: " + bHeap1.findMin().getNodeValue());

        BinomialTree minNode = bHeap1.extractMin();

        System.out.println("After extraction, minNode of Heap-1: " + minNode.getNodeValue());
        bHeap1.print();

        System.out.println("");
        System.out.println("again, ");

        BinomialHeap bHeap3 = new BinomialHeap();

        for(int i=0; i<7; i++) {
            if(i == 4) {
                bHeap3.insert(new BinomialTree(-3));
            } else {
                bHeap3.insert(new BinomialTree(i));
            }
        }

        bHeap3.print();
        bHeap3.extractMin();
        bHeap3.print();
    }
}
