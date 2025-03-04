#include <cmath>
#include <iostream>
#include <fstream>
#include <ranges>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>

#include "AStar.h"
#include "StarNode.h"
#include "Utils.h"

using namespace std;

vector<shared_ptr<StarNode>> createGraph(int num) {
  // create nodes
  vector<shared_ptr<StarNode>> nodes;
  shared_ptr<StarNode> start = make_shared("Start", 1,1);
  shared_ptr<StarNode> goal = make_shared("Goal", Utils::WIDTH-1,Utils::HEIGHT-1);
  nodes.push_back(start);
  nodes.push_back(goal);

  for(int i=0; i<num; i++) {
    nodes.push_back(make_shared(string(1, 'A' + num)));
  }

  // every node needs some neighbors
  int REQUIRED_NEIGHBORS = 3;ß
  std::srand(std::time(0));
  for(auto nd : nodes) {
    int neigh = REQUIRED_NEIGHBORS;
    while(neigh) {
      int index = std::rand() % (num+2);
      bool added = nd->addNeighbor(nodes[index]);
      if(added) {
        neigh--;
      }
    }

  }

}

AStar loadYamlToAStar(string params_file) {
  // Load the YAML file
  YAML::Node config = YAML::LoadFile(params_file);

  unordered_map<string,shared_ptr<AStarNode>> node_map;
  for (const auto& node : config["nodes"]) {
    string name = node["name"].as<string>();
    double x = node["x"].as<double>();
    double y = node["y"].as<double>();
    shared_ptr<AStarNode> nd = make_shared<AStarNode>(name, x, y);
    node_map[name] = nd;
  }

  vector<shared_ptr<AStarNode>> nodes(std::views::values(node_map).begin(), std::views::values(node_map).end());

	vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>> edges;
	vector<double> weights;

  for (const auto& edge : config["edges"]) {
    string src = edge["s"].as<string>();
    string dst = edge["d"].as<string>();
    double w = edge["w"].as<double>();

    edges.push_back({node_map[src], node_map[dst]});
    weights.push_back(w);
  }

  AStar astar(nodes, edges, weights);
  return astar;
}

int main(int argc, char** argv) {
  

  AStar astar = loadYamlToAStar(params_file);
  astar.findPath();
	return 0;
}