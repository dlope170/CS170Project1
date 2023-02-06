#include <iostream>
#include <vector>
#include <queue>
#include "algorithms.h"

using namespace std;

//referenced https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
priority_queue<Problem*, vector<Problem*>, greater<Problem*>> frontier;
vector<Problem*> exploredSet;

void uniformCostSearch(Problem* initialState) {
    if(initialState->goalTest()) {
        cout << "Initial state matches goal state" << endl;
        return;
    }
    frontier.push(initialState);
    Problem* currNode;

    //while you haven't reached the goal state keep exploring 
    while(!frontier.top()->goalTest()) {
        //if frontier is empty return failure
        if(frontier.empty()) {
            return;
        }
        vector<Problem*>::iterator it;
        it = find(exploredSet.begin(), exploredSet.end(), frontier.top());

        if(it != exploredSet.end()) {
            //remove node from the frontier because it is already in the explored set
            frontier.pop();
        }
    
        else {
            //explore the node at front of frontier by creating its children
            currNode = frontier.top();
            currNode->expandNode();

            //if the child is not null checks if it is already in the explored set
            //if child is already in explored set don't add it to the frontier else add it to the frontier
            if(currNode->upChild != NULL) {
                vector<Problem*>::iterator it;
                it = find(exploredSet.begin(), exploredSet.end(), currNode->upChild);
                if(it != exploredSet.end()) {
                    //dont add to frontier
                }
                else {
                    frontier.push(currNode->upChild);
                }
            }
            if(currNode->downChild != NULL) {
                vector<Problem*>::iterator it;
                it = find(exploredSet.begin(), exploredSet.end(), currNode->downChild);
                if(it != exploredSet.end()) {
                    //dont add to frontier
                }
                else {
                    frontier.push(currNode->downChild);
                }
            }
            if(currNode->leftChild != NULL) {
                vector<Problem*>::iterator it;
                it = find(exploredSet.begin(), exploredSet.end(), currNode->leftChild);
                if(it != exploredSet.end()) {
                    //dont add to frontier
                }
                else {
                    frontier.push(currNode->leftChild);
                }
            }
            if(currNode->rightChild != NULL) {
                vector<Problem*>::iterator it;
                it = find(exploredSet.begin(), exploredSet.end(), currNode->rightChild);
                if(it != exploredSet.end()) {
                    //dont add to frontier
                }
                else {
                    frontier.push(currNode->rightChild);
                }
            }
        }
        cout << "Goal!!" << endl;
        cout << frontier.top()->puzzle.at(0) << " ";
        cout << frontier.top()->puzzle.at(1) << " ";
        cout << frontier.top()->puzzle.at(2) << endl;
        cout << frontier.top()->puzzle.at(3) << " ";
        cout << frontier.top()->puzzle.at(4) << " ";
        cout << frontier.top()->puzzle.at(5) << endl;
        cout << frontier.top()->puzzle.at(6) << " ";
        cout << frontier.top()->puzzle.at(7) << " ";
        cout << frontier.top()->puzzle.at(8) << endl;

    }
}