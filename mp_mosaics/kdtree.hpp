/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] > second[curDim]) {
      return false;
    } else {
      return first < second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double curr_sum = 0.0;
    double potential_sum=0.0;
    for (int i = 0; i < Dim; i++) {
      curr_sum = curr_sum + (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
      potential_sum = potential_sum + (potential[i] - target[i]) * (potential[i] - target[i]);
    }
    if (curr_sum > potential_sum) {
      return true;
    } else if (curr_sum < potential_sum) {
      return false;
    } else {
      return potential < currentBest;
    }
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, int dimension, unsigned l, unsigned r, unsigned index) {
  Point<Dim> indexValue = list[index];
  Point<Dim> temp = list[r];
  list[r] = list[index];
  list[index] = temp;
  unsigned k = l;
  for (unsigned i = l; i < r; i++) {
    if (smallerDimVal(list[i], indexValue, dimension)) {
      temp = list[i];
      list[i] = list[k];
      list[k] = temp;
      k++;
    }
  }
  temp = list[k];
  list[k] = list[r];
  list[r] = temp;
  return k;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int dimension, unsigned l, unsigned r, unsigned k) {
  if (l == r) {
    return list[l];
  }
  unsigned pivot = k;
  pivot = partition(list, dimension, l, r, k);
  if (k == pivot) {
    return list[k];
  } else if (k < pivot) {
    return quickSelect(list, dimension, l, pivot - 1, k);
  } else {
    return quickSelect(list, dimension, pivot + 1, r, k);
  }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::build(vector<Point<Dim>>& list, int dimension, unsigned l, unsigned r) {
  if(list.empty()) {
    return NULL;
  }
  if (l < 0 || l >= list.size() || r < 0 || r >= list.size()) {
    return NULL;
  }
  if (r < l) {
    return NULL;
  }
  unsigned med = (l + r) / 2;
  KDTreeNode* subroot = new KDTreeNode(quickSelect(list, dimension % Dim, l, r, med));
  size += 1;
  dimension++;
  subroot->left = build(list, dimension, l, med - 1);
  subroot->right = build(list, dimension, med + 1, r);
  return subroot;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    vector<Point<Dim>> list;
    list.assign(newPoints.begin(), newPoints.end());
    root = build(list, 0, 0, list.size()-1);
}

template <int Dim>
void KDTree<Dim>::copy_(KDTreeNode * subroot, KDTreeNode * other) {
	subroot = new KDTreeNode();
	subroot->point = other->point;
	copy_(subroot->left, other->left);
	copy_(subroot->right, other->right);
}

template <int Dim>
void KDTree<Dim>::clear_(KDTreeNode * subroot) {
	if (subroot == NULL) {
    return;
  }
	if (subroot->left != NULL) {
    clear_(subroot->left);
  }
	if (subroot->right != NULL) {
    clear_(subroot->right);
  }
	delete subroot;
	subroot = NULL;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy_(this->root, other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != NULL) {
    clear_(root);
  }
  copy_(this->root, rhs.root);
  size = rhs.size();
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear_(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return nearestNeighbor(query, 0, root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::nearestNeighbor(const Point<Dim>& query, int dimension, KDTreeNode* subroot) const {
  if (subroot->left == NULL && subroot->right == NULL) {
    return subroot->point;
  }
  Point<Dim> currBest = subroot->point;
  bool wentLeft = false;
  if (smallerDimVal(query, subroot->point, dimension)) {
    if (subroot->left != NULL) {
      currBest = nearestNeighbor(query, (dimension + 1) % Dim, subroot->left);
    } else {
      currBest = nearestNeighbor(query, (dimension + 1) % Dim, subroot->right);
    }
    wentLeft = true;
  } else {
    if (subroot->right != NULL) {
      currBest = nearestNeighbor(query, (dimension + 1) % Dim, subroot->right);
    } else {
      currBest = nearestNeighbor(query, (dimension + 1) % Dim, subroot->left);
    }
  }
  if (shouldReplace(query, currBest, subroot->point)) {
    currBest = subroot->point;
  }
  double radius = 0.0;
  for (int i = 0; i < Dim; i++) {
    radius += (query[i] - currBest[i]) * (query[i] - currBest[i]);
  }
  double splitted = (query[dimension] - subroot->point[dimension]) * (query[dimension] - subroot->point[dimension]);
  if (splitted <= radius) {
    if (wentLeft) {
      if (subroot->right) {
        Point<Dim> newBest = nearestNeighbor(query, dimension, subroot->right);
        if (shouldReplace(query, currBest, newBest)) {
          currBest = newBest;
        }
      }
    } else {
      if (subroot->left) {
        Point<Dim> newBest = nearestNeighbor(query, dimension, subroot->left);
        if (shouldReplace(query, currBest, newBest)) {
          currBest = newBest;
        }
      }
    }
  }
  return currBest;
}