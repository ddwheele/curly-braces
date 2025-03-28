#include <iostream>
#include <fstream>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>

#include "RRT.h"

using namespace std;

RRT loadYamlToRrt(const string& params_file) {
  // Load the YAML file
  YAML::Node config = YAML::LoadFile(params_file);

  double stepSize = config["step_size"].as<double>();
  // Read in start and goal points
  double startx = config["start"]["x"].as<double>();
  double starty = config["start"]["y"].as<double>();
  double goalx = config["goal"]["x"].as<double>();
  double goaly = config["goal"]["y"].as<double>();
  shared_ptr<RrtNode> start = make_shared<RrtNode>(startx, starty);
  shared_ptr<RrtNode> goal = make_shared<RrtNode>(goalx, goaly);

  // Read in obstacles
  vector<Obstacle> obstacles;
  for (const auto& obstacle : config["obstacles"]) {
    double x1 = obstacle["x1"].as<double>();
    double y1 = obstacle["y1"].as<double>();
    double x2 = obstacle["x2"].as<double>();
    double y2 = obstacle["y2"].as<double>();
    obstacles.emplace_back(x1, y1, x2, y2);
  }
  cout << "Finished reading params_file"<< endl;
  cout << "stepSize = " << stepSize << endl;

  return RRT(std::move(start), std::move(goal), std::move(obstacles), stepSize);
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

  RRT rrt = loadYamlToRrt(params_file);
  rrt.findPath();
  return 0;
}
