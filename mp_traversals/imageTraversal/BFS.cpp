#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;
using namespace std;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tol_ = tolerance;
  visited_ = vector<vector<bool>>();
  visited_.resize(png_.width());
  for (unsigned a = 0; a < png_.width(); a++) {
    visited_[a] = vector<bool>();
    visited_[a].resize(png_.height());
    for (unsigned b = 0; b < png.height(); b++) {
      visited_[a][b] = false;
    }
  }
  q_.push(start_);
  visited_[start.x][start.y] = true;
}

BFS::~BFS() {}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS * begin_BFS = new BFS(png_, start_, tol_);
  return ImageTraversal::Iterator(*begin_BFS, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  q_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point p = q_.front();
  q_.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return q_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return q_.empty();
}

PNG* BFS::getPNG() {
  return &png_;
}

double BFS::getTol() {
  return tol_;
}

bool BFS::isVisited(unsigned x, unsigned y) {
  return visited_[x][y];
}

void BFS::setVisited(unsigned x, unsigned y) {
  visited_[x][y] = true;
}