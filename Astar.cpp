#include <iostream>
#include <set>
#include <map>
#include <stdexcept>

using namespace std;

// Compile with `clang++ -std=c++14 Astar.cpp -o Astar`

struct ANode {
  string _name;
  int _index;
  double _x;
  double _y;
  double _hn; // h(n) = heuristic. Admissible -> never overestimate the actual path cost
  // An admissible heuristic never overestimates the actual cost to reach the goal.
  // A consistent heuristic satisfies the condition that the estimated cost from the current 
  // node to the goal node is always less than or equal to the estimated distance from any 
  // neighbouring vertex to the goal, plus the cost of reaching that neighbour.
  double _gn; // g(n) = operating cost = how many units we moved from start node
  shared_ptr<ANode> _parent = nullptr;

  static int _counter;

  ANode(string name, double x, double y) : _name(name), _x(x), _y(y), _index(_counter++) {}

  void computeHeuristic(shared_ptr<ANode> goal) {
    // let's use Euclidean distance for heuristic
    double xdiff = goal->_x - _x;
    double ydiff = goal->_y - _y;
    _hn = sqrt(xdiff*xdiff + ydiff*ydiff);
  }

  double evaluate() const  {
    // f(n) = g(n) + h(n)
    return _gn + _hn;
  }

  // Define operator< for ordering
  bool operator<(const ANode& other) const {
      return evaluate() < other.evaluate();
  }
};
int ANode::_counter = 0;

class AStar {
  private:
    vector<shared_ptr<ANode> > _nodes;
    map<shared_ptr<ANode>, vector<pair<shared_ptr<ANode>,double> > > _adj;
    shared_ptr<ANode> _goal;
    shared_ptr<ANode> _start;
  public:
    AStar(vector<shared_ptr<ANode>> nodes, vector<pair<shared_ptr<ANode>,shared_ptr<ANode>>> edges, vector<double> weights) : _nodes(nodes) {
      if(edges.size() != weights.size()) {
        throw std::invalid_argument("edges and weights must be the same length");
      }
      int n = edges.size();
      for(int i=0; i<n; i++) {
        auto e = edges[i];
        auto e1 = e.first;
        auto e2 = e.second;
        auto w = weights[i];
        _adj[e1].push_back({e2,w});
        _adj[e2].push_back({e1,w});
      }
    }
    
    void findPath(shared_ptr<ANode> start, shared_ptr<ANode> goal){
      _start = start;
      _goal = goal;

      set<shared_ptr<ANode>> closed;

      for(auto n : _nodes) {
        n->computeHeuristic(goal);
      }
      // Using lambda to compare elements.
      auto cmp = [](shared_ptr<ANode> left, shared_ptr<ANode> right) { 
        //cout << left->evaluate() << "<" <<right->evaluate() << "? " << (left->evaluate() < right->evaluate()) <<std::endl;
        return left->evaluate() > right->evaluate(); };
      std::priority_queue<shared_ptr<ANode>,vector<shared_ptr<ANode>>,decltype(cmp)> open(cmp);
      //priority_queue<shared_ptr<ANode>,vector<shared_ptr<ANode>>,greater<>> open;
      open.push(_start);
      while(!open.empty()) {
        auto nd1 = open.top();
        open.pop();
        cout << "Considering " << nd1->_name << ": " << nd1->evaluate() << endl;
        if(nd1 == _goal) {
          break;
        }
        closed.insert(nd1);
        auto neigh = _adj[nd1];
        for(auto& pr: neigh) {
          auto nd2 = pr.first;
          double w = pr.second;
          if(closed.count(nd2)) {
            continue;
          }
          nd2->_gn = nd1->_gn + w; // cost to neighbor = cost to old node + edge length
          nd2->_parent = nd1;
          cout << "Adding " << nd2->_name << ": " << nd2->evaluate() << endl;;
          open.push(nd2);
        }
      }

      shared_ptr<ANode> curr = _goal;
      cout << "I found this path: " << endl;
      while(curr != nullptr) {
        cout << curr->_name << " -> ";
        curr = curr->_parent;
      }
      cout << endl;
    }

};
 
// To execute C++, please define "int main()"
int main() {
  cout << "Creating Node List" << endl;
  vector<shared_ptr<ANode> > nodes;
  vector<pair<shared_ptr<ANode>,shared_ptr<ANode> > > edges ;
  vector<double> weights;

  shared_ptr<ANode> start = make_shared<ANode>("Start", 0,0);
  shared_ptr<ANode> a = make_shared<ANode>("A", 1,1);
  shared_ptr<ANode> b = make_shared<ANode>("B", 1,3);
  shared_ptr<ANode> c = make_shared<ANode>("C", 5,1);
  shared_ptr<ANode> d = make_shared<ANode>("D", 3,3);
  shared_ptr<ANode> goal = make_shared<ANode>("Goal", 3,5);

  nodes.push_back(start);
  nodes.push_back(a);
  nodes.push_back(b);
  nodes.push_back(c);
  nodes.push_back(d);
  nodes.push_back(goal);

  edges.push_back({start,a});
  weights.push_back(2);

  edges.push_back({a,b});
  weights.push_back(2);

  edges.push_back({a,c});
  weights.push_back(4);

  edges.push_back({b,d});
  weights.push_back(2);

  edges.push_back({c,d});
  weights.push_back(4);

  edges.push_back({d,goal});
  weights.push_back(3);

  AStar astar(nodes, edges, weights);
  astar.findPath(start, goal);

  return 0;
}



