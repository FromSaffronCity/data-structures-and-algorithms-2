#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>

#define INVALID_INDEX -1
#define INFINITY -999999

using namespace std;


class ArrayList {
    int size;
    int contains;

    int* array;

    void expand();

public:
    ArrayList();
    ~ArrayList();

    int search(int) const;
    void insert(int);
    void remove(int);
    int getInt(int) const;

    bool isEmpty() const;
    int getContains() const;
};

void ArrayList::expand() {
    size *= 2;
    int* tempArray = new int[size];

    for(int i=0; i<contains; i++) {
        tempArray[i] = array[i];
    }

    delete[] array;
    array = tempArray;

    return ;
}

ArrayList::ArrayList() {
    size = 2;
    contains = 0;
    array = new int[size];
}

ArrayList::~ArrayList() {
    size = contains = 0;
    delete[] array;
}

int ArrayList::search(int n) const {
    for(int i=0; i<contains; i++) {
        if(array[i] == n) {
            return i;  // returning valid position
        }
    }

    return INVALID_INDEX;  // returning invalid position
}

void ArrayList::insert(int n) {
    if(contains == size) {
        expand();
    }

    array[contains++] = n;

    return ;
}

void ArrayList::remove(int n) {
    if(isEmpty() == true) {
        return ;  // deletion failed
    }

    int idx = search(n);

    if(idx == INVALID_INDEX) {
        return ;  // deletion failed
    } else {
        array[idx] = array[--contains];
    }

    return ;
}

int ArrayList::getInt(int idx) const {
    if(idx<0 || idx>=contains) {
        return INFINITY;
    }

    return array[idx];
}

bool ArrayList::isEmpty() const {
    return (contains == 0);
}

int ArrayList::getContains() const {
    return contains;
}


class Graph {
    int node;
    int edge;
    bool isDirected;

    ArrayList* adjList;

public:
    Graph();
    ~Graph();

    void setGraph(int, bool);

    void addEdge(int, int);
    void removeEdge(int, int);
    bool isEdge(int, int) const;
    int getDegree(int) const;
    void print(ofstream&) const;

    // offline functionality
    int appxAlgo2A();
    int appxAlgo2B();
};

Graph::Graph() {
    node = edge = 0;
    isDirected = false;
    adjList = NULL;
}

Graph::~Graph() {
    node = edge = 0;
    isDirected = false;
    delete[] adjList;
}

void Graph::setGraph(int node, bool isDirected) {
    this->node = node;
    this->isDirected = isDirected;

    adjList = new ArrayList[node];
    return ;
}

void Graph::addEdge(int u, int v) {
    if((u<0 || u>=node) || (v<0 || v>=node)) {
        return ;  // operation failed
    }

    if(isEdge(u, v) == true) {
        return ;  // edge already exists
    } else {
        adjList[u].insert(v);
        edge++;

        if(isDirected == false) {
            adjList[v].insert(u);
        }
    }

    return ;
}

void Graph::removeEdge(int u, int v) {
    if((u<0 || u>=node) || (v<0 || v>=node)) {
        return ;  // operation failed
    }

    if(isEdge(u, v) == false) {
        return ;  // no such edge exists
    } else {
        adjList[u].remove(v);
        edge--;

        if(isDirected == false) {
            adjList[v].remove(u);
        }
    }

    return ;
}

bool Graph::isEdge(int u, int v) const {
    if((u<0 || u>=node) || (v<0 || v>=node)) {
        return false;  // no such edge exists
    }

    if(adjList[u].search(v) == INVALID_INDEX) {
        return false;  // no such edge exists
    } else {
        return true;
    }
}

int Graph::getDegree(int u) const {
    int inDeg = 0;
    int outDeg = adjList[u].getContains();

    if(isDirected == true) {
        for(int i=0; i<node; i++) {
            if(isEdge(i, u) == true) {
                inDeg++;
            }
        }
    }

    return (inDeg+outDeg);
}

