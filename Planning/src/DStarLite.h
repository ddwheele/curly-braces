#ifndef D_STAR_LITE
#define D_STAR_LITE

#include <queue>
#include "DStarNode.h"
#include "PathPlanner.h"
#include "DrawMapDStarLite.h"


class DStarLite : public PathPlanner {
public:
  DStarLite(vector<shared_ptr<DStarNode>> node);
  void findPath() override;

  // Custom comparator for shared_ptr<DStarNode> (min-heap)
  struct DStarNodePtrCompare {
      bool operator()(const std::shared_ptr<DStarNode>& lhs, const std::shared_ptr<DStarNode>& rhs) const {
          return *lhs > *rhs;  // Delegate to DStarNode's operator<
      }
  };

private: 
  DrawMapDStarLite drawMap;

  vector<shared_ptr<DStarNode>> nodes;
  shared_ptr<DStarNode> goal;
  shared_ptr<DStarNode> start;
  float key_modifier;

  // TODO write test to confirm that this does the right thing (returns D*Node with smallest key)
  priority_queue<shared_ptr<DStarNode>,vector<shared_ptr<DStarNode>>, DStarNodePtrCompare> openQ;
 // unordered_map<shared_ptr<DStarNode>, Key> lookups;

};



#endif