/*
Tommy Bonetti Section 1002
CS 302 Ed Jorgenson
This is the implementation file for the class mazeSolver.h.
*/

#include "mazeSolver.h"
#include "priorityQueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctgmath>

using namespace std;

static const string LTC = "\u2554";					// l, left top corner
static const string RTC = "\u2557";					// r, right top corner
static const string LBC = "\u255A";					// k, left bottom corner
static const string RBC = "\u255D";					// z, right bottom corner
static const string HLN = "\u2550";					// -, horizontal line
static const string VLN = "\u2551";					// i, vertical line
static const string CTR = "\u256C";					// x, center 4 way
static const string VLT = "\u2560";					// f, vertical left
static const string VRT = "\u2563";					// 7, vertical right
static const string HUP = "\u2569";					// ^, horizontal up
static const string HDW = "\u2566";					// t, horizontal down
static const string BLT = "\u2022";					// bullet
static const string SPC = " ";						// space
static const string STR = "S";						// start
static const string END = "E";						// end
const char* bold	= "\033[lm";					// start bolding
const char* red		= "\033[31m";					// start red
const char* green	= "\033[32m";					// start green
const char* unbold	= "\033[0m";					// end bolding/reset

/* The mazeSolver() constructor function should initialize class variables (NULL or
0 as appropriate). */
mazeSolver::mazeSolver()
{
   height = 0;
   width = 0;
   mazeTitle = "";
   int startR = 0;
   int startC = 0;
   int endR = 0;
   int endC = 0;
   int steps = 0;
}

/* The ~mazeSolver() destructor function should free the allocated memory */
mazeSolver::~mazeSolver()
{
    delete [] maze;
}

/* The readmaze(const string) function should attempt to open and read the passed
maze file name. If the function is unable to open the file, a false should be
returned. The first line will contain the maze title, the next line will contain the
maze height and width. The remaining lines will contain the maze contents where
S is the start and E is the end and otherwise spaces indicate a path and non-space
indicates a wall. The function should dynamically create the maze (of the
appropriate size) and read the maze */
bool mazeSolver::readMaze(const string inFileName) {
    //Create the infile that will be attempted to be opened.
    ifstream inFile;
    //Create a variable that will be used to represent each line of the maze
    string inLine = "";
    //Create a variable that will be used to represent each row counter.
    int rowCounter = 0;
    inFile.open(inFileName);
    //Check if the file is able to be opened, if not return false.
    if(inFile) {
        //Read the first line which will contain the maze Title
        getline(inFile,mazeTitle);
        //Now read the next line which will contain the maze height and width;
        inFile >> height >> width; /*
        if(height > MAX_SIZE || height < MIN_SIZE || width > MAX_SIZE || width < MIN_SIZE) {
            cout << "Error: Too big of a maze." << endl;
            return false;
        }
        */
        //Use the height and width to allocate memory for the maze.
        maze = new mazeCell*[height];
        for(int i=0; i<height; i++) {
            maze[i] = new mazeCell[width];
        }
        inFile.ignore();
        //Finally, read the remaining lines which will contain the maze contents where S is the start and E is the end.
        while(rowCounter<height) {
            getline(inFile,inLine);
            //Now go through each char in the line, and input it into the maze appropriately
            for(int i=0; i<inLine.length(); i++) {
                switch(inLine[i]) {
                    //Create a switch case for the character.
                    //If the character is an S, then it is the Start position, so declare the variable startC and startR
                    case 'S' :  startC = i;
                                startR = rowCounter;

                    //If the character is an E, then is the end position, so declare the variable endC and endR
                    case 'E' :  endC = i;
                                endR = rowCounter;
                }
                maze[rowCounter][i].value=inLine[i];
                maze[rowCounter][i].c = i;
                maze[rowCounter][i].r = rowCounter;
            }
            //increment row after every line.
            rowCounter++;
        }
    }
    else {
        cout << "Error: Unable to open file." << endl;
        return false;
    }
}

/* The getTitle() function should return the current maze title. */
string mazeSolver::getTitle() const {
    return mazeTitle;
}

/* The getSteps() function should return the current value of the steps class variable.  */
int mazeSolver::getSteps() const {
    return steps;
}

