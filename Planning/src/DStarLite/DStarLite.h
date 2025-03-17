#ifndef D_STAR_LITE
#define D_STAR_LITE

#include <queue>
#include "DStarNode.h"
#include "AbstractDStarLite.h"
#include "../IDrawMap.h"
#include "UpdateableMinHeap.h"

class DrawMapDStarLite;

class DStarLite : public AbstractDStarLite {
public:
  DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
			const vector<vector<shared_ptr<DStarNode>>>& edges, 
			const vector<double>& weights,
			const shared_ptr<DStarNode>& _start,
			const shared_ptr<DStarNode>& _goal);

  DStarLite(DStarLite&&) noexcept = default;
  DStarLite& operator=(DStarLite&&) noexcept = default;

  void findPath() override;
  void findPathInteractive();
  void setTimedObstacles(vector<shared_ptr<DStarNode>>& timedObstacles);

  // turn a node into an obstacle
  void placeNamedObstacle(const string& obsName, double weight = 1000) override;

  // make a node not an obstacle anymore
  void removeNamedObstacle(const string& obsName, double weight = 10000) override;

private: 
  // which node the obstacle is on a time i+1;
  vector<shared_ptr<DStarNode>> timedObstacles;

  void initialize() override;
  void updateVertex(const shared_ptr<DStarNode>&node) override;
  void computeShortestPath() override;

  // for non-interactive
  void applyTimedObstacles(int &obstacleTime);

  // add weight to all edges to obstacle
  void updateEdgesTo(shared_ptr<DStarNode>& obstacle, double weight) override;
};

#endif