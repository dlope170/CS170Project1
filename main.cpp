#include "problem.h"
#include "algorithms.h"
#include <iostream>
#include <array>
#include <vector>
using namespace std;


int main() {
    int userInput = 0;
    vector<int> newPuzzle;

    cout << "Welcome to dlope170 8 Puzzle Solver" << endl;

    cout << "Enter 1 to use a default puzzle or 2 to enter your own puzzle" << endl;
    cin >> userInput;

    if(userInput == 1) {
        newPuzzle = {1,2,3,4,5,8,0,6,7};

    }
    else if (userInput == 2) {
        for(int i = 0; i < 3; i++) {
            cout << "Enter row " << i + 1 << " of puzzle making sure to press enter after each value and 0 to represent the blank" << endl;
            for( int j = 0; j < 3; j++){
                int num;
                cin >> num;
                newPuzzle.push_back(num);
            }
        }
        cout << "The puzzle you entered is" << endl;
        for(int p = 0; p < 9; p++) {
            if(p == 2 || p == 5 || p == 8) {
                cout << newPuzzle.at(p) << endl;
            }
            else {
                cout << newPuzzle.at(p) << " ";
            }
        } 
    }

    cout << "Choose which algorithm you want to implement" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with the Misplaced Tile Heuristic" << endl;
    cout << "3. A* with the Euclidean Distance Heuristic" << endl;
    
    cin >> userInput;
    while (userInput > 3 || userInput <= 0 ) {
        cout << "Invalid Entry" << endl;
        cout << "Choose which algorithm you want to implement" << endl;
        cout << "1. Uniform Cost Search" << endl;
        cout << "2. A* with the Misplaced Tile Heuristic" << endl;
        cout << "3. A* with the Euclidean Distance Heuristic" << endl;
        cin >> userInput;
    }

    Problem* startNode = new Problem(newPuzzle);

    if (userInput == 1) {
        uniformCostSearch(startNode);

    }
    else if(userInput == 2) {
        aStarMisplaced(startNode);
    }
    else if(userInput == 3) {
        aStarEuclidean(startNode);
    }

    return 0;
}