void Graph::print(ofstream& oObj) const {
    oObj << "node: " << node << "\t" << "edge: " << edge << "\n" << endl;

    for(int i=0; i<node; i++) {
        oObj << "node " << i << ": ";

        for(int ii=0; ii<adjList[i].getContains(); ii++) {
             oObj << adjList[i].getInt(ii) << " ";
        }

        oObj << endl;
    }

    return ;
}

int Graph::appxAlgo2A() {
    int vertexCover, idx, index, v;
    vertexCover = idx = 0;

    bool isDone = false;

    struct Edge {
        int u;
        int v;
    } tempArray[edge];

    srand(time(NULL));  // NOTICE

    while(isDone == false) {
        index = ((rand()<<2) + rand()/10)%node;  // NOTICE
        isDone = true;

        if(adjList[index].isEmpty() == false) {
            v = adjList[index].getInt(0);

            while(adjList[index].isEmpty() == false) {
                tempArray[idx].u = index;
                tempArray[idx++].v = adjList[index].getInt(0);

                removeEdge(index, adjList[index].getInt(0));
            }

            while(adjList[v].isEmpty() == false) {
                tempArray[idx].u = v;
                tempArray[idx++].v = adjList[v].getInt(0);

                removeEdge(v, adjList[v].getInt(0));
            }

            vertexCover+=2;
        }

        for(int i=0; i<node; i++) {
            if(adjList[i].isEmpty() == false) {
                isDone = false;
                break;
            }
        }
    }

    for(int i=0; i<idx; i++) {
        addEdge(tempArray[i].u, tempArray[i].v);
    }

    return vertexCover;
}

int Graph::appxAlgo2B() {
    int vertexCover, idx, u, v, maxDeg, degree;
    vertexCover = idx = 0;

    bool isDone = false;

    struct Edge {
        int u;
        int v;
    } tempArray[edge];

    while(isDone == false) {
        u = v = maxDeg = -1;  // NOTICE
        isDone = true;

        /* finding maxDeg edge */
        for(int i=0; i<node; i++) {
            for(int ii=0; ii<adjList[i].getContains(); ii++) {
                degree = getDegree(i) + getDegree(adjList[i].getInt(ii));

                if(degree > maxDeg) {
                    maxDeg = degree;
                    u = i;
                    v = adjList[i].getInt(ii);
                }
            }
        }

        while(adjList[u].isEmpty() == false) {
            tempArray[idx].u = u;
            tempArray[idx++].v = adjList[u].getInt(0);

            removeEdge(u, adjList[u].getInt(0));
        }

        while(adjList[v].isEmpty() == false) {
            tempArray[idx].u = v;
            tempArray[idx++].v = adjList[v].getInt(0);

            removeEdge(v, adjList[v].getInt(0));
        }

        vertexCover+=2;

        for(int i=0; i<node; i++) {
            if(adjList[i].isEmpty() == false) {
                isDone = false;
                break;
            }
        }
    }

    for(int i=0; i<idx; i++) {
        addEdge(tempArray[i].u, tempArray[i].v);
    }

    return vertexCover;
}


