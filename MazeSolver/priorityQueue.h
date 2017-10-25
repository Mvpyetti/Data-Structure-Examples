//Tommy Bonetti
//CS 302 Section 1002
//Assignment #8
//******************************************************************
//  This class, priorityQueue, will be used to represent the data structure
//  of a priorityQue. The priority Queue will be a min Heap, meaning the minimum(top)
//  value will take the priority in operations.
//******************************************************************


#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <fstream>
#include <iostream>
#include <array>

using namespace std;

template <class myType>
class priorityQueue
{
    public:
        priorityQueue(int=100);                 //Constructor will initialize the binary heap to an empty state.
        ~priorityQueue();                       //Destructor will delete the heap
        int entries() const;                    //Function will return the total count of elements in the heap.
        void insert(const myType, const int);   //Function will insert an entry into the binary heap.
        bool isEmpty() const;                   //Function should return true if there are no elements in the heap
        bool deleteMin(myType &,int &);         //Function will remove the minimum entry from the heap
        void printHeap() const;                 //Function will print the current heap in level order
        bool readData(const string);            //Function will read the formatted file and enter the values read into the array.

    private:
        struct heapNode {
            int priority;                       //Indicates the priority the node has according to the heap
            myType item;                        //The value the node contains
        };
        void buildHeap();                       //Function will update the heap to apply the heap properties.
        void reHeapUp(int);                     //Function will recursively ensure the heap order property is maintained. Starts at root, and goes down.
        void reHeapDown(int);                   //Function will recursively ensure the heap order property is maintained, starts at passed node and goes up
        void resize();                          //Function will create a new heap array twice the size of the existing heap.
        int count;                              //Count will represent the amount of nodes within the heap.
        int heapSize;                           //Will represent the size of the heap.
        heapNode * myHeap;                      //myHeap will represent the array of nodes in the priority que data structure.
};

/*  The priorityQueue() constructor should initialize the binary heap to an empty state. The
    parameter must be checked to ensure it is at least 100 and, if not, use the default value. */
template <class myType>
priorityQueue<myType>::priorityQueue(int initialHeapSize) {
    //initialize the count to 0.
    count=0;

    //Check if the parameter heapSize is at least 100, if it's 100 or more than initialize to that value
    //Otherwise use the default value.
    if(initialHeapSize>=100) {
        myHeap = new heapNode[initialHeapSize];
        heapSize = initialHeapSize;
    }
    else {
        heapSize = 100;
        myHeap = new heapNode[100];
    }
}

/* The ~priorityQueue() destructor should delete the heap. */
template<class myType>
priorityQueue<myType>::~priorityQueue() {
    delete[] myHeap;
}

/* The entries() function should return the total count of elements in the heap. */
template<class myType>
int priorityQueue<myType>::entries() const{
    return count;
}

/* The insert() function should insert an entry into the binary heap. If the count of heap
entries exceeds the heap size, the heap must be expanded via the private resize() function.
The heap properties must be maintained via the private reheapUp() function. The count
should be updated. */
template <class myType>
void priorityQueue<myType>::insert(const myType newItem, const int newPriority) {
    //If the count is greater than or equal to the HeapSize, than resize the heap
    //in order to prevent any segmentation fault.
    if(count >= heapSize) {
        resize();
    }
    //Now Insert the the element into the heap
    myHeap[count].item = newItem;
    myHeap[count].priority = newPriority;

    //Now reHeap, and make sure everything is in the correct spot after the insertion
    reHeapUp(count);
    //Increase the element count
    count++;

}

/* The private buildHeap() function should update the heap to apply the heap properties */
template <class myType>
void priorityQueue<myType>::buildHeap() {
    //Start at the lowest parent, and ordering everything in their correct order.
    for(int i=(count-1)/2; i>=0; i--)
        reHeapDown(i);
}

/* The isEmpty() function should return true if there are no elements in the heap and false
otherwise. */
template <class myType>
bool priorityQueue<myType>::isEmpty() const {
    //if the heapSize is not 0, then  the heap is not empty.
    if(count == 0)
        return true;
    else
        return false;
}

/* The deleteMin() function should remove the minimum entry from the heap. The heap
properties must be maintained via the private reheapDown() function. Additionally, the
count should be updated. If the heap is already empty, the function should return false
and otherwise return the minimum priority information (via reference) and return true */
template <class myType>
bool priorityQueue<myType>::deleteMin(myType & removedObj, int & removedPriority) {
    //First make sure the heap isn't already empty. Otherwise you'd be removing from an empty heap.
    if(isEmpty())
        return false;
    else {
        //Pass back the node that is being removed by reference
        removedObj = myHeap[0].item;
        removedPriority = myHeap[0].priority;
        //Orphan the lowest right most node(index count), and insert it into the root.
        myHeap[0].item = myHeap[count-1].item;
        myHeap[0].priority = myHeap[count-1].priority;
        //Decrease the total amount of elements in queue by 1
        count--;
        //Now  make sure the amount of entries is > 0 before Reheaping
        if(entries() > 0)
            //Reheap everything now starting from the root that was replaced.
            reHeapDown(0);
        //Now return true since the heap wasn't empty.
        return true;
    }
}

