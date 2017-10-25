/* Tommy Bonetti
This class will be used to implement the main directed Graph data, before
algorithm has been calculated. The main data structure here will be a custom made one for the
algorithm being used. This is very similar to a linked list, but instead of each page pointing the successor pages,
each pages linked list points to the predecessors(inlinks). Each page will also count the amount of outlinks as per
the algorithm. */

#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H
#include <string>

using namespace std;

class directedGraph
{
    public:
        directedGraph();                    //This constructor will be used to initialize private data
        ~directedGraph();                   //Deallocate data and delete variables
        bool readGraph(const string);       //Function will be used to read the graph data from txt file
        string getTitle() const;                  //Function will obtain the title of the graph
        int getEdgeCount() const;           //Function will obtain the edge count of the graph
        int getVertexCount() const;         //Function will return the amount of vertex's
        void insertLinks(int, int);
        void createSinkPages();           //Function will create the sink pages
        void showGraphStats();        //Function will show the stats of the graph
        void findPageRanks();         //Function will call a function within the adjacency matrix to solve pageRanks
        void displayPageRanks(int);      //Function will display the ranks of the page in a specific format

    private:
        struct node{                    //node will be used to represent the inlink linked list within each page.
            int item;
            node * link;
        };
        struct page{
            node * inlink;                  //This will be the linked lists of pages pointing the specific page.
            double pageRank;
            double newPageRank;
            int pagenum;
            bool sink = true;               //bool determining if the page is a sink page(no outlinks)
            int outlinkCount = 0;
        };
        int partitionFunc(int, int);
        void quickSort(int, int);           //Function will be used to sort the graph at the very end to obtain the top 300 nodes
        double const dampFactor = 0.85;
        int const MAXTOP = 300;
        page * pages;                       //pages will represent the main array of pages/nodes within the graph.
        int * sinkPages;                    //sinkpages will represent all the nodes which are sink nodes. This was made into separate array in order to save time
        int sinkCount;                      //The amount of sink pages
        int vertexCount;                    //Represents the amount of vertex's
        int edgeCount;                      //Represents the amount of edges
        string title;                       //Represents the title of the graph
};

#endif // DIRECTEDGRAPH_H
