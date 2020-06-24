#include<iostream>
#include<fstream>
#include<cstdlib>

#define INFINITY 999999

using namespace std;




struct adjListNode {
    int nodeIdx;
    int weight;
};


class ArrayList {
    int length;
    int capacity;
    struct adjListNode* array;

    void expand();

public:
    ArrayList();
    ~ArrayList();

    void addNode(struct adjListNode);
    int searchNode(int) const;
    bool deleteNode(int);
    struct adjListNode getNode(int) const;

    int getLength() const;
    bool isEmpty() const;
};

void ArrayList::expand() {
    capacity *= 2;

    struct adjListNode* tempArray = new adjListNode[capacity];

    for(int i=0; i<length; i++) {
        tempArray[i] = array[i];
    }

    delete[] array;
    array = tempArray;

    return ;
}

ArrayList::ArrayList() {
    length = 0;
    capacity = 2;
    array = new adjListNode[capacity];
}

ArrayList::~ArrayList() {
    length = capacity = 0;
    delete[] array;
}

void ArrayList::addNode(struct adjListNode node) {
    if(length == capacity) {
        expand();
    }

    array[length] = node;
    length++;

    return ;
}

int ArrayList::searchNode(int nodeIdx) const {
    for(int i=0; i<length; i++) {
        if(array[i].nodeIdx == nodeIdx) {
            return i;  // returning index in arraylist
        }
    }

    return -1;
}

bool ArrayList::deleteNode(int nodeIdx) {
    int position = searchNode(nodeIdx);

    if(position == -1) {
        return false;
    } else {
        array[position] = array[--length];
        return true;
    }
}

struct adjListNode ArrayList::getNode(int position) const {
    if(position < 0 || position >= length) {
        struct adjListNode errorNode;
        errorNode.nodeIdx = errorNode.weight = -1;

        return errorNode;  // returning error
    }

    return array[position];
}

int ArrayList::getLength() const {
    return length;
}

bool ArrayList::isEmpty() const {
    return (length == 0);
}




class Node {
    int nodeIdx;
    ArrayList adjList;

public:
    Node();
    ~Node();

    void setNodeIdx(int);
    int getNodeIdx() const;

    void setEdge(struct adjListNode);
    struct adjListNode getEdge(int) const;
    int getWeight(int) const;
    void removeEdge(int);

    int getNumberEdge() const;
    bool isEdge(int) const;
};

Node::Node() {
    nodeIdx = -1;
}

Node::~Node() {
    nodeIdx = -1;
}

void Node::setNodeIdx(int nodeIdx) {
    this->nodeIdx = nodeIdx;
    return ;
}

int Node::getNodeIdx() const {
    return nodeIdx;
}

void Node::setEdge(struct adjListNode node) {
    adjList.addNode(node);
    return ;
}

struct adjListNode Node::getEdge(int position) const {
    return adjList.getNode(position);
}

int Node::getWeight(int v) const {
    int idx = adjList.searchNode(v);

    return adjList.getNode(idx).weight;
}

void Node::removeEdge(int v) {
    adjList.deleteNode(v);
}

int Node::getNumberEdge() const {
    return adjList.getLength();
}

bool Node::isEdge(int v) const {
    if(adjList.searchNode(v) == -1) {
        return false;
    } else {
        return true;
    }
}




class Stack {
    int length;
    int size;

    int* array;

    void expand();

public:
    Stack();
    ~Stack();

    void push(int);
    int pop();
    bool isEmpty() const;
};

void Stack::expand() {
    size*=2;

    int* tempArray = new int[size];

    for(int i=0; i<length; i++) {
        tempArray[i] = array[i];
    }

    delete[] array;
    array = tempArray;

    return ;
}

Stack::Stack() {
    length = 0;
    size = 2;

    array = new int[size];
}

Stack::~Stack() {
    delete[] array;
    array = NULL;
}

void Stack::push(int u) {
    if(length == size) {
        expand();
    }

    array[length] = u;
    length++;

    return ;
}

int Stack::pop() {
    if(length == 0) {
        return -1;
    }

    int u = array[length-1];
    length--;

    return u;
}

bool Stack::isEmpty() const {
    return (length == 0);
}




class Queue {
    int contain;
    int capacity;

    int front;
    int rear;
    int* array;

    void expand();

public:
    Queue();
    ~Queue();

    void enqueue(int);
    int dequeue();

    bool isEmpty() const;
    bool isFull() const;
};

void Queue::expand() {
    capacity*=2;

    int* tempArray = new int[capacity];
    int idx = 0;

    for(int i=front; i<contain; i++) {
        tempArray[idx++] = array[i];
    }

    for(int i=0; i<front; i++) {
        tempArray[idx++] = array[i];
    }

    front = 0;
    rear = contain-1;

    delete[] array;
    array = tempArray;

    return ;
}

