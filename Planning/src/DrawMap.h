#ifndef DRAW_MAP_H
#define DRAW_MAP_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "RrtNode.h"
#include "Obstacle.h"
#include "Constants.h"
#include "AStarNode.h"

class PathPlanner;

class DrawMap {
public:
	DrawMap(const PathPlanner& _planner);
	void drawRrt();
  void drawFinalRrtPath();

	void drawAStarMap();

private:
  cv::Mat mat;
  const PathPlanner& planner;  // Reference to the Planner object (read-only)
 
  void drawObstacle(const Obstacle& o) const;
  void drawColoredNode(const Node& n, 
 		const cv::Scalar& color) const;

  void drawAStarEdge(const AStarNode& n1, const AStarNode& n2, double weight);
	void drawLabeledAStarNode(const AStarNode& anode);

  void drawRrtNode(const RrtNode& n,
  	const cv::Scalar& color, int width=1) const;

  static constexpr int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
  static constexpr int FILL_SHAPE = -1;
  static constexpr double FONT_SCALE = 0.5;
  static constexpr double FONT_THICKNESS = 2;

  static inline cv::Point NODE_LABEL_OFFSET = cv::Point(0,0);

};

#endif