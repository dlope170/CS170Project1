#include "problem.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Problem::Problem(vector<int> newPuzzle) {
    gn_cost = 0;
    puzzle = newPuzzle;
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
        //invalid move
        return NULL;
    }
    else {
        Problem* upNode = new Problem(puzzle);
        swap(upNode->puzzle.at(location), upNode->puzzle.at(location - 3));
        upNode->parent = this;
        upNode->gn_cost = upNode->parent->gn_cost + 1;
        return upNode;
    }
}
Problem* Problem::down() {
    int location = findZero();
    if(location == 6 || location == 7 || location == 8) {
        //invalid move
        return NULL;
    }
    else {
        Problem* downNode = new Problem(puzzle);
        swap(downNode->puzzle.at(location), downNode->puzzle.at(location + 3));
        downNode->parent = this;
        downNode->gn_cost = downNode->parent->gn_cost + 1;
    }
}
Problem* Problem::left() {
    int location = findZero();
    if(location == 0 || location == 3 || location == 6) {
        //invalid move
        return NULL;
    }
    else {
        Problem* leftNode = new Problem(puzzle);
        swap(leftNode->puzzle.at(location), leftNode->puzzle.at(location + 1));
        leftNode->parent = this;
        leftNode->gn_cost = leftNode->parent->gn_cost + 1;
    }
}
Problem* Problem::right() {
    int location = findZero();
    if(location == 2 || location == 5 || location == 8) {
        //invalid move
        return NULL;
    }
    else {
        Problem* rightNode = new Problem(puzzle);
        swap(rightNode->puzzle.at(location), rightNode->puzzle.at(location - 1));
        rightNode->parent = this;
        rightNode->gn_cost = rightNode->parent->gn_cost + 1;
    }
}