/* The printMaze() function should print the formatted maze using UNICODE
characters */
void mazeSolver::printMaze() const {
    //Go through each value and print. put a line feed after every row
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            switch(maze[i][j].value) {
                    //Create a switch case for the character.
                    //If the character is an S, then it is the Start position, so declare the variable startC and startR
                    case 'S' :  cout << STR;
                                break;
                    //If the character is an E, then is the end position, so declare the variable endC and endR
                    case 'E' :  cout << END;
                                break;
                    //If its a space, then just put it into the maze as a space which signifies an open route
                    case ' ' :  cout << SPC;
                                break;
                    //If its the left top corner marked by 'l'
                    case 'l' :  cout << LTC;
                                break;
                    //ifs its the right top corner marked by 'r'
                    case 'r' :  cout << RTC;
                                break;
                    //if its the left bottom corner marked by 'k'
                    case 'k' :  cout << LBC;
                                break;
                    //if its the right bottom corner marked by 'z'
                    case 'z' :  cout << RBC;
                                break;
                    //if its a horizontal line marked by '-'
                    case '-' :  cout << HLN;
                                break;
                    //if its a vertical line marked by a 'i'
                    case 'i' :  cout << VLN;
                                break;
                    //if its a center 4 way marked by an 'x'
                    case 'x' :  cout << CTR;
                                break;
                    //if its a vertical left marked by an 'f'
                    case 'f' :  cout << VLT;
                                break;
                    //if its a vertical right marked by a 7
                    case '7' :  cout << VRT;
                                break;
                    //if its a horizontal up marked by a '^'
                    case '^' :  cout << HUP;
                                break;
                    //if its a horizontal down marked by a 't'
                    case 't' :  cout << HDW;
                                break;
                    case '.' :  cout << BLT;
                                break;
            }
        }
        cout << endl;
    }
}

/* The findPath() function should find a path through the maze using the passed
strategy (i.e., using either the DFS or A* algorithm). */
bool mazeSolver::findPath(mazeStrategyOptions pathMethod) {
    if(pathMethod== DFS) {
        if(findPathDFS())
            //If a path was successfully found, return true.
            return true;
        else
            return false;
    }
    if(pathMethod == ASTAR) {
        //in case mazeStrategy Option is ASTART
        if(findPathASTAR())
            //If a path was successfully found, return true.
            return true;
        else
            return false;
    }
    else
        return false;
}

/* The findPathDFS() function should use the recursive DFS algorithm to find and
mark a path through the maze. If a path can be found, the path should be marked,
the steps class variable set appropriately, and true returned. If no path can be
found, the function should return false.  */
bool mazeSolver::findPathDFS() {
    mazeCell * startingCell;
    startingCell = &maze[startR][startC];

    //First call recursive DFS function with start cell
    if(dfs(startingCell))
        return true;

    //After recursive function is done determine the number of steps
    //by starting in the beginning and going through the end until the next cell is over
    int currR = startR;
    int currC = startC;
    bool forever =true;
    /*
    while(forever) {
        if(currR-1>=0) {
            if(maze[currR-1][currC].value == BLT || maze[currR-1][]
        }
    }
    */
}

//The recursive function to accompany the findPathDfs function
bool mazeSolver::dfs(mazeCell * currCell) {
    mazeCell * mainCell = currCell;
    //First check if the current cell is a goal cell, if so return true
    if(currCell->value == 'E') {
        steps--;
        return true;
    }
    //Now Check if the cell is non=traversable or the cell has already been visited. If so
    //Return false. Check if its either a whitespace(traversable) or the start position)
    if((currCell->value != ' ' && currCell->value!= 'S') || currCell->visited == true)
        return false;
    //Mark the current cell
    currCell->visited = true;
    if(currCell->value !='S') {
        currCell->value = '.';
        steps++;
    }
    //Check if the above cell is valid.
    if(currCell->r-1>=0) {
        currCell = &maze[currCell->r-1][currCell->c];
        //Call the recursive function using the next cell.
        //If the recursive function returns true, return true
        if(dfs(currCell))
            return true;
        else
            currCell = mainCell;
    }
    //Do the same as above with the other three directions.
    //Check the downwards direction now
    if(currCell->r+1<height) {
        currCell = &maze[currCell->r+1][currCell->c];
        if(dfs(currCell))
            return true;
        else
            currCell = mainCell;
    }
    //Check the left direction now
    if(currCell->c-1>=0) {
        currCell = &maze[currCell->r][currCell->c-1];
        if(dfs(currCell))
            return true;
        else
            currCell = mainCell;
    }
    if(currCell->c+1<width) {
        currCell = &maze[currCell->r][currCell->c+1];
        if(dfs(currCell))
            return true;
        else
            currCell = mainCell;
    }
    //unmark the cell.
    currCell->value = ' ';
    steps--;
    return false;
}

