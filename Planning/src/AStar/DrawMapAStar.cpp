#include <algorithm>
#include <format>
#include "DrawMap.h"
#include "DrawMapAStar.h"
#include "AStar.h"
#include "Utils.h"

using namespace std;

DrawMapAStar::DrawMapAStar(const AStar& _astar) : astar(_astar) {}

// calculate the size the canvas needs to be (in units, not pixels) to contain all nodes
void DrawMapAStar::calculateUnitSize() {
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

// Draw all edges and nodes in graph
void DrawMapAStar::drawMap() {
  calculateUnitSize();
  mat = cv::Mat(UNIT_X_SIZE*Utils::SCALE, UNIT_Y_SIZE*Utils::SCALE, CV_8UC3, WHITE);

  for( auto& [node1, vec] : astar.getAdjacencyMatrix()) {
  	for(const auto& pr : vec) {
    	drawAStarEdge(*node1, *pr.first, pr.second);
    }
  }
}

// Highlight the final path in green
void DrawMapAStar::drawFinalPath() {
  auto curr = astar.getGoal();
  shared_ptr<AStarNode> lastCurr;
  cout << "Initial node: ";
  curr->printMe();
  while(curr != nullptr) {
    curr->printMe();

    if(lastCurr != nullptr) {
      highlightAStarEdge(*curr, *lastCurr);
    }
    highlightNode(*curr);
    lastCurr = curr;
    curr = curr->getParent();
  }
  cv::imshow("AStar Map", mat);
  cv::waitKey(0);
}

void DrawMapAStar::highlightNode(const AStarNode& node) {
  drawLabeledAStarNode(node);

  cv::Point nodeLoc = getCvPoint(node);

  cv::circle(mat, nodeLoc, RADIUS_PX, GREEN, 4);
}

void DrawMapAStar::drawLabeledAStarNode(const AStarNode& anode) {
	cv::Point nodeLoc = getCvPoint(anode);

	cv::circle(mat, nodeLoc, RADIUS_PX, LT_GRAY, FILL_SHAPE);

	std::string text = anode.getName();
	
	cv::putText(mat, text, nodeLoc + NODE_LABEL_OFFSET, 
		FONT_FACE, FONT_SCALE_LARGE, BLACK, FONT_THICK);
}

void DrawMapAStar::highlightAStarEdge(const AStarNode& n1, const AStarNode& n2) {
  cv::line(mat, getCvPoint(n1), 
              getCvPoint(n2),
              GREEN, 4);

  drawLabeledAStarNode(n1);
  drawLabeledAStarNode(n2);
}


void DrawMapAStar::drawAStarEdge(const AStarNode& n1, const AStarNode& n2, double weight) {
  cv::line(mat, getCvPoint(n1), 
              getCvPoint(n2),
              BLACK, 1);

	drawLabeledAStarNode(n1);
  drawLabeledAStarNode(n2);

  cv::Point midpoint = (getCvPoint(n1) + getCvPoint(n2)) / 2;

  cv::putText(mat, format("{:.1f}", weight), midpoint, 
    FONT_FACE, FONT_SCALE_SMALL, BLACK, FONT_THIN);
}