Queue::Queue() {
    contain = 0;
    capacity = 2;

    front = 0;
    rear = -1;
    array = new int[capacity];
}

Queue::~Queue() {
    delete[] array;
    array = NULL;
}

void Queue::enqueue(int number) {
    if(isFull() == true) {
        expand();
    }

    rear = (rear+1)%capacity;
    array[rear] = number;
    contain++;

    return ;
}

int Queue::dequeue() {
    if(isEmpty() == true) {
        return INFINITY;
    }

    int temp = array[front];
    front = (front+1)%capacity;
    contain--;

    return temp;
}

bool Queue::isEmpty() const {
    return (contain == 0);
}

bool Queue::isFull() const {
    return (contain == capacity);
}




struct Edge {
    int u;
    int v;
    int weight;
};


class PriorityQueue {
    int length;
    int capacity;
    struct Edge* array;

    void expand();
    void siftUp(int);
    void siftDown(int);

public:
    PriorityQueue();
    ~PriorityQueue();

    bool isEmpty() const;

    void add(struct Edge);
    void heapify();
    struct Edge extractMin();
    int contains(int, int) const;
    void decreaseKey(int, int, int);
};

void PriorityQueue::expand() {
    capacity *= 2;

    struct Edge* tempArray = new Edge[capacity];

    for(int i=0; i<length; i++) {
        tempArray[i] = array[i];
    }

    delete[] array;
    array = tempArray;

    return ;
}

void PriorityQueue::siftUp(int index) {
    // O(logn) time is required

    if(index == 0) {
        return ;  // the node is root here
    }

    int parentIdx = (index-1)/2;

    if(array[parentIdx].weight > array[index].weight) {
        /* swapping parent and child */
        struct Edge temp = array[index];
        array[index] = array[parentIdx];
        array[parentIdx] = temp;

        siftUp(parentIdx);  // NOTICE
    }

    return ;
}

void PriorityQueue::siftDown(int index) {
    // O(logn) time is required

    int parentIdx = index;
    int leftIdx = 2*index + 1;
    int rightIdx = 2*index + 2;

    if(leftIdx<length && array[leftIdx].weight<array[parentIdx].weight) {
        parentIdx = leftIdx;
    }

    if(rightIdx<length && array[rightIdx].weight<array[parentIdx].weight) {
        parentIdx = rightIdx;
    }

    if(parentIdx != index) {
        /* swapping parent and child */
        struct Edge temp = array[index];
        array[index] = array[parentIdx];
        array[parentIdx] = temp;

        siftDown(parentIdx);  // NOTICE
    }

    return ;
}

PriorityQueue::PriorityQueue() {
    length = 0;
    capacity = 2;
    array = new Edge[capacity];
}

PriorityQueue::~PriorityQueue() {
    length = capacity = 0;
    delete[] array;
    array = NULL;
}

bool PriorityQueue::isEmpty() const {
    return (length == 0);
}

void PriorityQueue::add(struct Edge node) {
    if(length == capacity) {
        expand();
    }

    array[length] = node;
    length++;

    return ;
}

void PriorityQueue::heapify() {
    // O(n.logn) => O(n) time is required

    for(int i=(length/2 - 1); i>=0; i--) {
        siftDown(i);
    }

    return ;
}

struct Edge PriorityQueue::extractMin() {
    struct Edge temp;

    if(length == 0) {
        temp.u = temp.v = temp.weight = -1;

        return temp;  // returning error
    }

    temp = array[0];

    array[0] = array[--length];
    siftDown(0);

    return temp;
}

int PriorityQueue::contains(int u, int v) const {
    for(int i=0; i<length; i++) {
        if(array[i].u == u && array[i].v == v) {
            return i;
        }
    }

    return -1;
}

void PriorityQueue::decreaseKey(int u, int v, int weight) {
    int index = contains(u, v);

    if(index == -1) {
        return ;  // operation failed
    } else {
        array[index].weight = weight;
        siftUp(index);
    }

    return ;
}




struct SubSet {
    int parent;
    int rank;
};


class DisjointSet {
    int size;
    int length;

    struct SubSet* array;

public:
    DisjointSet();
    ~DisjointSet();

    void setDisjointSet(int);
    void addSubSet(struct SubSet);
    struct SubSet getSubSet(int) const;
    bool isFull() const;

    int findRoot(int);
    void unionSet(int, int);
};

DisjointSet::DisjointSet() {
    size = length = 0;
    array = NULL;
}

DisjointSet::~DisjointSet() {
    size = length = 0;
    delete[] array;
    array = NULL;
}

void DisjointSet::setDisjointSet(int size) {
    this->size = size;
    array = new SubSet[size];

    return ;
}