/* The findPathASTAR() function should use the A* algorithm to find and mark a
path through the maze. If a path can be found, the path should be marked, the
steps class variables set appropriately, and true returned. If no path can be found,
the function should return false. */
bool mazeSolver::findPathASTAR() {
    //Create a current cell that will be used to traverse
    mazeCell curr;
    mazeCell nextCell;
    int heuristic;
    int fofN;
    //Create a priority queue that begins as empty
    priorityQueue<mazeCell> locations;
    //Set the value of g(n) of the startcell to 0
    maze[startR][startC].g = 0;

    //Add the start location to the cell priority queue.
    locations.insert(maze[startC][startR], maze[startC][startR].g);

    while(!locations.isEmpty()) {
        //grab cell from the priority queue.
        if(locations.deleteMin(curr, curr.g)) {
            //mark the cell as visited
            curr.visited=true;
            //if the current cell is the goal cell then mark the path using '.'
            if(curr.c == endC && curr.r == endR) {
                maze[curr.prevC][curr.prevR].value = '.';
                return true;
            }
            //Check the up cell
            if(curr.r-1>=0) {
                nextCell.c = curr.c;
                nextCell.r = curr.r-1;
                //check thats it not a wall and has not been visited.
                if((nextCell.value == ' ' || nextCell.value == 'E' || nextCell.value == 'S') && !nextCell.visited==false) {
                    nextCell.prevC = curr.c;
                    nextCell.prevR = curr.r;
                    nextCell.g = curr.g+1;
                    heuristic = abs(curr.c-endC) + abs(curr.r-endR);
                    fofN = curr.g + heuristic;
                    locations.insert(nextCell, fofN);
                }
            }
            //Check the down cell
            if(curr.r+1<height) {
                nextCell.c = curr.c;
                nextCell.r = curr.r+1;
                //check thats it not a wall and has not been visited.
                if((nextCell.value == ' ' || nextCell.value == 'E' || nextCell.value == 'S') && !nextCell.visited==false) {
                    nextCell.prevC = curr.c;
                    nextCell.prevR = curr.r;
                    nextCell.g = curr.g+1;
                    heuristic = abs(curr.c-endC) + abs(curr.r-endR);
                    fofN = curr.g + heuristic;
                    locations.insert(nextCell, fofN);
                }
            }
            //Check the right cell
            if(curr.c-1>=0) {
                nextCell.c = curr.c-1;
                nextCell.r = curr.r;
                //check thats it not a wall and has not been visited.
                if((nextCell.value == ' ' || nextCell.value == 'E' || nextCell.value == 'S') && nextCell.visited==false) {
                    nextCell.prevC = curr.c;
                    nextCell.prevR = curr.r;
                    nextCell.g = curr.g+1;
                    heuristic = abs(curr.c-endC) + abs(curr.r-endR);
                    fofN = curr.g + heuristic;
                    locations.insert(nextCell, fofN);
                }
            }
            //Check the up cell
            if(curr.c+1<width) {
                nextCell.c = curr.c+1;
                nextCell.r = curr.r;
                //check thats it not a wall and has not been visited.
                if((nextCell.value == ' ' || nextCell.value == 'E' || nextCell.value == 'S') && nextCell.visited==false) {
                    nextCell.prevC = curr.c;
                    nextCell.prevR = curr.r;
                    nextCell.g = curr.g+1;
                    heuristic = abs(curr.c-endC) + abs(curr.r-endR);
                    fofN = curr.g + heuristic;
                    locations.insert(nextCell, fofN);
                }
            }
        }
    }
    return false;
}

