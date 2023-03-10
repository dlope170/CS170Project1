#ifndef PROBLEM_H_
#define PROBLEM_H_
#include <vector>
#include <string>
using namespace std;

class Problem {
    public: 
        vector<int> puzzle;
        vector<int> goal_state = {1,2,3,4,5,6,7,8,0};
        int gn_cost;
        int hn_cost;
        int fn_cost;
        void misplacedHeuristic();
        void euclideanDistance();

        //initialize problem with new puzzle
        Problem(vector<int> newPuzzle);

        //check if puzzle matches goal_state
        bool goalTest();

        //operators
        Problem* up();
        Problem* down();
        Problem* left();
        Problem* right();
        void expandNode();

        //pointers to parent and children of the current node
        Problem* parent;
        Problem* upChild;
        Problem* downChild;
        Problem* leftChild;
        Problem* rightChild;

        int findZero();
        int findValue(int val);

};


#endif //PROBLEM_H_