void DisjointSet::addSubSet(struct SubSet u) {
    if(isFull() == true) {
        return ;  // operation failed
    }

    array[length++] = u;

    return ;
}

struct SubSet DisjointSet::getSubSet(int u) const {
    if(u >= length) {
        struct SubSet temp;
        temp.parent = temp.rank = -1;

        return temp;
    }

    return array[u];
};

bool DisjointSet::isFull() const {
    return (size == length);
}

int DisjointSet::findRoot(int u) {
    if(array[u].parent != u) {
        array[u].parent = findRoot(array[u].parent);
    }

    return array[u].parent;
}

void DisjointSet::unionSet(int u, int v) {
    int uRoot = findRoot(u);
    int vRoot = findRoot(v);

    if(array[uRoot].rank > array[vRoot].rank) {
        array[vRoot].parent = uRoot;
    } else if (array[uRoot].rank < array[vRoot].rank) {
        array[uRoot].parent = vRoot;
    } else {
        array[vRoot].parent = uRoot;
        array[uRoot].rank++;
    }

    return ;
}




class MST {
    int size;
    int length;

    struct Edge* array;
    int weight;

public:
    MST();
    ~MST();

    void setMST(int);

    void addEdge(struct Edge);
    struct Edge getEdge(int) const;

    int getWeight() const;
    bool isFull() const;
};

MST::MST() {
    size = length = weight = 0;
    array = NULL;
}

MST::~MST() {
    size = length = weight = 0;
    delete[] array;
    array = NULL;
}

void MST::setMST(int size) {
    this->size = size;
    array = new Edge[size];

    return ;
}

void MST::addEdge(struct Edge edge) {
    if(isFull() == true) {
        return ;  // operation failed
    }

    array[length++] = edge;
    this->weight += edge.weight;

    return ;
}

struct Edge MST::getEdge(int idx) const {
    if(idx >= length) {
        struct Edge temp;
        temp.u = temp.v = temp.weight = -1;

        return temp;
    }

    return array[idx];
};

int MST::getWeight() const {
    return weight;
}

bool MST::isFull() const {
    return (size == length);
}




class Graph {
    int numberNode;
    int numberEdge;
    bool isDirected;
    bool isNegative;

    Node* array;

    /* For DFS */
    int* color;
    int* parent;

    /* For Minimum Spanning Tree Algorithm */
    MST mst;

public:
    Graph();
    ~Graph();

    void setGraph(int, bool, bool);

    void addEdge(int, int, int);
    void removeEdge(int, int);
    bool isEdge(int, int) const;
    int getInDeg(int) const;
    int getDegree(int) const;
    void printGraph(ofstream&) const;

    /* For DFS Implementation */
    void dfs(int);
    void dfsVisit(int);

    /* For MST algorithm implementation */
    void kruskalMST();
    void printMST(ofstream&) const;
};

Graph::Graph() {
    numberNode = numberEdge = 0;
    isDirected = isNegative = false;

    array = NULL;
    color = parent = NULL;
}

Graph::~Graph() {
    numberNode = numberEdge = 0;
    isDirected = false;

    delete[] array;

    delete[] color;
    delete[] parent;

    array = NULL;

    color = parent = NULL;
}

void Graph::setGraph(int numberNode, bool isDirected, bool isNegative) {
    this->numberNode = numberNode;
    this->isDirected = isDirected;
    this->isNegative = isNegative;

    array = new Node[numberNode];

    color = new int[numberNode];
    parent = new int[numberNode];

    mst.setMST(numberNode-1);

    for(int i=0; i<numberNode; i++) {
        array[i].setNodeIdx(i);
    }

    return ;
}

void Graph::addEdge(int u, int v, int weight) {
    if((u < 0 || u >= numberNode) || (v < 0 || v >= numberNode) || (isNegative == false && weight < 0)) {
        return ;  // operation failed
    }

    struct adjListNode temp;
    temp.nodeIdx = v;
    temp.weight = weight;

    array[u].setEdge(temp);
    numberEdge++;

    if(isDirected == false) {
        temp.nodeIdx = u;
        array[v].setEdge(temp);
    }

    return ;
}

void Graph::removeEdge(int u, int v) {
    if((u < 0 || u >= numberNode) || (v < 0 || v >= numberNode)) {
        return ;  // operation failed
    }

    array[u].removeEdge(v);
    numberEdge--;

    if(isDirected == false) {
        array[v].removeEdge(u);
    }

    return ;
}

bool Graph::isEdge(int u, int v) const {
    if((u < 0 || u >= numberNode) || (v < 0 || v >= numberNode)) {
        return false;  // operation failed
    }

    return array[u].isEdge(v);
}

