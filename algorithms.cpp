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
    long int maxQueue = 0;
    frontier.push(initialState);
    Problem* currNode;

    //while the frontier is not empty keep searching
    while(!frontier.empty()) {
        currNode = frontier.top();
        frontier.pop();

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
            stack<Problem*> solution;
            while(currNode != NULL) {
                solution.push(currNode);
                currNode = currNode->parent;
            }
            int nodes = solution.size();
            cout << "To solve this problem the search algorithm expanded a total of " << exploredSet.size() << " nodes" << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxQueue << endl;
            cout << "The depth of the goal node was " << nodes - 1 << endl;
            cout << endl;
            cout << "Solution" << endl;
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
                if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->upChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->downChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                 if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->leftChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                if (found) {
                } 
                    //child node was not found in explored set so add it to the rontier
                else {
                    frontier.push(currNode->rightChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
                }
            }
            //add current node to explored set and pop it from the frontier
            exploredSet.push_back(currNode);
        }

    }
}
void aStarMisplaced(Problem* initialState) {
    long int maxQueue = 0;
    initialState->misplacedHeuristic();
    frontier.push(initialState);
    Problem* currNode;

    //while the frontier is not empty keep searching
    while(!frontier.empty()) {
        currNode = frontier.top();
        frontier.pop();
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
            stack<Problem*> solution;
            while(currNode != NULL) {
                solution.push(currNode);
                currNode = currNode->parent;
            }

            int nodes = solution.size();
            cout << "To solve this problem the search algorithm expanded a total of " << exploredSet.size() << " nodes" << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxQueue << endl;
            cout << "The depth of the goal node was " << nodes - 1 << endl;
            cout << endl;
            cout << "Solution" << endl;
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
                if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->upChild->misplacedHeuristic();
                    currNode->upChild->fn_cost = currNode->upChild->gn_cost + currNode->upChild->hn_cost;
                    frontier.push(currNode->upChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->downChild->misplacedHeuristic();
                    currNode->downChild->fn_cost = currNode->downChild->gn_cost + currNode->downChild->hn_cost;
                    frontier.push(currNode->downChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->leftChild->misplacedHeuristic();
                    currNode->leftChild->fn_cost = currNode->leftChild->gn_cost + currNode->leftChild->hn_cost;
                    frontier.push(currNode->leftChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                if (found) {
                   //child node was found in the explored set so don't add to frontier
                } 
                 //child node was not found in explored set so add it to the rontier
                else {
                    currNode->rightChild->misplacedHeuristic();
                    currNode->rightChild->fn_cost = currNode->rightChild->gn_cost + currNode->rightChild->hn_cost;
                    frontier.push(currNode->rightChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
                }
            }
            //add current node to explored set and pop it from the frontier
            exploredSet.push_back(currNode);
        }
    }
}
void aStarEuclidean(Problem* initialState) {
    long int maxQueue = 0;
    initialState->euclideanDistance();
    frontier.push(initialState);
    Problem* currNode;

    //while the frontier is not empty keep searching
    while(!frontier.empty()) {
        currNode = frontier.top();
        frontier.pop();
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
            stack<Problem*> solution;
            while(currNode != NULL) {
                solution.push(currNode);
                currNode = currNode->parent;
            }

            int nodes = solution.size();
            cout << "To solve this problem the search algorithm expanded a total of " << exploredSet.size() << " nodes" << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxQueue << endl;
            cout << "The depth of the goal node was " << nodes - 1 << endl;
            cout << endl;
            cout << "Solution" << endl;
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
                if (found) {
                   //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->upChild->euclideanDistance();
                    currNode->upChild->fn_cost = currNode->upChild->gn_cost + currNode->upChild->hn_cost;
                    frontier.push(currNode->upChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->downChild->euclideanDistance();
                    currNode->downChild->fn_cost = currNode->downChild->gn_cost + currNode->downChild->hn_cost;
                    frontier.push(currNode->downChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                 if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                //child node was not found in explored set so add it to the rontier
                else {
                    currNode->leftChild->euclideanDistance();
                    currNode->leftChild->fn_cost = currNode->leftChild->gn_cost + currNode->leftChild->hn_cost;
                    frontier.push(currNode->leftChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
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
                if (found) {
                    //child node was found in the explored set so don't add to frontier
                } 
                 //child node was not found in explored set so add it to the rontier
                else {
                    currNode->rightChild->euclideanDistance();
                    currNode->rightChild->fn_cost = currNode->rightChild->gn_cost + currNode->rightChild->hn_cost;
                    frontier.push(currNode->rightChild);
                    if (frontier.size() > maxQueue) {
                      maxQueue = frontier.size();
                    }
                }
            }
            //add current node to explored set and pop it from the frontier
            exploredSet.push_back(currNode);
        }
    }
}