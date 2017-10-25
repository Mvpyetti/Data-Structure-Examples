/* Tommy Bonetti
11/28/2016
This is the implementation file for directedGraph */

#include "directedGraph.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

/* Constructor that will be used to initialize all the class variables */
directedGraph::directedGraph() {
    vertexCount = 0;
    edgeCount = 0;
    title = "";
}

/* Destructor that will reset all the values */
directedGraph::~directedGraph()
{
    vertexCount = 0;
    edgeCount = 0;
    title = "";
}

/* Function will read the graph and check if the file is valid. If invalid
function will return a false. Function will also insert nodes into the adjacencyList. */
bool directedGraph::readGraph(const string graphName) {
    //Create an input file that will represent the input graph
    ifstream input;
    string emptystr;
    int srcNode =0;
    int dstNode =0;
    input.open(graphName);

    //Check if the graph is able to be opened
    if(input) {
        getline(input,emptystr);
        //Obtain the second the line which is the title
        getline(input,title);

        //ignore characters until the first ':' is reached
        input.ignore(100, ':');
        //Then store the next valuen into vertex count
        input >> vertexCount;

        //With the newly obtained vertexCount, make that the default sinkCount
        sinkCount = vertexCount;

        //ignore all values up until :
        input.ignore(100, ':');

        //store next value into edgecount
        input >> edgeCount;

        //ignore next line
        getline(input,emptystr);
        getline(input,emptystr);

        //dynamically allocate memory for pages using vertex count
        pages = new page[vertexCount];

        while(input >> srcNode >> dstNode) {

            //Check if either one of the vertex's are over the vertex count.
            if(srcNode > vertexCount || dstNode > vertexCount)
                cout << "addEdge: error, invalid vertex - " << srcNode << " " << dstNode << endl;
            else
                insertLinks(srcNode, dstNode);
        }

        //Now go through every node and check if it's a sink or not.
        createSinkPages();

        //Since file read successfully return true.
        return true;
    }
    //If the graph is not able to be opened return a false with an error message
    else {
        cout << "File unable to be opened." << endl;
        return false;
    }
}

//This function will insert the inlink and outlink as read from the graph to the node.
void directedGraph::insertLinks(int srcNode, int dstNode) {
    //create a temp node
    node * temp = new node;
    //Check if the inlink node is NULL, if its null allocate it. and add the srcnode value to it
    // because this is the first inlink item.
    if(pages[dstNode].inlink == NULL) {
        pages[dstNode].inlink = new node;
        pages[dstNode].inlink->item = srcNode;
    }
    //If it's not null then just add a new node to the inlink linked list
    else {
        temp->item = srcNode;
        temp->link = pages[dstNode].inlink;
        pages[dstNode].inlink = temp;
    }

    //now check if the outlinkCount is 0. If it's 0 then it's no longer a nonSink value
    if(pages[srcNode].outlinkCount == 0) {
        pages[srcNode].sink = false;
        //Decrease the sinkCount since, a node is longer a nonsink value
        sinkCount--;
    }
    //increase the outlinkCount of the node
    pages[srcNode].outlinkCount++;
}

//Function will create a sinkArray for each node
void directedGraph::createSinkPages() {
    int sinkIterator=0;
    sinkPages = new int[sinkCount];
    //iterate through every page, and check if it's a sink or not.
    //if it's a sink then add it to the sinkPages array.
    for(int i=0; i<vertexCount; i++) {
        if(pages[i].sink == true) {
            sinkPages[sinkIterator]=i;
            sinkIterator++;
        }
    }
}

//Function will show the stats of the graph in the proper format.
void directedGraph::showGraphStats() {
    cout << "Graph Statistics:" << endl;
    cout << "   Title: " << title << endl;
    cout << "   Nodes: " << vertexCount << endl;
    cout << "   Edges: " << edgeCount << endl << endl;
}

int directedGraph::getEdgeCount() const {
    return edgeCount;
}

string directedGraph::getTitle() const {
    return title;
}

int directedGraph::getVertexCount() const {
    return vertexCount;
}

//Function will calculate the page Ranks for reach individual page.
void directedGraph::findPageRanks() {
    //Bool determining convergence
    bool pageNumInserted = false;
    double sinkPageRank;
    node * curr;

    //For each page p in P Calculate PR(p) = 1 /N
    for(int i=0; i<vertexCount; i++) {
        pages[i].pageRank = 1.0/vertexCount;
    }

    //While pageRank has not converged
    for(int l=0; l<100; l++) {
        //Initialize the sinkPageRank
        sinkPageRank = 0;
        for(int i=0; i<sinkCount+1; i++) {
            sinkPageRank += pages[sinkPages[i]].pageRank;
        }
        for(int i=0; i<vertexCount; i++) {
            //insert the pagenum into the page
            if(!pageNumInserted)
                pages[i].pagenum = i;

            pages[i].newPageRank = (1-dampFactor)/vertexCount;
            pages[i].newPageRank +=  dampFactor * sinkPageRank / vertexCount;

            //for each page q in M(p) (inlinks)
            //iterate through each inLink to calculate the pageRank using Google algorithm.
            curr = pages[i].inlink;
            while(curr!=NULL) {
                pages[i].newPageRank += dampFactor * pages[curr->item].pageRank / pages[curr->item].outlinkCount;
                curr = curr->link;
            }
            pages[i].pageRank = pages[i].newPageRank;
        }
        pageNumInserted = true;
    }
    delete [] sinkPages;
}

//Function will display the 300 ranks.
void directedGraph::displayPageRanks(int amount) {
    cout << "Page Ranks:" << endl;
    cout << "-----------" << endl;
    cout << setw(5) << "Rank" << setw(10) << "Page" << setw(17) << "Rank Value" << endl;
    quickSort(0, vertexCount-1);
    for(int i=0; i<MAXTOP && i<vertexCount; i++) {
        cout << setw(5) << i+1 << setw(10) << pages[i].pagenum << setw(17) << pages[i].pageRank << endl;
    }
    cout << endl;
}

void directedGraph::quickSort(int low, int high) {
    double pivot;
    if(low < high) {
        pivot = partitionFunc(low, high);
        quickSort(low, pivot);
        quickSort(pivot+1, high);
    }
}

int directedGraph::partitionFunc(int low, int high) {
    double pivot = pages[low].pageRank;
    int i= low-1;
    int j= high+1;
    bool forever = true;
    while(forever) {
        do {
            i=i+1;
        }
        while(pages[i].pageRank > pivot);

        do {
            j = j-1;
        }
        while(pages[j].pageRank < pivot);

        if(i>=j) {
            return j;
            break;
        }
        swap(pages[i], pages[j]);
    }
    return 0;
}
