package myPacakge;

public class MyQueue {
    private int contain;
    private int capacity;
    private int front;
    private int rear;

    private QueueNode[] array;

    public MyQueue() {
        capacity = 2;
        rear = -1;
        array = new QueueNode[capacity];
    }

    private void expand() {
        capacity *= 2;
        QueueNode[] tempArray = new QueueNode[capacity];

        int idx = 0;

        for(int i=front; i<contain; i++) {
            tempArray[idx++] = array[i];
        }

        for(int i=0; i<front; i++) {
            tempArray[idx++] = array[i];
        }

        front = 0;
        rear = contain - 1;

        array = tempArray;
        return ;
    }

    public void enqueue(QueueNode qNode) {
        if(isFull() == true) {
            expand();
        }

        rear = (rear+1)%capacity;
        array[rear] = qNode;
        contain++;

        return ;
    }

    public QueueNode dequeue() {
        if(isEmpty() == true) {
            return null;
        }

        QueueNode temp = array[front];
        front = (front+1)%capacity;
        contain--;

        return temp;
    }

    public boolean isEmpty() {
        return (contain == 0);
    }

    public boolean isFull() {
        return (contain == capacity);
    }
}
