#include <iostream>
#include <fstream>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>

#include "RRT.hpp"

using namespace std;

void loadFromYaml() {
    // Load the YAML file
    YAML::Node config = YAML::LoadFile("../src/params.yaml");


    // Access start and goal points
    Point start = { config["start"]["x"].as<float>(), config["start"]["y"].as<float>() };
    Point goal = { config["goal"]["x"].as<float>(), config["goal"]["y"].as<float>() };

  // Output the start, goal, and obstacles
    std::cout << "Start: (" << start.x << ", " << start.y << ")" << std::endl;
    std::cout << "Goal: (" << goal.x << ", " << goal.y << ")" << std::endl;

}

int main() {
  RRT rrt;
//  rrt.printSomething();

  loadFromYaml();
  cout << "Estoy terminado" << endl;
  return 0;
}
