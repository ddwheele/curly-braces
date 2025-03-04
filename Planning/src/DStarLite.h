#ifndef D_STAR_LITE
#define D_STAR_LITE

#include <queue>
#include "DStarNode.h"
#include "PathPlanner.h"
//#include "DrawMapDStarLite.h"

class DrawMapDStarLite;

class DStarLite : public PathPlanner {
public:
  DStarLite(vector<shared_ptr<DStarNode>> node);
  void findPath() override;

  // don't think we need this anymore
  // Custom comparator for shared_ptr<DStarNode> (min-heap)
  struct DStarNodePtrCompare {
      bool operator()(const std::shared_ptr<DStarNode>& lhs, const std::shared_ptr<DStarNode>& rhs) const {
          return *lhs > *rhs;  // Delegate to DStarNode's operator<
      }
  };

private: 
  std::unique_ptr<DrawMapDStarLite> drawMap;

  vector<shared_ptr<DStarNode>> nodes;
  shared_ptr<DStarNode> goal;
  shared_ptr<DStarNode> start;
  float key_modifier;

  UpdateableMinHeap<shared_ptr<DStarNode>> openSet;

};



#endif