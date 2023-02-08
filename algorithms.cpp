#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <stack>
#include "algorithms.h"

using namespace std;

//referenced https://www.technical-recipes.com/2011/priority-queues-and-min-priority-queues-in-c/ 
struct compare {
  bool operator()(const Problem *a, const Problem *b) const {
    return a->fn_cost > b->fn_cost;
  }
};

//referenced https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
priority_queue<Problem*, vector<Problem*>, compare> frontier;
vector<Problem*> exploredSet;

void uniformCostSearch(Problem* initialState) {
    frontier.push(initialState);
//    cout << "Added initial node to frontier" << endl;
    Problem* currNode;

    //while the frontier is not empty keep searching
    while(!frontier.empty()) {
        currNode = frontier.top();
        frontier.pop();
//        cout << "Assigned frontier top to a current node for exploring and popped from frontier" << endl;
        cout << "The best state to expand with g(n) = " << currNode->gn_cost << " and h(n) = " << currNode->hn_cost << endl;
        for(int j = 0; j < 9; j++) {
            if(j == 2 || j == 5 || j == 8) {
                cout << currNode->puzzle.at(j) << endl;
            }
            else{
                cout << currNode->puzzle.at(j) << " ";
            }
        }
        
        //if the current node matches the goal state exit while loop and return 
        if(currNode->goalTest()) {
            cout << "Goal!!" << endl;
            cout << endl;
            cout << "Solution" << endl;
            stack<Problem*> solution;
            while(currNode != NULL) {
                solution.push(currNode);
                currNode = currNode->parent;
            }
            while(!solution.empty()) {
                for(int s = 0; s < 9; s++) {
                    if(s == 2 || s == 5 || s == 8) {
                        cout << solution.top()->puzzle.at(s) << endl;
                    }
                    else {
                        cout << solution.top()->puzzle.at(s) << " ";
                    }
                }
                cout << endl;
                solution.pop();
            }
            return;
        }
        //current node does not match goal state so keep searching 
        else {
            //explore the current node by creating its children
            currNode->expandNode();
//            cout << "Expanded children of current node" << endl;

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
//                    cout << "Already explored up child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->upChild);
//                    cout << "Added up child" << endl;
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
//                cout << "Already explored down child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->downChild);
//                    cout << "Added down child" << endl;
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
//                    cout << "Already explored left child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->leftChild);
//                    cout << "Added left child" << endl;
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
//                   cout << "Already explored right child" << endl;
                } 
                 //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->rightChild);
//                    cout << "Added right child" << endl;
                }
            }
            //add current node to explored set and pop it from the frontier
            exploredSet.push_back(currNode);
//            cout << "Added node to explored set" << endl;
        }

    }
}
void aStarMisplaced(Problem* initialState) {
    frontier.push(initialState);
//    cout << "Added initial node to frontier" << endl;
    Problem* currNode;

    //while the frontier is not empty keep searching
    while(!frontier.empty()) {
        currNode = frontier.top();
        frontier.pop();
//        cout << "Assigned frontier top to a current node for exploring and popped from frontier" << endl;
        cout << "The best state to expand with g(n) = " << currNode->gn_cost << " and h(n) = " << currNode->hn_cost << endl;
        for(int j = 0; j < 9; j++) {
            if(j == 2 || j == 5 || j == 8) {
                cout << currNode->puzzle.at(j) << endl;
            }
            else{
                cout << currNode->puzzle.at(j) << " ";
            }
        }
        
        //if the current node matches the goal state exit while loop and return 
        if(currNode->goalTest()) {
            cout << "Goal!!" << endl;
            cout << endl;
            cout << "Solution" << endl;
            stack<Problem*> solution;
            while(currNode != NULL) {
                solution.push(currNode);
                currNode = currNode->parent;
            }
            while(!solution.empty()) {
                for(int s = 0; s < 9; s++) {
                    if(s == 2 || s == 5 || s == 8) {
                        cout << solution.top()->puzzle.at(s) << endl;
                    }
                    else {
                        cout << solution.top()->puzzle.at(s) << " ";
                    }
                }
                cout << endl;
                solution.pop();
            }
            return;
        }
        //current node does not match goal state so keep searching 
        else {
            //explore the current node by creating its children
            currNode->expandNode();
//            cout << "Expanded children of current node" << endl;

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
//                    cout << "Already explored up child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->upChild->misplacedHeuristic();
                    currNode->upChild->fn_cost = currNode->upChild->gn_cost + currNode->upChild->hn_cost;
                    frontier.push(currNode->upChild);
//                    cout << "Added up child" << endl;
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
//                cout << "Already explored down child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->downChild->misplacedHeuristic();
                    currNode->downChild->fn_cost = currNode->downChild->gn_cost + currNode->downChild->hn_cost;
                    frontier.push(currNode->downChild);
//                    cout << "Added down child" << endl;
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
//                    cout << "Already explored left child" << endl;
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->leftChild->misplacedHeuristic();
                    currNode->leftChild->fn_cost = currNode->leftChild->gn_cost + currNode->leftChild->hn_cost;
                    frontier.push(currNode->leftChild);
//                    cout << "Added left child" << endl;
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
//                   cout << "Already explored right child" << endl;
                } 
                 //child node was not found in explored set so add it to the rontier
                else {
                    currNode->rightChild->misplacedHeuristic();
                    currNode->rightChild->fn_cost = currNode->rightChild->gn_cost + currNode->rightChild->hn_cost;
                    frontier.push(currNode->rightChild);
//                    cout << "Added right child" << endl;
                }
            }
            //add current node to explored set and pop it from the frontier
            exploredSet.push_back(currNode);
//            cout << "Added node to explored set" << endl;
        }
    }
}