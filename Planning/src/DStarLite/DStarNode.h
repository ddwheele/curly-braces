#ifndef D_STAR_NODE_H
#define D_STAR_NODE_H

#include <iomanip>
#include <format>
#include "StarNode.h"
#include "Utils.h"


using namespace std;

class DStarNode : public StarNode {
public:
  struct Key {
    double k1;
    double k2;
    // storing the following just to print for debugging
    double gn;
    double rhs;
    double hn;
    double km;

    Key() : k1(numeric_limits<double>::max()), k2(numeric_limits<double>::max()) {}

    Key(double _k1, double _k2) : k1(_k1), k2(_k2) { }

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

    inline bool operator<(const Key& other) { return k1 < other.k1 || Utils::equals(k1,other.k1) && k2 < other.k2; }
    inline bool operator>(const Key& other) { return k1 > other.k1 || Utils::equals(k1,other.k1) && k2 > other.k2; }
    inline bool operator==(const Key& other) { return Utils::equals(k1,other.k1) && Utils::equals(k2,other.k2); }
    inline bool operator!=(const Key& other) { return !(*this==other); }

    // option 2: define hash inside the class itself
    struct Hash {
        size_t operator()(const Key& k) const {
            size_t h1 = std::hash<double>{}(k.k1);
            size_t h2 = std::hash<double>{}(k.k2);
            return h1 ^ (h2 << 1);
        }
    };
  };

  DStarNode(string _name, double _x, double _y);
  DStarNode(string _name);

  DStarNode(char _name, double _x, double _y);
  DStarNode(char _name);

  // make sure hn calculated frst!
  Key computeKey(double km); // takes a key modifier

  Key getKey() const;

  bool gnEqualsRhs() const;

  double getRhs() const;
  void setRhs(double _rhs);

  bool operator<(const DStarNode& other) const;
  bool operator>(const DStarNode& other) const;

  // XXX defeats the whole purpose of inheritance - there's really no better way to do this????
  bool addDStarNeighbor(shared_ptr<DStarNode> n);
  const vector<shared_ptr<DStarNode>>& getDStarNeighbors() const;
  const vector<shared_ptr<DStarNode>>& getPredecessors() const;
  const vector<shared_ptr<DStarNode>>& getSuccessors() const;

  friend std::ostream& operator<<(std::ostream& os, const DStarNode& dsn) {
    if(dsn.onOpenSet) {
      return os << std::fixed << std::setprecision(2) << dsn.name
      << ": (" << dsn.x << "," << dsn.y
      << "), gn = " << Utils::infString(dsn.gn) << ", rhs = " << Utils::infString(dsn.rhs)
      << ", key= {" << dsn.key.toString() << "}";
    }
    return os << std::fixed << std::setprecision(2) << dsn.name
      << ": (" << dsn.x << "," << dsn.y
      << "), gn = " << Utils::infString(dsn.gn) << ", rhs = " << Utils::infString(dsn.rhs);
  }

private:
  Key key;
  double rhs;
  const int maxIterations = 1000;

  void initGnRhs();

  // this is only to help with debugging output
  bool onOpenSet = false;

  // XXX truely cringe-worthy not to be able to use neighbors
  const vector<shared_ptr<DStarNode>> dStarNeighbors;
};

#endif