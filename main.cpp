#include <iostream>
using namespace std;

int main() {
    int userInput = 0;

    cout << "8 Puzzle Solver" << endl;
    cout << "Choose which algorithm you want to implement" << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A*" << endl;
    cout << "3. A*" << endl;
    
    cin >> userInput;
    while (userInput > 3 || userInput <= 0 ) {
        cout << "Invalid Entry" << endl;
        cout << "Choose which algorithm you want to implement" << endl;
        cout << "1. Uniform Cost Search" << endl;
        cout << "2. A*" << endl;
        cout << "3. A*" << endl;
        cin >> userInput;
    }
    cout << userInput;

    return 0;
}