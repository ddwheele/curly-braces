#ifndef D_STAR_NODE_H
#define D_STAR_NODE_H

#include <iomanip>
#include <format>
#include "../StarNode.h"
#include "../Utils.h"


using namespace std;

/**
 * Node class suitable for use in D* Lite algorithm
 * Keeps track of its Key
 */
class DStarNode : public StarNode {
public:
  /**
   * Class for D* Lite key
   */
  struct Key {
    double k1;
    double k2;
    // storing the following just to print for debugging
    double gn;
    double rhs;
    double hn;
    double km;

    // initialize to inf
    Key() : k1(numeric_limits<double>::max()), k2(numeric_limits<double>::max()) {}

    Key(double _k1, double _k2) : k1(_k1), k2(_k2) { }

    // set values of key components
    void update(double _gn, double _rhs, double _hn, double _km) {
      gn = _gn;
      rhs = _rhs;
      hn = _hn;
      km = _km;

      k1 = min(gn, rhs) + hn + km;
      k2 = min(gn, rhs);
    }

    void printMe() const {
      cout << "k1 = " << Utils::infString(k1) << ", k2 = " << Utils::infString(k2) << endl;
    }

    string toString() const {
      return "k1 = min(" + Utils::infString(gn) + "," + Utils::infString(rhs) + ") + " + std::format("{:.2f}", hn) + " + " + std::format("{:.2f}", km) + " = " + Utils::infString(k1)
        + "; k2 = min(" + Utils::infString(gn) + "," + Utils::infString(rhs) + ") = " + Utils::infString(k2);
    }

    string toShortString() const {
      return "(" + Utils::infString(k1) + ", " + Utils::infString(k2) + ")";
    }

    // Override comparisons so Key can be used in Min Heap
    inline bool operator<(const Key& other) { return k1 < other.k1 || Utils::equals(k1,other.k1) && k2 < other.k2; }
    inline bool operator>(const Key& other) { return k1 > other.k1 || Utils::equals(k1,other.k1) && k2 > other.k2; }
    inline bool operator==(const Key& other) { return Utils::equals(k1,other.k1) && Utils::equals(k2,other.k2); }
    inline bool operator!=(const Key& other) { return !(*this==other); }


    struct Hash {
        size_t operator()(const Key& k) const {
            size_t h1 = std::hash<double>{}(k.k1);
            size_t h2 = std::hash<double>{}(k.k2);
            return h1 ^ (h2 << 1);
        }
    };
  };
  // create node at given coordinates
  DStarNode(const string& _name, const double _x, const double _y);
  DStarNode(const char _name, const double _x, const double _y);

  // create node at random coordinates
  DStarNode(const string& _name);
  DStarNode(const char _name);

  // make sure hn calculated frst!
  // takes a key modifier, updates key based on current gn, rhs, and hn values
  Key computeKey(const double km); 

  Key getKey() const;

  bool gnEqualsRhs() const;

  double getRhs() const;
  void setRhs(const double _rhs);

  bool isInOpenSet() const;
  void setInOpenSet(const bool inSet);

  bool operator<(const DStarNode& other) const;
  bool operator>(const DStarNode& other) const;

  // passing by value because this Node cares about its neighbors (wants to share ownership)
  bool addDStarNeighbor(shared_ptr<DStarNode> n);
  const vector<shared_ptr<DStarNode>>& getDStarNeighbors() const;
  const vector<shared_ptr<DStarNode>>& getPredecessors() const;
  const vector<shared_ptr<DStarNode>>& getSuccessors() const;

  friend std::ostream& operator<<(std::ostream& os, const DStarNode& dsn) {
    if(dsn.inOpenSet) {
      return os << std::fixed << std::setprecision(2) << dsn.name
      << ": gn = " << Utils::infString(dsn.gn) << ", rhs = " << Utils::infString(dsn.rhs)
      << ", key= {" << dsn.key.toString() << "}";
    }
    return os << std::fixed << std::setprecision(2) << dsn.name
      << ": gn = " << Utils::infString(dsn.gn) << ", rhs = " << Utils::infString(dsn.rhs);
  }

private:
  Key key;
  double rhs;

  void initGnRhs();

  // this is only to help with debugging output
  bool inOpenSet = false;

  // XXX truely horrendous not to be able to use neighbors
  const vector<shared_ptr<DStarNode>> dStarNeighbors;
};

#endif