/* The printHeap() function should print the current heap in level order with a blank line
between each level. */
template <class myType>
void priorityQueue<myType>::printHeap() const {
    //Begin by creating a start index for the print
    int index = 0;
    //Then create a level index indicating how many values to print
    int levelIndex = 1;

    //Start a while loop that will increment the index and start printing
    while(index<count) {
        //Since the heap is being printed by levels. Print all the values in the current Level(levelindex*2)
        for(int i=0; i<levelIndex; i++) {
            //Make sure to not exceed the maximum number of values in the heap, otherwise break the while and the for loop
            if(index<count) {
                cout << myHeap[index].item << " " << myHeap[index].priority << endl;
                //Increment the index after every print
                index++;
            }
            else
                break;
        }
        //Once all values in that specific level has been printed, print a linefeed and increase the levelindex by multiplying the level index by 2
        cout << endl;
        levelIndex*=2;
    }
}

/* The readData() function should read a formatted file (name and priority) and enter the
values read into the array without using the insert() function. The size will need to be
checked and the resize() function called as needed. Once the values are read, the
buildHeap() function should be called. . */
template <class myType>
bool priorityQueue<myType>::readData(const string inFileName) {
    //Create variables to represent the current Value and current Priority
    myType currVal;
    int currPriority;
    //Create a new input file based on the parameter passed(inFileName)
    ifstream inFile;
    inFile.open(inFileName.c_str());

    //Make sure the file exists before opening it
    if(inFile) {
        while(inFile >> currVal >> currPriority) {
            //If the index reaches the heapSize, it is now out of bounds so resize the heap
            if(count >= heapSize)
                resize();
            //Start inserting the values from the line into the index within the heap
            myHeap[count].item = currVal;
            myHeap[count].priority = currPriority;

            //increment the index for the next line
            count++;
        }
        //Once all the files have been read, reheap the heap to put everything in the right order.
        buildHeap();
        //Since everything was successful, return true
        return true;
    }
    else
        //Since the file does not exist return false.
        cout << "Error opening File" << endl;
        return false;
}

/*The reheapUp() function to recursively ensure the heap order property is maintained.
Starts at tree leaf and works up to the root. Must be written recursively */
template<class myType>
void priorityQueue<myType>::reHeapUp(int currNode) {
    //Create a variable that will represent the index of the currNode's parent
    int parent= (currNode-1)/2;
    //Create a variable that will be used to swap two nodes.
    heapNode tmpNode;

    //Make sure that the parent is greater than or equal to 0
    //and its value is greater than the current nodes value
    if(parent >= 0 && myHeap[parent].priority > myHeap[currNode].priority) {
        //Since the parentNode has a greater value than the child node, swap the nodes
        tmpNode = myHeap[currNode];
        myHeap[currNode] = myHeap[parent];
        myHeap[parent] = tmpNode;

        //Once the values have been swapped, recursively go up the heap from the parent.
        reHeapUp(parent);
    }
}

/*The reheapDown() function to recursively ensure the heap order property is maintained.
Starts at the passed node and works down to the applicable leaf. Must be written
recursively */
template<class myType>
void priorityQueue<myType>::reHeapDown(int currNode) {
    //First create two index variables. One will represent the left child, and the other the right child.
    int leftChild, rightChild;

    //Create a variable representing the lesser index between the two children
    int lesserIndex;

    //Indicate the locations of those children
    leftChild = currNode*2+1;
    rightChild = currNode*2+2;

    //Then create a variable that will be used as a tempNode when swapping
    heapNode tmpNode;

    //Check if the right Child is greater than the heapSize
    if(rightChild>=count) {
        //Now check if the left child is greater than the heap. If it is, then there are no more children so return
        if(leftChild >= count)
            return;
        else
            //Since there is only one child, make that the lesser index to check
            lesserIndex = leftChild;
    }
    else {
        //if the left childs priority is less than the right childs, the lesser index is the left child
        if(myHeap[leftChild].priority <= myHeap[rightChild].priority)
            lesserIndex = leftChild;
        else
        //if the right index has a lower priority make it the lesser index
            lesserIndex = rightChild;
    }
    //Now check if the lesserindex value has a less value than the parent node
    if(myHeap[lesserIndex].priority < myHeap[currNode].priority) {
        //Since the child has a lower number priority, swap it with the parent
        tmpNode = myHeap[lesserIndex];
        myHeap[lesserIndex] = myHeap[currNode];
        myHeap[currNode] = tmpNode;

        //Recursively go to the child index now
        reHeapDown(lesserIndex);
    }
}

/* The resize() function should create a new heap array twice the size of the existing heap,
copy all entries from the current heap into the new heap, and delete the old heap. The
heapSize should be updated accordingly. */
template <class myType>
void priorityQueue<myType>::resize() {
    //First create the new heap that is twice the size of the original heap
    heapNode * newHeap = new heapNode[heapSize*2];
    //Now start copying all the values from the old Heap into the New Heap
    for(int i=0; i<count; i++) {
        newHeap[i] = myHeap[i];
    }
    //delete the old heap, then make it point to the new heap.
    delete[] myHeap;
    myHeap = newHeap;

    //resize the heapsize
    heapSize*=2;
}

#endif // PRIORITYQUEUE_H
