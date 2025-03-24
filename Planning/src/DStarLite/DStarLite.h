#ifndef D_STAR_LITE
#define D_STAR_LITE

#include <queue>
#include "DStarNode.h"
#include "AbstractDStarLite.h"
#include "../IDrawMap.h"
#include "UpdateableMinHeap.h"

class DrawMapDStarLite;

/** 
 * Finds the shortest path through the given undirected graph from start node to given goal node,
 * using the original D* Lite algorithm
 */
class DStarLite : public AbstractDStarLite {
public:
  DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
			const vector<vector<shared_ptr<DStarNode>>>& edges, 
			const vector<double>& weights,
			const shared_ptr<DStarNode>& _start,
			const shared_ptr<DStarNode>& _goal);

  DStarLite(DStarLite&&) noexcept = default;
  DStarLite& operator=(DStarLite&&) noexcept = default;

  // call this to run D* Lite if you have specified a list of timed obstacles
  void findPath() override;
  // call this to run D* Lite and specify obstacles interactively
  void findPathInteractive();

  // preset which node will be an obstacle at which time (vector index = time)
  void setTimedObstacles(vector<shared_ptr<DStarNode>>& timedObstacles);

  // turn a node into an obstacle
  void placeNamedObstacle(const string& obsName, const double weight = 10000) override;

  // make a node not an obstacle anymore
  void removeNamedObstacle(const string& obsName, const double weight = 10000) override;

private: 
  // which node the obstacle is on a time i+1;
  vector<shared_ptr<DStarNode>> timedObstacles;

  void initialize() override;

  // make sure RHS points to the best neighbor; if inconsistent, put on open queue
  void updateVertex(const shared_ptr<DStarNode>&node) override;
  
  // process open set until Start is consistent, and all nodes with smaller keys than Start are processed
  void computeShortestPath() override;

  // for non-interactive
  // findPath() calls this to apply the specified timed obstacles to the graph
  void applyTimedObstacles(int &obstacleTime);

  // add weight to all edges to obstacle
  void updateEdgesTo(shared_ptr<DStarNode>& obstacle, const double weight) override;
};

#endif