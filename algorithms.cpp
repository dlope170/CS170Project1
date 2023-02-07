#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include "algorithms.h"

using namespace std;

//referenced https://www.technical-recipes.com/2011/priority-queues-and-min-priority-queues-in-c/ 
struct compare {
  bool operator()(const Problem *a, const Problem *b) const {
    return a->gn_cost > b->gn_cost;
  }
};

//referenced https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
priority_queue<Problem*, vector<Problem*>, /*greater<Problem*>*/compare> frontier;
vector<Problem*> exploredSet;

void uniformCostSearch(Problem* initialState) {
    if(initialState->goalTest()) {
        cout << "Initial state matches goal state" << endl;
        return;
    }
    frontier.push(initialState);
    cout << "Added initial node to frontier" << endl;
    Problem* currNode;

    //while the frontier is not empty keep searching
    while(!frontier.empty()) {
        currNode = frontier.top();
        frontier.pop();
        cout << "Assigned frontier top to a current node for exploring and popped from frontier" << endl;
        
        //if the current node matches the goal state exit while loop and return 
        if(currNode->goalTest()) {
            cout << "Goal!!" << endl;
            return;
        }
        //current node does not match goal state so keep searching 
        else {
            //explore the current node by creating its children
            currNode->expandNode();
            cout << "Expanded children of current node" << endl;

            //if the child is not null checks if it is already in the explored set
            //if child is already in explored set don't add it to the frontier else add it to the frontier
            if(currNode->upChild != NULL) {
                bool found = false;
                vector<Problem *>::iterator iter;
                for (iter = exploredSet.begin(); iter != exploredSet.end(); iter++) {
                    vector<int> search = (*iter)->puzzle;
                    for (int i = 0; i < search.size(); i++) {
                        if (search.at(i) == currNode->upChild->puzzle.at(i)) {
                            // keep comparing
                            found = true;
                        } 
                        else {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    } 
                    else {
                        // move on to next node and compare those 2
                    }
                }
                //child node was found in the explored set so don't add to frontier
                if (found) {
                    cout << "Already explored up child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->upChild);
                    cout << "Added up child" << endl;
                }
            }
            if(currNode->downChild != NULL) {
                bool found = false;
                vector<Problem *>::iterator iter;
                for (iter = exploredSet.begin(); iter != exploredSet.end(); iter++) {
                    vector<int> search = (*iter)->puzzle;
                    for (int i = 0; i < search.size(); i++) {
                        if (search.at(i) == currNode->downChild->puzzle.at(i)) {
                            // keep comparing
                            found = true;
                        } 
                        else {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                //child node was found in the explored set so don't add to frontier
                if (found) {
                cout << "Already explored down child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->downChild);
                    cout << "Added down child" << endl;
                }
            }
            if(currNode->leftChild != NULL) {
                bool found = false;
                 vector<Problem *>::iterator iter;
                for (iter = exploredSet.begin(); iter != exploredSet.end(); iter++) {
                    vector<int> search = (*iter)->puzzle;
                    for (int i = 0; i < search.size(); i++) {
                        if (search.at(i) == currNode->leftChild->puzzle.at(i)) {
                            // keep comparing
                            found = true;
                        } 
                        else {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                //child node was found in the explored set so don't add to frontier
                 if (found) {
                    cout << "Already explored left child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->leftChild);
                    cout << "Added left child" << endl;
                }
            }
            if(currNode->rightChild != NULL) {
                bool found = false;
                vector<Problem *>::iterator iter;
                for (iter = exploredSet.begin(); iter != exploredSet.end(); iter++) {
                    vector<int> search = (*iter)->puzzle;
                    for (int i = 0; i < search.size(); i++) {
                        if (search.at(i) == currNode->rightChild->puzzle.at(i)) {
                            // keep comparing
                            found = true;
                        } 
                        else {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
                //child node was found in the explored set so don't add to frontier
                if (found) {
                    cout << "Already explored right child" << endl;
                } 
                 //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->rightChild);
                    cout << "Added right child" << endl;
                }
            }
            //add current node to explored set and pop it from the frontier
            exploredSet.push_back(currNode);
            cout << "Added node to explored set" << endl;

        }

    }
}