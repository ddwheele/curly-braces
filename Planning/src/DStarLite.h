#ifndef D_STAR_LITE
#define D_STAR_LITE

#include <queue>



class DStarLite : public PathPlanner {
public:
  DStarLite(vector<shared_ptr<StarNode>> node);
  void findPath() override;

private: 
  DrawMapDStarLite drawMap;

  vector<shared_ptr<StarNode>> nodes;
  shared_ptr<StarNode> goal;
  shared_ptr<StarNode> start;
  float key_modifier;

  priority_queue<shared_ptr<StarNode>> openQ;
  unordered_map<shared_ptr<StarNode>, Key> lookups;

};



#endif