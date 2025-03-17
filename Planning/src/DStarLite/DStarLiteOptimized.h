#ifndef D_STAR_LITE_OPTIMIZED
#define D_STAR_LITE_OPTIMIZED

#include <queue>
#include "DStarNode.h"
#include "AbstractDStarLite.h"
#include "../IDrawMap.h"
#include "UpdateableMinHeap.h"

class DrawMapDStarLite;

class DStarLiteOptimized : public AbstractDStarLite {
public:
  DStarLiteOptimized(const vector<shared_ptr<DStarNode>>& _nodes,
			const vector<vector<shared_ptr<DStarNode>>>& edges, 
			const vector<double>& weights,
			const shared_ptr<DStarNode>& _start,
			const shared_ptr<DStarNode>& _goal);
  void findPath() override;

  void findPathInteractive();

    // add weight to all edges to obstacle
  void placeObstacle(shared_ptr<DStarNode>& obstacle, double weight = 10000);
  // remove weight from all edges to obstacle
  void removeObstacle(shared_ptr<DStarNode>& noObstacle, double weight = 10000);

private:
  void initialize() override;
  void updateVertex(const shared_ptr<DStarNode>&node) override;
  void computeShortestPath() override;

  // turn a node into an obstacle
  void placeNamedObstacle(const string& obsName, double weight = 10000) override;

  // make a node not an obstacle anymore
  void removeNamedObstacle(const string& obsName, double weight = 10000) override;
};

#endif