int Graph::getInDeg(int u) const {
    int inDeg = 0;

    if(isDirected == true) {
        for(int i=0; i<numberNode; i++) {
            if(isEdge(i, u) == true) {
                inDeg++;
            }
        }
    }

    return inDeg;
}

int Graph::getDegree(int u) const {
    int inDeg, outDeg;

    inDeg = getInDeg(u);
    outDeg = array[u].getNumberEdge();

    return inDeg+outDeg;
}

void Graph::printGraph(ofstream& oObj) const {
    struct adjListNode temp;

    cout << "\n" << "Number of node: " << numberNode << "\n" << "Number of edge: " << numberEdge << "\n" << endl;
    oObj << "\n" << "Number of node: " << numberNode << "\n" << "Number of edge: " << numberEdge << "\n" << endl;

    for(int i=0; i<numberNode; i++) {
        cout << i << ": ";
        oObj << i << ": ";

        for(int ii=0; ii<array[i].getNumberEdge(); ii++) {
            temp = array[i].getEdge(ii);
            cout << temp.nodeIdx << "(" << temp.weight << ")" << " ";
            oObj << temp.nodeIdx << "(" << temp.weight << ")" << " ";
        }

        cout << endl;
        oObj << endl;
    }

    return ;
}

void Graph::dfs(int source) {
    for(int i=0; i<numberNode; i++) {
        color[i] = 0; // WHITE
        parent[i] = -1;
    }

    dfsVisit(source);

    return ;
}

void Graph::dfsVisit(int source) {
    int idx;

    color[source] = 1;  // GRAY

    for(int i=0; i<array[source].getNumberEdge(); i++) {
        idx = array[source].getEdge(i).nodeIdx;

        if(color[idx] == 0) {
            parent[idx] = source;

            dfsVisit(idx);
        }
    }

    color[source] = 2;  // BLACK

    // after running DFS on a graph, if found node has color BLACK, then that node is reachable from source

    return ;
}

void Graph::kruskalMST() {
    /* for simple connected edge-weighted undirected graph G */
    DisjointSet disSet;
    struct SubSet temps;

    disSet.setDisjointSet(numberNode);

    for(int i=0; i<numberNode; i++) {
        temps.parent = i;
        temps.rank = 0;

        disSet.addSubSet(temps);
    }

    PriorityQueue pQueue;

    int u;
    struct adjListNode v;
    struct Edge temp;

    for(int i=0; i<numberNode; i++) {
        for(int ii=0; ii<array[i].getNumberEdge(); ii++) {
            u = array[i].getNodeIdx();
            v = array[i].getEdge(ii);

            if(pQueue.contains(u, v.nodeIdx) == -1 && pQueue.contains(v.nodeIdx, u) == -1) {
                temp.u = i;
                temp.v = v.nodeIdx;
                temp.weight = v.weight;

                pQueue.add(temp);
            }
        }
    }

    pQueue.heapify();  // IMPORTANT

    while(mst.isFull() == false) {
        temp = pQueue.extractMin();

        if(disSet.findRoot(temp.u) != disSet.findRoot(temp.v)) {
            disSet.unionSet(temp.u, temp.v);

            mst.addEdge(temp);
        }
    }

    return ;
}

void Graph::printMST(ofstream& oObj) const {
    cout << "\n" << endl;
    oObj << "\n" << endl;


    cout << "Added Edges:" << "\n" << endl;
    oObj << "Added Edges:" << "\n" << endl;

    for(int i=0; i<numberNode-1; i++) {
        cout << "(" << mst.getEdge(i).u << ", " << mst.getEdge(i).v << ")" << endl;
        oObj << "(" << mst.getEdge(i).u << ", " << mst.getEdge(i).v << ")" << endl;
    }

    cout << "\n" << "MST weight: " << mst.getWeight() << endl;
    oObj << "\n" << "MST weight: " << mst.getWeight() << endl;

    return ;
}




int main() {
    ofstream oObj;
    ifstream iObj;

    Graph myGraph;
    int numberNode, numberEdge, u, v, weight;
    bool isDirected, isNegative;

    iObj.open("input.txt");  // change input from here
    oObj.open("output.txt");

    if(iObj.is_open() == true) {
        iObj >> numberNode;
        iObj >> numberEdge;
        iObj >> isDirected;
        iObj >> isNegative;
    } else {
        exit(EXIT_FAILURE);
    }

    myGraph.setGraph(numberNode, isDirected, isNegative);  // directed or undirected

    for(int i=0; i<numberEdge; i++) {
        iObj >> u >> v >> weight;
        myGraph.addEdge(u, v, weight);
    }

    if(oObj.is_open() == true) {
        myGraph.printGraph(oObj);
    }  else {
        exit(EXIT_FAILURE);
    }

    myGraph.kruskalMST();
    myGraph.printMST(oObj);

    iObj.close();
    oObj.close();

    return 0;
}
