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

    /* for Dijkstra Implementation*/
    int distance;
    Node* parent;

public:
    Node();
    ~Node();

    void setNodeIdx(int);
    int getNodeIdx() const;
    void setDist(int);
    int getDist() const;
    void setParent(Node*);
    Node* getParent() const;

    void setEdge(struct adjListNode);
    struct adjListNode getEdge(int) const;
    int getWeight(int) const;
    void removeEdge(int);

    int getNumberEdge() const;
    bool isEdge(int) const;

    friend ostream& operator<<(ostream&, Node&);
};

Node::Node() {
    nodeIdx = -1;
    distance = -1;
    parent = NULL;
}

Node::~Node() {
    nodeIdx = -1;
    distance = -1;
    parent = NULL;
}

void Node::setNodeIdx(int nodeIdx) {
    this->nodeIdx = nodeIdx;
    return ;
}

int Node::getNodeIdx() const {
    return nodeIdx;
}

void Node::setDist(int distance) {
    this->distance = distance;
    return ;
}

int Node::getDist() const {
    return distance;
}

void Node::setParent(Node* parent) {
    this->parent = parent;
    return ;
}

Node* Node::getParent() const {
    return parent;
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

ostream& operator<<(ostream& out, Node& node) {
    if(&node != 0) {
        out << node.getNodeIdx();
    } else {
        out << "null";
    }

    return out;
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




struct pqNode {
    int nodeIdx;
    int distance;  // shortest distance from source
};


class PriorityQueue {
    int length;
    int capacity;
    struct pqNode* array;

    void expand();
    void siftUp(int);
    void siftDown(int);

public:
    PriorityQueue();
    ~PriorityQueue();

    bool isEmpty() const;

    void add(struct pqNode);
    void heapify();
    struct pqNode extractMin();
    int contains(int) const;
    void decreaseKey(int, int);
};

void PriorityQueue::expand() {
    capacity *= 2;

    struct pqNode* tempArray = new pqNode[capacity];

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

    if(array[parentIdx].distance > array[index].distance) {
        /* swapping parent and child */
        struct pqNode temp = array[index];
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

    if(leftIdx<length && array[leftIdx].distance<array[parentIdx].distance) {
        parentIdx = leftIdx;
    }

    if(rightIdx<length && array[rightIdx].distance<array[parentIdx].distance) {
        parentIdx = rightIdx;
    }

    if(parentIdx != index) {
        /* swapping parent and child */
        struct pqNode temp = array[index];
        array[index] = array[parentIdx];
        array[parentIdx] = temp;

        siftDown(parentIdx);  // NOTICE
    }

    return ;
}

PriorityQueue::PriorityQueue() {
    length = 0;
    capacity = 2;
    array = new pqNode[capacity];
}

PriorityQueue::~PriorityQueue() {
    length = capacity = 0;
    delete[] array;
    array = NULL;
}

bool PriorityQueue::isEmpty() const {
    return (length == 0);
}

void PriorityQueue::add(struct pqNode node) {
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

struct pqNode PriorityQueue::extractMin() {
    struct pqNode temp;

    if(length == 0) {
        temp.nodeIdx = temp.distance = -1;

        return temp;  // returning error
    }

    temp = array[0];

    array[0] = array[--length];
    siftDown(0);

    return temp;
}

int PriorityQueue::contains(int nodeIdx) const {
    for(int i=0; i<length; i++) {
        if(array[i].nodeIdx == nodeIdx) {
            return i;
        }
    }

    return -1;
}

void PriorityQueue::decreaseKey(int nodeIdx, int distance) {
    int index = contains(nodeIdx);

    if(index == -1) {
        return ;  // operation failed
    } else {
        array[index].distance = distance;
        siftUp(index);
    }

    return ;
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

    /* For Dijkstra Implementation */
    bool dijkstra(int);
    bool bellmanFord1(int);
    bool bellmanFord2(int);
    void printResult(ofstream&) const;

    void floydWarshall(ofstream&);

    /* Online Problem (NOTICE) */
    friend void solution(Graph&);  // online-1
    friend void solution2(ofstream&, Graph&);  // online-2
    friend void solutionFloyd(ofstream&, Graph&);  // problem suggested by Saifullah on Floyd-Warshall algorithm
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

bool Graph::dijkstra(int s) {
    struct adjListNode tempEdge;
    struct pqNode tempNode;
    PriorityQueue pQueue;

    int u, v;

    for(int i=0; i<numberNode; i++) {
        array[i].setDist(INFINITY);
        array[i].setParent(NULL);
    }

    array[s].setDist(0);

    for(int i=0; i<numberNode; i++) {
        tempNode.nodeIdx = i;
        tempNode.distance = array[i].getDist();

        pQueue.add(tempNode);
    }

    pQueue.heapify();

    while(pQueue.isEmpty() == false) {
        tempNode = pQueue.extractMin();
        u = tempNode.nodeIdx;

        /* IMPORTANT */
        for(int i=0; i<array[u].getNumberEdge(); i++) {
            tempEdge = array[u].getEdge(i);
            v = tempEdge.nodeIdx;

            if(array[v].getDist() > array[u].getDist() + tempEdge.weight) {
                array[v].setDist(array[u].getDist() + tempEdge.weight);
                array[v].setParent(&array[u]);
                pQueue.decreaseKey(v, array[v].getDist());
            }
        }
    }

    return true;
}

bool Graph::bellmanFord1(int s) {
    int u, v;

    for(int i=0; i<numberNode; i++) {
        array[i].setDist(INFINITY);
        array[i].setParent(NULL);
    }

    array[s].setDist(0);

    /* First (n-1) iteration */
    for(int i=1; i<numberNode; i++) {
        for(int ii=0; ii<numberNode; ii++) {
            for(int iii=0; iii<array[ii].getNumberEdge(); iii++) {
                u = array[ii].getNodeIdx();
                v = array[ii].getEdge(iii).nodeIdx;

                if(array[v].getDist() > array[u].getDist() + array[ii].getEdge(iii).weight) {
                    array[v].setDist(array[u].getDist() + array[ii].getEdge(iii).weight);
                    array[v].setParent(&array[u]);
                }
            }
        }
    }

    /* checking negative weight cycle */
    int dist[numberNode];

    for(int i=0; i<numberNode; i++) {
        dist[i] = array[i].getDist();
    }

    for(int i=0; i<numberNode; i++) {
        for(int ii=0; ii<array[i].getNumberEdge(); ii++) {
            u = array[i].getNodeIdx();
            v = array[i].getEdge(ii).nodeIdx;

            if(array[v].getDist() > array[u].getDist() + array[i].getEdge(ii).weight) {
                array[v].setDist(array[u].getDist() + array[i].getEdge(ii).weight);
                array[v].setParent(&array[u]);
            }
        }
    }

    for(int i=0; i<numberNode; i++) {
        if(array[i].getDist() != dist[i]) {
            return false;
        }
    }

    return true;
}

bool Graph::bellmanFord2(int s) {
    Queue myQueue;
    bool inQueue[numberNode], flag;
    int u, v, countSenti = 0;

    for(int i=0; i<numberNode; i++) {
        array[i].setDist(INFINITY);
        array[i].setParent(NULL);

        inQueue[i] = false;
    }

    array[s].setDist(0);
    myQueue.enqueue(array[s].getNodeIdx());
    inQueue[s] = true;

    myQueue.enqueue(INFINITY);
    countSenti++;  // whenever sentinel is enqueued, countSenti is incremented by 1

    while(myQueue.isEmpty() == false) {
        u = myQueue.dequeue();

        /* IMPORTANT */
        if(u == INFINITY) {
            if(myQueue.isEmpty() == true) {
                flag = true;
                break;
            } else {
                if(countSenti >= numberNode-1) {
                    flag = false;
                    break;
                } else {
                    myQueue.enqueue(INFINITY);
                    countSenti++;

                    u = myQueue.dequeue();
                }
            }
        }

        inQueue[u] = false;

        for(int i=0; i<array[u].getNumberEdge(); i++) {
            v = array[u].getEdge(i).nodeIdx;

            if(array[v].getDist() > array[u].getDist() + array[u].getEdge(i).weight) {
                array[v].setDist(array[u].getDist() + array[u].getEdge(i).weight);
                array[v].setParent(&array[u]);

                if(inQueue[v] == false) {
                    myQueue.enqueue(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    return flag;
}

void Graph::printResult(ofstream& oObj) const {
    cout << endl;
    oObj << endl;

    for(int i=0; i<numberNode; i++) {
        cout << i << ": distance = " << array[i].getDist() << " & parent = " << *(array[i].getParent()) << endl;
        oObj << i << ": distance = " << array[i].getDist() << " & parent = " << *(array[i].getParent()) << endl;
    }

    return ;
}

void Graph::floydWarshall(ofstream& oObj) {
    int distance[numberNode][numberNode], parent[numberNode][numberNode];  /* space complexity O(V2) */
    adjListNode v;
    bool hasNegativeCycle = false;

    /* setting up the D matrix in O(V2) time */
    for(int i=0; i<numberNode; i++) {
        for(int ii=0; ii<numberNode; ii++) {
            if(i == ii) {
                distance[i][ii] = 0;
                parent[i][ii] = i;
            } else {
                distance[i][ii] = INFINITY;
                parent[i][ii] = -1;
            }
        }
    }

    /* setting up the D0 matrix in O(E) time */
    for(int i=0; i<numberNode; i++) {
        for(int ii=0; ii<array[i].getNumberEdge(); ii++) {
            v = array[i].getEdge(ii);

            distance[i][v.nodeIdx] = v.weight;
            parent[i][v.nodeIdx] = i;
        }
    }

    /* setting up the matrices D1 to Dv in O(V3) time */
    for(int k=0; k<numberNode; k++) {
        for(int i=0; i<numberNode; i++) {
            for(int ii=0; ii<numberNode; ii++) {
                if(distance[i][ii] > distance[i][k] + distance[k][ii]) {
                    distance[i][ii] = distance[i][k] + distance[k][ii];
                    parent[i][ii] = parent[k][ii];
                }
            }
        }
    }

    /* negative cycle detection in O(V) time */
    for(int i=0; i<numberNode; i++) {
        if(distance[i][i] < 0) {
            hasNegativeCycle = true;
        }
    }

    /* printing result in O(V2) time */
    cout << "\n" << "All Pair Shortest Paths:" << "\n" << endl;
    oObj << "\n" << "All Pair Shortest Paths:" << "\n" << endl;

    for(int i=0; i<numberNode; i++) {
        for(int ii=0; ii<numberNode; ii++) {
            cout << distance[i][ii] << "\t";
            oObj << distance[i][ii] << "\t";
        }

        cout << endl;
        oObj << endl;
    }

    cout << "\n" << "Predecessor Matrix:" << "\n" << endl;
    oObj << "\n" << "Predecessor Matrix:" << "\n" << endl;

    for(int i=0; i<numberNode; i++) {
        for(int ii=0; ii<numberNode; ii++) {
            if(parent[i][ii] == -1) {
                cout << "null" << "\t";
                oObj << "null" << "\t";

                continue;
            }

            cout << parent[i][ii] << "\t";
            oObj << parent[i][ii] << "\t";
        }

        cout << endl;
        oObj << endl;
    }

    if(hasNegativeCycle == true) {
        cout << "\n" << "Negative Cycle: Yes" << endl;
        oObj << "\n" << "Negative Cycle: Yes" << endl;
    } else {
        cout << "\n" << "Negative Cycle: No" << endl;
        oObj << "\n" << "Negative Cycle: No" << endl;
    }

    return ;
}

void solution(Graph& myGraph) {
    int source, destination, extra, u, v, weight;
    int distS[myGraph.numberNode], distD[myGraph.numberNode];

    cin >> source >> destination >> extra;  // extra is the number of extra edges

    myGraph.dijkstra(source);  // O((E+V)logV)

    for(int i=0; i<myGraph.numberNode; i++) {
        distS[i] = myGraph.array[i].getDist();  // O(logV)
    }

    myGraph.dijkstra(destination);  // O((E+V)logV)

    for(int i=0; i<myGraph.numberNode; i++) {
        distD[i] = myGraph.array[i].getDist();  // O(logV)
    }

    int minDist = myGraph.array[source].getDist();
    int minIdx = -1;

    /* O(E') */
    for(int i=0; i<extra; i++) {
        cin >> u >> v >> weight;

        myGraph.addEdge(u, v, weight);

        if(minDist > distS[u] + weight + distD[v]) {
            minDist = distS[u] + weight + distD[v];
            minIdx = i;
        }

        if(minDist > distS[v] + weight + distD[u]) {
            minDist = distS[v] + weight + distD[u];
            minIdx = i;
        }

        myGraph.removeEdge(u, v);
    }

    cout << "\n" << minDist << " " << minIdx << endl;  // in total O((E+V)logV + E')

    return ;
}

void solution2(ofstream& oObj, Graph& myGraph) {
    if(myGraph.isDirected == false) {
        return ;  // this program is for digraph
    }

    int s = 0, u, v;
    bool flag;
    Graph spTree;  // for the construction of shortest path tree

    flag = myGraph.bellmanFord1(s);

    if(flag == false) {
        cout << "\n" << "negative cycle detected" << endl;
        oObj << "\n" << "negative cycle detected" << endl;

        return ;  // this graph contains negative cycle
    }

    spTree.setGraph(myGraph.numberNode, myGraph.isDirected, myGraph.isNegative);

    /* constructing the shortest path tree */
    for(int i=0; i<myGraph.numberNode; i++) {
        v = i;

        while(myGraph.array[v].getParent() != NULL) {
            u = myGraph.array[v].getParent() -> getNodeIdx();

            if(spTree.isEdge(u, v) == false) {
                spTree.addEdge(u, v, myGraph.array[u].getWeight(v));
            }

            v = u;
        }
    }

    /* top sort */
    int inDegs[myGraph.numberNode], topOrder[myGraph.numberNode], count = 0;
    Queue myQueue;

    for(int i=0; i<myGraph.numberNode; i++) {
        inDegs[i] = spTree.getInDeg(i);

        if(inDegs[i] == 0) {
            myQueue.enqueue(i);
        }
    }

    while(myQueue.isEmpty() == false) {
        u = myQueue.dequeue();
        topOrder[count] = u;
        count++;

        for(int i=0; i<spTree.array[u].getNumberEdge(); i++) {
            v = spTree.array[u].getEdge(i).nodeIdx;

            inDegs[v]--;

            if(inDegs[v] == 0) {
                myQueue.enqueue(v);
            }
        }
    }

    cout << "\n" << "order of edges:" << "\n" << endl;
    oObj << "\n" << "order of edges:" << "\n" << endl;

    for(int i=0; i<count; i++) {
        u = topOrder[i];

        for(int ii=0; ii<myGraph.array[u].getNumberEdge(); ii++) {
            v = myGraph.array[u].getEdge(ii).nodeIdx;

            cout << u << " " << v << endl;
            oObj << u << " " << v << endl;
        }
    }

    return ;
}

void solutionFloyd(ofstream& oObj, Graph& myGraph) {
    int order[myGraph.numberNode], sum;
    Stack myStack;

    cout << endl;

    for(int i=myGraph.numberNode-1; i>=0; i--) {
        cin >> order[i];
    }

    int distance[myGraph.numberNode][myGraph.numberNode];
    adjListNode u;

    for(int i=0; i<myGraph.numberNode; i++) {
        for(int ii=0; ii<myGraph.numberNode; ii++) {
            if(i == ii) {
                distance[i][ii] = 0;
            } else {
                distance[i][ii] = INFINITY;
            }
        }
    }

    for(int i=0; i<myGraph.numberNode; i++) {
        for(int ii=0; ii<myGraph.array[i].getNumberEdge(); ii++) {
            u = myGraph.array[i].getEdge(ii);

            distance[i][u.nodeIdx] = u.weight;
        }
    }

    for(int k=0; k<myGraph.numberNode; k++) {
        /* O(V2) */
        for(int i=0; i<myGraph.numberNode; i++) {
            for(int ii=0; ii<myGraph.numberNode; ii++) {
                /* IMPORTANT */
                if(distance[order[i]][order[ii]] > distance[order[i]][order[k]] + distance[order[k]][order[ii]]) {
                    distance[order[i]][order[ii]] = distance[order[i]][order[k]] + distance[order[k]][order[ii]];
                }
            }
        }

        sum = 0;

        /* O(V2) */
        for(int i=0; i<=k; i++) {
            for(int ii=0; ii<=k; ii++) {
                sum += distance[order[i]][order[ii]];
            }
        }

        myStack.push(sum);
    }

    cout << endl;
    oObj << endl;

    while(myStack.isEmpty() == false) {
        sum = myStack.pop();

        cout << sum << " ";
        oObj << sum << " ";
    }

    return ;
}




int main() {
    ofstream oObj;
    ifstream iObj;

    Graph myGraph;
    int numberNode, numberEdge, u, v, weight, source;
    bool isDirected, isNegative, flag;

    iObj.open("__input2.txt");  // change input from here
    oObj.open("myOutput.txt");

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

    // myGraph.floydWarshall(oObj);
    // solution2(oObj, myGraph);
    solutionFloyd(oObj, myGraph);

    iObj.close();
    oObj.close();

    return 0;
}
