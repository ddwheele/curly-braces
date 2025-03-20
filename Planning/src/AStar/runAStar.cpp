#include <iostream>
#include <fstream>
#include <ranges>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>


#include "AStar.h"
#include "AStarNode.h"

using namespace std;

AStar loadYamlToAStar(const string& params_file) {
  // Load the YAML file
  YAML::Node config = YAML::LoadFile(params_file);

  unordered_map<string,shared_ptr<AStarNode>> node_map;
  for (const auto& node : config["nodes"]) {
    string name = node["name"].as<string>();
    double x = node["x"].as<double>();
    double y = node["y"].as<double>();
    node_map[name] = make_shared<AStarNode>(name, x, y);
  }
  vector<shared_ptr<AStarNode>> nodes(std::views::values(node_map).begin(), std::views::values(node_map).end());

	vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>> edges;
	vector<double> weights;

  for (const auto& edge : config["edges"]) {
    string src = edge["s"].as<string>();
    string dst = edge["d"].as<string>();
    double w = edge["w"].as<double>();

    edges.emplace_back(node_map[src], node_map[dst]);
    weights.push_back(w);
  }
  return AStar(std::move(nodes), std::move(edges), std::move(weights));
}

int main(int argc, char** argv) {
  // Check if a command line argument was provided
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_yaml_file>" << std::endl;
    return 1;
  }

  std::string params_file = argv[1];

  // Check if the file exists
  std::ifstream file(params_file);
  if (!file) {
    std::cerr << "Error: Cannot open file " << params_file << std::endl;
    return 1;
  }

  AStar astar = loadYamlToAStar(params_file);
  astar.findPath();
	return 0;
}