#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include "maze.h"
#include <vector>

SquareMaze::SquareMaze() {
    w = 0;
    h = 0;
    maze = new vector<Node>;
    dset = new DisjointSets();
}

SquareMaze::~SquareMaze() {
    delete maze;
    maze = NULL;
    delete dset;
    dset = NULL;
}

void SquareMaze::makeMaze(int width, int height) {
    w = width;
    h = height;
    dset->addelements(w * h);
    for (int a = 0; a < w * h; a++) {
        maze->push_back(Node(true, true));
    }
    for (int b = 0; b < w * h - 1; b++) {
        vector<int> dir;
        if (((b + 1) % w != 0) && (dset->find(b + 1) != dset->find(b))) {
            dir.push_back(0);
        }
        if (!(b >= w * (h - 1)) && (dset->find(b) != dset->find(b + w))) {
            dir.push_back(1);
        }
        if (!(b % w == 0) && (dset->find(b) != dset->find(b - 1))) {
            dir.push_back(2);
        }
        if (!(b < w) && (dset->find(b) != dset->find(b - w))) {
            dir.push_back(3);
        }

        if (dir.size() == 0) {
            continue;
        }
        int currentDir = dir[rand() % (dir.size())];
        if (currentDir == 0) {
            dset->setunion(b, b + 1);
            (*maze)[b].right = false;
        } else if (currentDir == 1) {
            dset->setunion(b, b + w);
            (*maze)[b].down = false;
        } else if (currentDir == 2) {
            dset->setunion(b, b-1);
            (*maze)[b - 1].right = false;
        } else if (currentDir == 3) {
            dset->setunion(b, b - w);
            (*maze)[b - w].down = false;
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) {
        if (w - 1 <= x) {
            return false;
        } else {
            return !(*maze)[x + y * w].right;
        }
    } else if (dir == 1) {
        if (h - 1 <= y) {
            return false;
        } else {
            return !(*maze)[x + y * w].down;
        }
    } else if (dir == 2) {
        if (x <= 0) {
            return false;
        } else {
            return !(*maze)[(x - 1) + y * w].right;
        }
    } else if (dir == 3) {
        if (y <= 0) {
            return false;
        } else {
            return !(*maze)[x + (y - 1) * w].down;
        }
    } else {
        return false;
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir) {
        (*maze)[w * y + x].down = exists;
    } else {
        (*maze)[w * y + x].right = exists;
    }
}

void SquareMaze::solve(vector<vector<pair<int, int>>>* solved, pair<unsigned, unsigned> point) {
    int a = point.first;
    int b = point.second;
    if ((!canTravel(a, b, 0) || (*solved)[a + 1][b].second == 0) 
        && (!canTravel(a, b, 1) || (*solved)[a][b + 1].second == 1) 
        && (!canTravel(a, b, 2) || (*solved)[a - 1][b].second == 2) 
        && (!canTravel(a, b, 3) || (*solved)[a][b - 1].second == 3)) {
	    return;
	}
    pair<int, int> curr = (*solved)[a][b];
    if (canTravel(a, b ,0) && (*solved)[a + 1][b].first == -1) {
        (*solved)[a + 1][b] = pair<int, int>(curr.first + 1, 2);
        solve(solved, pair<int, int>(a + 1, b));
    }
    if (canTravel(a, b, 1) && (*solved)[a][b + 1].first == -1) {
        (*solved)[a][b + 1] = pair<int, int>(curr.first + 1, 3);
        solve(solved, pair<int, int>(a, b + 1));
    }
    if (canTravel(a, b ,2) && (*solved)[a - 1][b].first == -1) {
        (*solved)[a - 1][b] = pair<int, int>(curr.first + 1, 0);
        solve(solved, pair<int, int>(a - 1, b));
    }
    if (canTravel(a, b, 3) && (*solved)[a][b - 1].first == -1) {
        (*solved)[a][b - 1] = pair<int, int>(curr.first + 1, 1);
        solve(solved, pair<int, int>(a, b - 1));
    }
}

vector<int> SquareMaze::solveMaze() {
    vector<vector<pair<int, int>>> solved;
    for (int i = 0; i < w; i++) {
        solved.push_back(vector<pair<int, int>>());
        for (int j = 0; j < h; j++) {
            solved.back().push_back(pair<int, int>(-1, -1));
        }
    }
    solve(&solved, pair<int, int>(0, 0));
    int max = solved[0][h - 1].first;
    pair<int, int> current(0, h - 1);
    for (int k = 0; k < w; k++) {
        if (solved[k][h - 1].first > max) {
            max = solved[k][h - 1].first;
            current = pair<int, int>(k, h - 1);
        }
    }
    vector<int> output;
    while (current != pair<int, int>(0, 0)) {
        int a = current.first;
        int b = current.second;
        int move = -1;
        int last_move = solved[a][b].second;
        move = last_move == 0 ? 2 : move;
        move = last_move == 1 ? 3 : move;
        move = last_move == 2 ? 0 : move;
        move = last_move == 3 ? 1 : move;
        output.push_back(move);
        current = (last_move == 0) ? pair<int, int>(a + 1, b) : current;
        current = (last_move == 1) ? pair<int, int>(a, b + 1) : current;
        current = (last_move == 2) ? pair<int, int>(a - 1, b) : current;
        current = (last_move == 3) ? pair<int, int>(a, b - 1) : current;
    }
    reverse(output.begin(), output.end());
    return output;
}

PNG* SquareMaze::drawMaze() {
    PNG* output = new PNG(10 * w + 1, 10 * h + 1);
    for (int a = 0; a < w; a++) {
        for (int b = 0; b < h; b++) {
            if (b == 0) {
                for (int c = 0; c < 10; c++) {
                    if ((10 * a + c < 1) || (10 * a + c > 9)) {
                        HSLAPixel & pixel = output->getPixel(10 * a + c, 0);
                        pixel.l = 0;
                    }
                }
            }
            if (a == 0) {
                for (int d = 0; d < 10; d++) {
                    HSLAPixel & pixel = output->getPixel(0, 10 * b + d);
                    pixel.l = 0;
                }
            }
            if (!canTravel(a, b, 0)) {
                for (int e = 0; e < 11; e++) {
                    HSLAPixel & pixel = output->getPixel(10 * (a + 1), 10 * b + e);
                    pixel.l = 0;
                }
            }
            if (!canTravel(a, b, 1)) {
                for (int f = 0; f < 11; f++) {
                    HSLAPixel & pixel = output->getPixel(10 * a + f, 10 * (b + 1));
                    pixel.l = 0;
                }
            }
        }
    }
    return output;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* output = drawMaze();
    vector<int> solutions = solveMaze();
    pair<int, int> point(5, 5);
    for (auto x : solutions) {
        if (x == 0) {
            for (int a = 0; a < 10; a++) {
                HSLAPixel & pixel = output->getPixel(point.first, point.second);
                pixel.l = 0.5;
                pixel.h = 0;
                pixel.s = 1.0;
                point.first++;
            }
        } else if (x == 1) {
            for (int b = 0; b < 10; b++) {
                HSLAPixel & pixel = output->getPixel(point.first, point.second);
                pixel.l = 0.5;
                pixel.h = 0;
                pixel.s = 1.0;
                point.second++;
            }
        } else if (x == 2) {
            for (int c = 0; c < 10; c++) {
                HSLAPixel & pixel = output->getPixel(point.first, point.second);
                pixel.l = 0.5;
                pixel.h = 0;
                pixel.s = 1.0;
                point.first--;
            }
        } else if (x == 3) {
            for (int d = 0; d < 10; d++) {
                HSLAPixel & pixel = output->getPixel(point.first, point.second);
                pixel.l = 0.5;
                pixel.h = 0;
                pixel.s = 1.0;
                point.second--;
            }
        }
    }
    HSLAPixel & pixel = output->getPixel(point.first, point.second);
    pixel.l = 0.5;
    pixel.h = 0;
    pixel.s = 1.0;
    point.first = point.first - 4;
    point.second = point.second + 5;
    for (int i = point.first; i < point.first + 9; i++) {
        HSLAPixel & pixel = output->getPixel(i, 10 * h);
        pixel.l = 1.0;
    }
    return output;
}