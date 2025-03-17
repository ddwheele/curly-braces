#ifndef ABSTRACT_D_STAR_LITE_H
#define ABSTRACT_D_STAR_LITE_H

#include <queue>
#include "DStarNode.h"
#include "AbstractDStarLite.h"
#include "../IDrawMap.h"
#include "UpdateableMinHeap.h"

#include "../PathPlanner.h"

// Base of both DStarLite and DStarLiteOptimized
class AbstractDStarLite : public PathPlanner {
public:
  AbstractDStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
			const vector<vector<shared_ptr<DStarNode>>>& edges, 
			const vector<double>& weights,
			const shared_ptr<DStarNode>& _start,
			const shared_ptr<DStarNode>& _goal);

  AbstractDStarLite(AbstractDStarLite&&) noexcept = default;
  AbstractDStarLite& operator=(AbstractDStarLite&&) noexcept = default;
	virtual ~AbstractDStarLite() = default;

  const vector<shared_ptr<DStarNode>>& getNodes() const;
  const vector<shared_ptr<DStarNode>> getNodeNeighbors(const shared_ptr<DStarNode>& node) const;
  const shared_ptr<DStarNode>& getStartNode() const;

  const unordered_set<shared_ptr<DStarNode>>& getCurrentObstacles() const;



  const unordered_map<shared_ptr<DStarNode>, unordered_map<shared_ptr<DStarNode>,double>>& getCostMap() const;

  void drawMap() const;
  void drawMapAndWait() const;
  void printState() const;

protected:
  virtual void initialize() = 0;
  virtual void updateVertex(const shared_ptr<DStarNode>&node) = 0;
  virtual void computeShortestPath() = 0;

  unique_ptr<IDrawMap> dStarDrawMap;

  vector<shared_ptr<DStarNode>> nodes;
  shared_ptr<DStarNode> goal;
  shared_ptr<DStarNode> start;
  float key_modifier;

  // needed to update key_modifier
  shared_ptr<DStarNode> lastStart;

  // the set of edges, with their weights
  unordered_map<shared_ptr<DStarNode>, unordered_map<shared_ptr<DStarNode>,double>> cost;

  // the locally inconsistent vertices
  UpdateableMinHeap<shared_ptr<DStarNode>> openSet;


  // nodes currently denoted as obstacles
  unordered_set<shared_ptr<DStarNode>> currentObstacles;

  static const int maxSteps = 1000;

  bool PRINT_DEBUG = false;

  // for interactive
  void doObstacleUpdates();

    // turn a node into an obstacle
  virtual void placeNamedObstacle(const string& obsName, double weight= 10000) = 0;

  // make a node not an obstacle anymore
  virtual void removeNamedObstacle(const string& obsName, double weight= 10000) = 0;
};


#endif