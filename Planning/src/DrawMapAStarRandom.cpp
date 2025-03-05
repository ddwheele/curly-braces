#include <algorithm>
#include <format>
#include "DrawMap.h"
#include "AStarRandom.h"
#include "AStar.h"
#include "AStarNode.h"
#include "StarNode.h"
#include "Utils.h"

using namespace std;

DrawMapAStarRandom::DrawMapAStarRandom(const AStarRandom& _astar) : astar(_astar) {}

void DrawMapAStarRandom::calculateUnitSize() {
  if(UNIT_X_SIZE > 0 && UNIT_Y_SIZE > 0) {
    return;
  }
  double maxX = 0, maxY = 0;
  for( auto& [node1, _] : astar.getAdjacencyMatrix()) {
    maxX = std::max(maxX, node1->x);
    maxY = std::max(maxY, node1->y);
  }
  UNIT_X_SIZE = maxX + 1;
  UNIT_Y_SIZE = maxY + 1;
}

void DrawMapAStarRandom::drawMap() {
  calculateUnitSize();
  mat = cv::Mat(UNIT_X_SIZE*Utils::SCALE, UNIT_Y_SIZE*Utils::SCALE, CV_8UC3, WHITE);

  for( auto& [node1, vec] : astar.getAdjacencyMatrix()) {
  	for(const auto& pr : vec) {
    	drawAStarEdge(*node1, *pr.first, pr.second);
    }
  }

}

void DrawMapAStarRandom::drawFinalPath() {
  auto curr = astar.getGoal();
  cout << "Initial node: ";
  curr->printMe();
  while(curr != nullptr) {
    curr->printMe();
    highlightNode(*curr);
    curr = curr->getParent();
  }
  cv::imshow("AStar Map", mat);
  cv::waitKey(0);
}

void DrawMapAStarRandom::highlightNode(const StarNode& node) {
  cv::Point nodeLoc = node.getCvPoint();
  cv::circle(mat, nodeLoc, RADIUS_PX, GREEN, 2);
  if(node.getParent()) {
      cv::line(mat, node.getCvPoint(), 
              node.getParent()->getCvPoint(),
              GREEN, 2);
  }

}

void DrawMapAStarRandom::drawLabeledAStarNode(const StarNode& anode) {
	cv::Point nodeLoc = anode.getCvPoint();

	cv::circle(mat, nodeLoc, RADIUS_PX, LT_GRAY, FILL_SHAPE);

	std::string text = anode.getName();
	
	cv::putText(mat, text, nodeLoc + NODE_LABEL_OFFSET, 
		FONT_FACE, FONT_SCALE_LARGE, BLACK, FONT_THICK);
}

void DrawMapAStarRandom::drawAStarEdge(const StarNode& n1, const StarNode& n2, double weight) {
  cv::line(mat, n1.getCvPoint(), 
              n2.getCvPoint(),
              BLACK, 1);

	drawLabeledAStarNode(n1);
  drawLabeledAStarNode(n2);

  cv::Point midpoint = (n1.getCvPoint() + n2.getCvPoint()) / 2;

  cv::putText(mat, format("{:.1f}", weight), midpoint, 
    FONT_FACE, FONT_SCALE_SMALL, BLACK, FONT_THIN);
}









