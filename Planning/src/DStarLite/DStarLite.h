#ifndef D_STAR_LITE
#define D_STAR_LITE

#include <queue>
#include "DStarNode.h"
#include "PathPlanner.h"
#include "IDrawMap.h"
#include "UpdateableMinHeap.h"

class DrawMapDStarLite;

class DStarLite : public PathPlanner {
public:
  DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
			const vector<vector<shared_ptr<DStarNode>>>& edges, 
			const vector<double>& weights,
			const shared_ptr<DStarNode>& _start,
			const shared_ptr<DStarNode>& _goal);
  void findPath() override;

  void initialize();
  void updateVertex(const std::shared_ptr<DStarNode>&node);
  void computeShortestPath();
  void recalculateNode(shared_ptr<DStarNode>& changed);

  // add weight to all edges to obstacle
  void placeObstacle(shared_ptr<DStarNode>& obstacle, int weight = 10000);
  // remove weight from all edges to obstacle
  void removeObstacle(shared_ptr<DStarNode>& noObstacle, int weight = 10000);

  void setTimedObstacles(vector<shared_ptr<DStarNode>>& timedObstacles);

  const vector<shared_ptr<DStarNode>>& getNodes() const;

  void drawMap() const;

  void printState() const;

  // // don't think we need this anymore
  // // Custom comparator for shared_ptr<DStarNode> (min-heap)
  // struct DStarNodePtrCompare {
  //     bool operator()(const std::shared_ptr<DStarNode>& lhs, const std::shared_ptr<DStarNode>& rhs) const {
  //         return *lhs > *rhs;  // Delegate to DStarNode's operator<
  //     }
  // };

private: 
  unique_ptr<IDrawMap> dStarDrawMap;

  vector<shared_ptr<DStarNode>> nodes;
  shared_ptr<DStarNode> goal;
  shared_ptr<DStarNode> start;
  float key_modifier;

  unordered_map<shared_ptr<DStarNode>, unordered_map<shared_ptr<DStarNode>,double>> cost;

  // the locally inconsistent vertices
  UpdateableMinHeap<shared_ptr<DStarNode>> openSet;

  const int maxSteps = 1000;

  // which node the obstacle is on a time i+1;
  vector<shared_ptr<DStarNode>> timedObstacles;
  bool PRINT_DEBUG = false;

};

#endif