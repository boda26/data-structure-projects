#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() :
  traversal_(), is_finished(true)
{
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point start) 
	:traversal_(&traversal), start_(start), is_finished(false) {
	curr_ = traversal.peek();
}

ImageTraversal::Iterator::~Iterator() {
  if (traversal_ != NULL) {
    delete traversal_;
    traversal_ = NULL;
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point curr = traversal_->pop();
  traversal_->setVisited(curr.x, curr.y);
  PNG* currPNG = traversal_->getPNG();
  cs225::HSLAPixel & startPixel = currPNG->getPixel(start_.x, start_.y);
  double tol = traversal_->getTol();
  Point right = Point(curr.x + 1, curr.y);
  Point down = Point(curr.x, curr.y + 1);
  Point left = Point(curr.x - 1, curr.y);
  Point up = Point(curr.x, curr.y - 1);

  if (right.x < currPNG->width()) {
    cs225::HSLAPixel & p1 = currPNG->getPixel(right.x, right.y);
    if (calculateDelta(startPixel, p1) < tol) {
      traversal_->add(right);
    }
  }
  if (down.y < currPNG->height()) {
    cs225::HSLAPixel & p2 = currPNG->getPixel(down.x, down.y);
    if (calculateDelta(startPixel, p2) < tol) {
      traversal_->add(down);
    }
  }
  if (left.x < currPNG->width()) {
    cs225::HSLAPixel & p3 = currPNG->getPixel(left.x, left.y);
    if (calculateDelta(startPixel, p3) < tol) {
      traversal_->add(left);
    }
  }
  if (up.y < currPNG->height()) {
    cs225::HSLAPixel & p4 = currPNG->getPixel(up.x, up.y);
    if (calculateDelta(startPixel, p4) < tol) {
      traversal_->add(up);
    }
  }
  while ((!(traversal_->empty())) && (traversal_->isVisited(traversal_->peek().x, traversal_->peek().y))) {
      traversal_->pop();
  }
  if (traversal_->empty()) {
    is_finished = true;
    return *this;
  }
  curr_ = traversal_->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (this->is_finished == other.is_finished) {
    return false;
  } else {
    return true;
  }
}

ImageTraversal::~ImageTraversal() {}

