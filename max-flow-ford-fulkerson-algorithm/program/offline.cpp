#include<iostream>
#include<fstream>
#include<cstdlib>
#include<conio.h>

#define INFINITY 999999

using namespace std;




struct adjListNode {
    int nodeIdx;
    int weight;
    bool isForward;
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
        errorNode.isForward = false;

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
    void removeEdge(int);

    /* included */
    void setWeight(int, int);
    int getWeight(int) const;
    bool getIsForward(int) const;

    int getNumberEdge() const;
    bool isEdge(int) const;

    friend ostream& operator<<(ostream&, Node&);
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

void Node::removeEdge(int v) {
    adjList.deleteNode(v);
}

void Node::setWeight(int v, int weight) {
    int idx = adjList.searchNode(v);

    struct adjListNode temp = adjList.getNode(idx);
    adjList.deleteNode(v);

    temp.weight = weight;
    adjList.addNode(temp);

    return ;
}

int Node::getWeight(int v) const {
    int idx = adjList.searchNode(v);

    return adjList.getNode(idx).weight;
}

bool Node::getIsForward(int v) const {
    int idx = adjList.searchNode(v);

    return adjList.getNode(idx).isForward;
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




class ResidualGraph {
    int numberNode;
    int numberEdge;
    bool isDirected;
    bool isNegative;

    Node* array;

    /* For BFS and DFS */
    int* color;
    int* parent;

    /* For Ford-Fulkerson Max Flow Algorithm */
    int maxFlow;

public:
    ResidualGraph();
    ~ResidualGraph();

    void setResidualGraph(int, bool, bool);

    void addEdge(int, int, int);
    void removeEdge(int, int);
    bool isEdge(int, int) const;
    int getInDeg(int) const;
    int getOutDeg(int) const;
    void printResidualGraph(ofstream&) const;

    /* For BFS Implementation */
    void bfs(int);

    /* For DFS Implementation */
    void dfs(int);
    void dfsVisit(int);

    /* offline-5 */
    void maxFlowFordFulkerson(int, int);
    void printMaxFlow(ofstream&);
};

ResidualGraph::ResidualGraph() {
    numberNode = numberEdge = maxFlow = 0;
    isDirected = isNegative = false;

    array = NULL;
    color = parent = NULL;
}

ResidualGraph::~ResidualGraph() {
    numberNode = numberEdge = maxFlow = 0;
    isDirected = isNegative = false;

    delete[] array;

    delete[] color;
    delete[] parent;

    array = NULL;

    color = parent = NULL;
}

void ResidualGraph::setResidualGraph(int numberNode, bool isDirected, bool isNegative) {
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

void ResidualGraph::addEdge(int u, int v, int weight) {
    if((u < 0 || u >= numberNode) || (v < 0 || v >= numberNode) || (isNegative == false && weight < 0)) {
        return ;  // operation failed
    }

    struct adjListNode temp;
    temp.nodeIdx = v;
    temp.weight = weight;
    temp.isForward = true;

    array[u].setEdge(temp);  // setting forward edge with residual capacity
    numberEdge++;

    temp.nodeIdx = u;
    temp.weight = 0;
    temp.isForward = false;

    array[v].setEdge(temp);  // setting backward edge with flow

    // this part does not work here as we are working on digraph
    if(isDirected == false) {
        temp.nodeIdx = u;
        array[v].setEdge(temp);
    }

    return ;
}

void ResidualGraph::removeEdge(int u, int v) {
    if((u < 0 || u >= numberNode) || (v < 0 || v >= numberNode)) {
        return ;  // operation failed
    }

    array[u].removeEdge(v);
    numberEdge--;

    array[v].removeEdge(u);


    // this part does not work here as we are working on digraph
    if(isDirected == false) {
        array[v].removeEdge(u);
    }

    return ;
}

bool ResidualGraph::isEdge(int u, int v) const {
    if((u < 0 || u >= numberNode) || (v < 0 || v >= numberNode)) {
        return false;  // operation failed
    }

    return array[u].isEdge(v);
}

int ResidualGraph::getInDeg(int u) const {
    int inDeg = 0;

    if(isDirected == true) {
        for(int i=0; i<numberNode; i++) {
            if(isEdge(i, u) == true && array[i].getIsForward(u) == true) {
                inDeg++;
            }
        }
    }

    return inDeg;
}

int ResidualGraph::getOutDeg(int u) const {
    int outDeg = 0;
    int v;

    for(int i=0; i<array[u].getNumberEdge(); i++) {
        v = array[u].getEdge(i).nodeIdx;

        if(array[u].getIsForward(v) == true) {
            outDeg++;
        }
    }

    return outDeg;
}

void ResidualGraph::printResidualGraph(ofstream& oObj) const {
    struct adjListNode temp;

    cout << "\n" << "Number of node: " << numberNode << "\n" << "Number of edge: " << numberEdge << "\n" << endl;
    oObj << "\n" << "Number of node: " << numberNode << "\n" << "Number of edge: " << numberEdge << "\n" << endl;

    for(int i=0; i<numberNode; i++) {
        cout << i << ": ";
        oObj << i << ": ";

        for(int ii=0; ii<array[i].getNumberEdge(); ii++) {
            temp = array[i].getEdge(ii);

            if(temp.isForward == true) {
                cout << temp.nodeIdx << "(" << temp.weight << ")" << " ";
                oObj << temp.nodeIdx << "(" << temp.weight << ")" << " ";
            }
        }

        cout << endl;
        oObj << endl;
    }

    return ;
}

void ResidualGraph::bfs(int source) {
    Queue myQueue;
    int visited;
    struct adjListNode neighbor;

    for(int i=0; i<numberNode; i++) {
        color[i] = 0;  // WHITE
        parent[i] = -1;
    }

    myQueue.enqueue(source);
    color[source] = 1;  // GRAY

    while(myQueue.isEmpty() == false) {
        visited = myQueue.dequeue();
        color[visited] = 2;  // BLACK

        for(int i=0; i<array[visited].getNumberEdge(); i++) {
            neighbor = array[visited].getEdge(i);

            /* NOTICE - modified */
            if(color[neighbor.nodeIdx] == 0 && neighbor.weight > 0) {
                myQueue.enqueue(neighbor.nodeIdx);
                color[neighbor.nodeIdx] = 1;
                parent[neighbor.nodeIdx] = visited;
            }
        }
    }

    return ;
}

void ResidualGraph::dfs(int source) {
    for(int i=0; i<numberNode; i++) {
        color[i] = 0; // WHITE
        parent[i] = -1;
    }

    dfsVisit(source);

    return ;
}

void ResidualGraph::dfsVisit(int source) {
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

    // after running DFS on a ResidualGraph, if found node has color BLACK, then that node is reachable from source

    return ;
}

void ResidualGraph::maxFlowFordFulkerson(int source, int sink) {
    /* this program runs in O(f.m) time where m = #edge and f = max flow */
    int minWeight, idx, tempWeight;

    if(getInDeg(source) != 0 || getOutDeg(sink) != 0) {
        return ;  // operation failed
    }

    while(true) {
        bfs(source);
        minWeight = INFINITY;

        if(color[sink] == 0) {
            break;
        }

        idx = sink;

        /* NOTICE & IMPORTANT */
        while(true) {
            if(array[parent[idx]].getWeight(idx) < minWeight) {
                minWeight = array[parent[idx]].getWeight(idx);
            }

            if(parent[idx] == source) {
                break;
            } else {
                idx = parent[idx];
            }
        }

        maxFlow += minWeight;
        idx = sink;

        while(true) {
            if(array[parent[idx]].getIsForward(idx) == true) {
                tempWeight = array[parent[idx]].getWeight(idx);
                tempWeight -= minWeight;  // decreasing residual capacity
                array[parent[idx]].setWeight(idx, tempWeight);

                tempWeight = array[idx].getWeight(parent[idx]);
                tempWeight += minWeight;  // increasing flow
                array[idx].setWeight(parent[idx], tempWeight);
            } else {
                tempWeight = array[parent[idx]].getWeight(idx);
                tempWeight -= minWeight;  // decreasing flow
                array[parent[idx]].setWeight(idx, tempWeight);

                tempWeight = array[idx].getWeight(parent[idx]);
                tempWeight += minWeight;  // increasing residual capacity
                array[idx].setWeight(parent[idx], tempWeight);
            }


            if(parent[idx] == source) {
                break;
            } else {
                idx = parent[idx];
            }
        }
    }

    return ;
}

void ResidualGraph::printMaxFlow(ofstream& oObj) {
    struct adjListNode temp;

    cout << "\n\n" << "Maximum Flow: " << maxFlow << "\n\n" << endl;
    oObj << "\n\n" << "Maximum Flow: " << maxFlow << "\n\n" << endl;

    cout << "Flow along each edge:" << "\n" << endl;
    oObj << "Flow along each edge:" << "\n" << endl;

    for(int i=0; i<numberNode; i++) {
        for(int ii=0; ii<array[i].getNumberEdge(); ii++) {
            temp = array[i].getEdge(ii);

            if(temp.isForward == false) {
                cout << "From " << temp.nodeIdx << " to " << array[i] << ": " << temp.weight << endl;
                oObj << "From " << temp.nodeIdx << " to " << array[i] << ": " << temp.weight << endl;
            }
        }
    }

    cout << "\n\n" << "Edges of min-cut: " << "\n" << endl;
    oObj << "\n\n" << "Edges of min-cut: " << "\n" << endl;

    // finding mincut edges
    for(int i=0; i<numberNode; i++) {
        if(color[i] == 2) {
            for(int ii=0; ii<array[i].getNumberEdge(); ii++) {
                temp = array[i].getEdge(ii);

                if(color[temp.nodeIdx] == 0 && temp.isForward == true) {
                    cout << "(" << array[i] << ", " << temp.nodeIdx << ")" << endl;
                    oObj << "(" << array[i] << ", " << temp.nodeIdx << ")" << endl;
                }
            }
        }
    }

    return ;
}




int main() {
    ofstream oObj;
    ifstream iObj;

    ResidualGraph myGraph;
    int numberNode, numberEdge, u, v, weight, source, sink;
    bool isDirected, isNegative;

    iObj.open("myInput.txt");  // change input from here
    oObj.open("myOutput.txt");

    if(iObj.is_open() == true) {
        iObj >> numberNode;
        iObj >> numberEdge;
        iObj >> isDirected;
        iObj >> isNegative;
    } else {
        exit(EXIT_FAILURE);
    }

    myGraph.setResidualGraph(numberNode, isDirected, isNegative);  // directed or undirected

    for(int i=0; i<numberEdge; i++) {
        iObj >> u >> v >> weight;
        myGraph.addEdge(u, v, weight);
    }

    if(oObj.is_open() == true) {
        myGraph.printResidualGraph(oObj);
    }  else {
        exit(EXIT_FAILURE);
    }

    iObj >> source >> sink;

    myGraph.maxFlowFordFulkerson(source, sink);
    myGraph.printMaxFlow(oObj);

    iObj.close();
    oObj.close();

    return 0;
}
