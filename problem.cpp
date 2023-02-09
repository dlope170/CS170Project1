#include "problem.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Problem::Problem(vector<int> newPuzzle) {
    puzzle = newPuzzle;
    gn_cost = 0;
    hn_cost = 0;
    fn_cost = 0;
    parent = NULL;
    upChild = NULL;
    downChild = NULL;
    leftChild = NULL;
    rightChild = NULL;
}
bool Problem::goalTest() {
    for(int i = 0; i < 9; i++) {
        if (puzzle.at(i) != goal_state.at(i)) {
            return false;
        }
    }
    return true;
}
int Problem::findZero() {
    for(int i = 0; i < 9;i++) {
        if(puzzle.at(i) == 0) {
            return i;
        }
    }
}
Problem* Problem::up() {
    int location = findZero();
    if(location == 0 || location == 1 || location == 2) {
        //invalid move unable to create that child so set it to null
        return NULL;
    }
    else {
        Problem* upNode = new Problem(puzzle);
        swap(upNode->puzzle.at(location), upNode->puzzle.at(location - 3));
        upNode->parent = this;
        upNode->gn_cost = upNode->parent->gn_cost + 1;
        upNode->fn_cost = upNode->gn_cost + upNode->hn_cost;
        return upNode;
    }
}
Problem* Problem::down() {
    int location = findZero();
    if(location == 6 || location == 7 || location == 8) {
        //invalid move unable to create that child so set it to null
        return NULL;
    }
    else {
        Problem* downNode = new Problem(puzzle);
        swap(downNode->puzzle.at(location), downNode->puzzle.at(location + 3));
        downNode->parent = this;
        downNode->gn_cost = downNode->parent->gn_cost + 1;
        downNode->fn_cost = downNode->gn_cost + downNode->hn_cost;
        return downNode;
    }
}
Problem* Problem::left() {
    int location = findZero();
    if(location == 0 || location == 3 || location == 6) {
        //invalid move unabe to create that child so set it to null
        return NULL;
    }
    else {
        Problem* leftNode = new Problem(puzzle);
        swap(leftNode->puzzle.at(location), leftNode->puzzle.at(location - 1));
        leftNode->parent = this;
        leftNode->gn_cost = leftNode->parent->gn_cost + 1;
        leftNode->fn_cost = leftNode->gn_cost + leftNode->hn_cost;
        return leftNode;
    }
}
Problem* Problem::right() {
    int location = findZero();
    if(location == 2 || location == 5 || location == 8) {
        //invalid move unable  to create that child so set it to null
        return NULL;
    }
    else {
        Problem* rightNode = new Problem(puzzle);
        swap(rightNode->puzzle.at(location), rightNode->puzzle.at(location + 1));
        rightNode->parent = this;
        rightNode->gn_cost = rightNode->parent->gn_cost + 1;
        rightNode->fn_cost = rightNode->gn_cost + rightNode->hn_cost;
        return rightNode;

    }
}
void Problem::expandNode() {
    //create all 4 children and either set them as null or assign a node to that child
    this->upChild = up();
    this->downChild = down();
    this->leftChild = left();
    this->rightChild = right();
}
void Problem::misplacedHeuristic() {
  int cnt = 0;
  for (int i = 0; i < 8; i++) {
    if (puzzle.at(i) != goal_state.at(i)) {
      cnt++;
    }
  }
  this->hn_cost = cnt;
}
int Problem::findValue(int val) {
  int position;
  for(int i = 0; i < puzzle.size(); i++) {
    if(puzzle.at(i) == val) {
      position = i;
    }
  }
  return position;
}
void Problem::euclideanDistance() {
  int cnt = 0;
  for(int i = 0; i < 8; i++) {
    if(puzzle.at(i) != goal_state.at(i)) {
      //1 not in correct position 
      if(i == 0){
        int currPosition = findValue(1);
        int currRow = currPosition/3;
        int goalRow = 0;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 0;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
      else if(i == 1) {
        int currPosition = findValue(2);
        int currRow = currPosition/3;
        int goalRow = 0;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 1;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
      else if(i == 2) {
        int currPosition = findValue(3);
        int currRow = currPosition/3;
        int goalRow = 0;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 2;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
      else if(i == 3) {
        int currPosition = findValue(4);
        int currRow = currPosition/3;
        int goalRow = 1;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 0;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
      else if (i == 4) {
        int currPosition = findValue(5);
        int currRow = currPosition/3;
        int goalRow = 1;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 1;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
      else if(i == 5) {
        int currPosition = findValue(6);
        int currRow = currPosition/3;
        int goalRow = 1;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 2;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
      else if(i == 6) {
        int currPosition = findValue(7);
        int currRow = currPosition/3;
        int goalRow = 2;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 0;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
      else if(i == 7) {
        int currPosition = findValue(8);
        int currRow = currPosition/3;
        int goalRow = 2;
        int rowDifference = abs(currRow - goalRow);
        int currColumn = currPosition % 3;
        int goalColumn = 1;
        int columnDifference = abs(currColumn - goalColumn);
        int cost = rowDifference + columnDifference; 
        cnt = cnt + cost; 
      }
    }
  }
  this->hn_cost = cnt;
}
