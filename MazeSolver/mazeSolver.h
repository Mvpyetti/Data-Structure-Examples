/*
Tommy Bonetti CS 302 Section 1002
Assignment 8 mazeSolver header
This is the header for the mazeSolver class that will be used to solve the fastest
route to complete the maze using two different algorithms. Either depth First Search
or the A^*3 algorithm.
*/

#ifndef MAZESOLVER_H
#define MAZESOLVER_H
#include <iostream>
#include <string>

using namespace std;

enum mazeStrategyOptions {DFS, ASTAR, NONE};    //possible algorithm to solve the maze
class mazeSolver
{
    public:
        mazeSolver();                                   //Constructor will initialize class variables
        ~mazeSolver();                                  //Destructor function should free the allocated memory
        bool readMaze(const string);                    //Function will attempt to open and read the passed maze file name
        string getTitle() const;                        //Function will return the current maze Title
        void printMaze() const;                         //Function should print the formatted maze using UNICODE characters
        bool findPath(mazeStrategyOptions);             //Function should find a path through the maze using the passed strategy
        int getSteps() const;                           //Function should return the current value of the steps class variable

    private:
        struct mazeCell {
            char value;
            int r, c;
            int g;
            bool visited;
            int prevR, prevC;
        };
        bool findPathDFS();                             //Function will use the recursive DFS algorithm to find and mark a path through the maze.
        bool dfs(mazeCell *);
        bool findPathASTAR();                           //Function should use the A* algorithm to find and mark a path through the maze.
        int height;
        int width;
        string mazeTitle;                               //mazeTitle will represent the title of the maze
        int startR;
        int startC;
        int endR;
        int endC;
        int steps;
        mazeCell ** maze;
        static constexpr int MIN_SIZE = 5;
        static constexpr int MAX_SIZE = 1000;
};

#endif // MAZESOLVER_H
