#include "problem.h"
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
        newPuzzle = {1,2,3,4,5,6,0,7,8};

    }
    else if (userInput == 2) {
        for(int i = 0; i < 3; i++) {
            cout << "Enter row " << i + 1 << " of puzzle making sure to press enter after each value" << endl;
            for( int j = 0; j < 3; j++){
                int num;
                cin >> num;
                newPuzzle.push_back(num);
            }
        }
        cout << "The puzzle you entered is" << endl;
        cout << newPuzzle.at(0) << " ";
        cout << newPuzzle.at(1) << " ";
        cout << newPuzzle.at(2) << endl;
        cout << newPuzzle.at(3) << " ";
        cout << newPuzzle.at(4) << " ";
        cout << newPuzzle.at(5) << endl;
        cout << newPuzzle.at(6) << " ";
        cout << newPuzzle.at(7) << " ";
        cout << newPuzzle.at(8) << endl;
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
        cout << "2. A*" << endl;
        cout << "3. A*" << endl;
        cin >> userInput;
    }
    

    return 0;
}