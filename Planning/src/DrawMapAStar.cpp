#include "DrawMap.h"
#include "AStar.h"

DrawMapAStar::DrawMapAStar(const AStar& _astar) : astar(_astar) {}

void DrawMapAStar::drawMap() {
  mat = cv::Mat(Constants::HEIGHT_PX, Constants::WIDTH_PX, CV_8UC3, Constants::WHITE);

  for( auto& [node1, vec] : astar.getAdjacencyMatrix()) {
  	for(const auto& pr : vec) {
    	drawAStarEdge(*node1, *pr.first, pr.second);
    }
  }
  cv::imshow("AStar Map", mat);
  cv::waitKey(0);
}

void DrawMapAStar::drawFinalPath() {
  
}

void DrawMapAStar::drawLabeledAStarNode(const AStarNode& anode) {
	cv::Point nodeLoc = anode.getCvPoint();

	cv::circle(mat, nodeLoc, Constants::RADIUS_PX, Constants::GRAY, 1);

	std::string text = anode.getName();
	
	// Draw the text on the image
	cv::putText(mat, text, nodeLoc + NODE_LABEL_OFFSET, 
		FONT_FACE, FONT_SCALE, Constants::BLACK, FONT_THICKNESS);
}

void DrawMapAStar::drawAStarEdge(const AStarNode& n1, const AStarNode& n2, double weight) {
	drawLabeledAStarNode(n1);
  drawLabeledAStarNode(n2);

  cv::line(mat, n1.getCvPoint(), 
              n2.getCvPoint(),
              Constants::BLACK, 1);
}
