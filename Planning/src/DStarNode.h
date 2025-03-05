#ifndef D_STAR_NODE_H
#define D_STAR_NODE_H

#include "StarNode.h"
#include "Utils.h"

using namespace std;

class DStarNode : public StarNode {
public:
  DStarNode(string _name, double _x, double _y);
  DStarNode(string _name);

  void computeKey(double km); // takes a key modifier

  Key getKey() const;

  bool addNeighbor(shared_ptr<DStarNode> n);
  unordered_set<shared_ptr<DStarNode>> getNeighbors() const;

  bool gnEqualsRhs() const;

  double getRhs() const;
  void setRhs(double _rhs);

  bool operator<(const DStarNode& other) const;
  bool operator>(const DStarNode& other) const;

private:
  struct Key {
    double k1;
    double k2;

    Key() : k1(numeric_limits<double>::max()), k2(numeric_limits<double>::max()) {}

    Key(double _k1, double _k2) : k1(_k1), k2(_k2) { }

    set(double _k1, double _k2) {
      k1 = _k1;
      k2 = _k2;
    }

    inline bool operator<(const Key& l, const Key& r) { return l.k1 < l.k2 || Utils::equal(l.k1,r.k1) && l.k2 < r.k2 }
    inline bool operator>(const Key& l, const Key& r) { return l.k1 > l.k2 || Utils::equal(l.k1,r.k1) && l.k2 > r.k2 }
    inline bool operator==(const Key& l, const Key& r) { return Utils::equal(l.k1,r.k1) && Utils::equal(l.k2,r.k2) }
    inline bool operator!=(const Key& l, const Key& r) { return !(l==r) }

    // // option 2: define hash inside the class itself
    // struct Hash {
    //     size_t operator()(const Key& k) const {
    //         size_t h1 = std::hash<double>{}(k.k1);
    //         size_t h2 = std::hash<double>{}(k.k2);
    //         return h1 ^ (h2 << 1);
    //     }
    // };
  };

  Key key;
  double rhs;

  unordered_set<shared_ptr<DStarNode>> neighbors;
};

// Option 1: Specialize std::hash for DStarLite::Key **outside** the class
namespace std {
    template <> 
    struct hash<DStarNode::Key> {
        size_t operator()(const DStarNode::Key& k) const {
            size_t h1 = std::hash<double>{}(k.k1);
            size_t h2 = std::hash<double>{}(k.k2);
            return h1 ^ (h2 << 1);
        }
    };
}





#endif