/* Your code here! */
#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <vector>
#include <utility>

using namespace std;
using namespace cs225;

class SquareMaze {
    public:
        SquareMaze();
        ~SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze();
        PNG* drawMazeWithSolution();

    private:
        void solve(vector<vector<pair<int, int>>>* solved, pair<unsigned, unsigned> point);

        class Node {
            public:
                Node(bool d, bool r) {
                    down = d;
                    right = r;
                }
                bool down;
                bool right;
        };

        vector<Node>* maze;
        DisjointSets* dset;
        int w;
        int h;
};