int main() {
    ifstream iObj;
    ofstream oObj;

    Graph graph15, graph17, graph19, graph21;

    int node,edge, u, v;
    char garbage;


    /* constructing 4 graphs from 4 different datasets */
    iObj.open("dataset15.txt");  // dataset15

    if(iObj.is_open() == true) {
        iObj >> node;
        iObj >> edge;
    } else {
        exit(EXIT_FAILURE);
    }

    graph15.setGraph(node, false);  // undirected graph

    for(int i=0; i<edge; i++) {
        iObj >> garbage >> u >> v;

        graph15.addEdge(u-1, v-1);
    }

    iObj.close();

    iObj.open("dataset17.txt");  // dataset17

    if(iObj.is_open() == true) {
        iObj >> node;
        iObj >> edge;
    } else {
        exit(EXIT_FAILURE);
    }

    graph17.setGraph(node, false);  // undirected graph

    for(int i=0; i<edge; i++) {
        iObj >> garbage >> u >> v;

        graph17.addEdge(u-1, v-1);
    }

    iObj.close();

    iObj.open("dataset19.txt");  // dataset19

    if(iObj.is_open() == true) {
        iObj >> node;
        iObj >> edge;
    } else {
        exit(EXIT_FAILURE);
    }

    graph19.setGraph(node, false);  // undirected graph

    for(int i=0; i<edge; i++) {
        iObj >> garbage >> u >> v;

        graph19.addEdge(u-1, v-1);
    }

    iObj.close();

    iObj.open("dataset21.txt");  // dataset21

    if(iObj.is_open() == true) {
        iObj >> node;
        iObj >> edge;
    } else {
        exit(EXIT_FAILURE);
    }

    graph21.setGraph(node, false);  // undirected graph

    for(int i=0; i<edge; i++) {
        iObj >> garbage >> u >> v;

        graph21.addEdge(u-1, v-1);
    }

    iObj.close();


    /* computation starts */
    int worst, best, avg, vc, vc2B[4];

    oObj.open("report.txt");

    if(oObj.is_open() == true) {
        // NOTHING
    } else {
        exit(EXIT_FAILURE);
    }

    oObj << "Evaluation for 2(a):" << "\n" << endl;

    /* vc evaluation for 2B appx algorithm */
    vc2B[0] = graph15.appxAlgo2B();
    vc2B[1] = graph17.appxAlgo2B();
    vc2B[2] = graph19.appxAlgo2B();
    vc2B[3] = graph21.appxAlgo2B();

    /* vc evaluation for 2A appx algorithm */
    worst = -1;  // maximum of all
    best = (-1)*INFINITY;  // minimum of all
    avg = 0;

    /* dataset15 */
    for(int i=0; i<5; i++) {
        vc = graph15.appxAlgo2A();
        avg += vc;

        if(vc > worst) {
            worst = vc;
        }

        if(vc < best) {
            best = vc;
        }
    }

    oObj << "for data set-15: best = " << best << " worst = " << worst << " avg = " << (avg/5) << endl;
    // taking the floor value of avg/5

    /* dataset17 */
    worst = -1;
    best = (-1)*INFINITY;
    avg = 0;

    for(int i=0; i<5; i++) {
        vc = graph17.appxAlgo2A();
        avg += vc;

        if(vc > worst) {
            worst = vc;
        }

        if(vc < best) {
            best = vc;
        }
    }

    oObj << "for data set-17: best = " << best << " worst = " << worst << " avg = " << (avg/5) << endl;

    /* dataset19 */
    worst = -1;
    best = (-1)*INFINITY;
    avg = 0;

    for(int i=0; i<5; i++) {
        vc = graph19.appxAlgo2A();
        avg += vc;

        if(vc > worst) {
            worst = vc;
        }

        if(vc < best) {
            best = vc;
        }
    }

    oObj << "for data set-19: best = " << best << " worst = " << worst << " avg = " << (avg/5) << endl;

    /* dataset21 */
    worst = -1;
    best = (-1)*INFINITY;
    avg = 0;

    for(int i=0; i<5; i++) {
        vc = graph21.appxAlgo2A();
        avg += vc;

        if(vc > worst) {
            worst = vc;
        }

        if(vc < best) {
            best = vc;
        }
    }

    oObj << "for data set-21: best = " << best << " worst = " << worst << " avg = " << (avg/5) << endl;

    oObj << "\n" << endl;

    oObj << "Evaluation for 2(b):" << "\n" << endl;
    oObj << "for data set-15: vc = " << vc2B[0] << "  minVC = " << 420 << endl;
    oObj << "for data set-17: vc = " << vc2B[1] << "  minVC = " << 560 << endl;
    oObj << "for data set-19: vc = " << vc2B[2] << "  minVC = " << 720 << endl;
    oObj << "for data set-21: vc = " << vc2B[3] << "  minVC = " << 900 << endl;


    /* task-4 */
    Graph graphWorst;

    graphWorst.setGraph(2, false);
    graphWorst.addEdge(0, 1);

    oObj << "\n" << endl;
    oObj << "task-4: " << "\n" << endl;
    graphWorst.print(oObj);

    oObj.close();

    return 0;
}
