/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  flow_ = g_;
  residual_ = g_;
  maxFlow_ = 0;
  for (Vertex a : flow_.getVertices()) {
    for (Vertex b : flow_.getAdjacent(a)) {
      flow_.setEdgeWeight(a, b, 0);
      flow_.setEdgeLabel(a, b, a + b);
    }
  }
  for (Vertex c : residual_.getVertices()) {
    for (Vertex d : residual_.getAdjacent(c)) {
      residual_.insertEdge(d, c);
      residual_.setEdgeWeight(d, c, 0);
      residual_.setEdgeLabel(c, d, c + d);
      residual_.setEdgeLabel(d, c, d + c);
    }
  }
  for (Vertex e : startingGraph.getVertices()) {
    flow_.insertVertex(e);
    residual_.insertVertex(e);
  }
  for (Edge i : startingGraph.getEdges()) {
    flow_.insertEdge(i.source, i.dest);
    flow_.setEdgeWeight(i.source, i.dest, 0);
    residual_.insertEdge(i.source, i.dest);
    residual_.setEdgeWeight(i.source, i.dest, startingGraph.getEdgeWeight(i.source, i.dest));
    residual_.insertEdge(i.dest, i.source);
    residual_.setEdgeWeight(i.dest, i.source, 0);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  if (path.size() < 2) {
    return 0;
  }
  int minWeight = residual_.getEdgeWeight(path[0], path[1]);
  for (unsigned i = 1; i < path.size() - 1; i++) {
    int currWeight = residual_.getEdgeWeight(path[i], path[i + 1]);
    if (currWeight < minWeight) {
      minWeight = currWeight;
    }
  }
  return minWeight;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  vector<Vertex> path;
  while (findAugmentingPath(source_, sink_, path)) {
    int cap = pathCapacity(path);
    maxFlow_ += cap;
    for (unsigned i = 0; i < path.size() - 1; i++) {
      if (flow_.edgeExists(path[i], path[i + 1])) {
        flow_.setEdgeWeight(path[i], path[i + 1], flow_.getEdgeWeight(path[i], path[i + 1]) + cap);
      } else {
        flow_.setEdgeWeight(path[i+1], path[i], flow_.getEdgeWeight(path[i + 1], path[i]) - cap);
      }
      residual_.setEdgeWeight(path[i], path[i + 1], residual_.getEdgeWeight(path[i], path[i + 1]) - cap);
      residual_.setEdgeWeight(path[i + 1], path[i], residual_.getEdgeWeight(path[i + 1], path[i]) + cap);
    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

