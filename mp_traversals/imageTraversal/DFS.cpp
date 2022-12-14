#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tol_ = tolerance;
  visited_.resize(png_.width());
  for (unsigned a = 0; a < visited_.size(); a++) {
    visited_[a].resize(png_.height());
    for (unsigned b = 0; b < visited_[a].size(); b++) {
      visited_[a][b] = false;
    }
  }
  s_.push(start);
  visited_[start.x][start.y] = true;
}

DFS::~DFS() {}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS * begin_DFS = new DFS(png_, start_, tol_);
  return ImageTraversal::Iterator(*begin_DFS, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  s_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point p = s_.top();
  s_.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return s_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return s_.empty();
}

PNG* DFS::getPNG() {
  return &png_;
}

double DFS::getTol() {
  return tol_;
}

bool DFS::isVisited(unsigned x, unsigned y) {
  return visited_[x][y];
}

void DFS::setVisited(unsigned x, unsigned y) {
  visited_[x][y] = true;
}