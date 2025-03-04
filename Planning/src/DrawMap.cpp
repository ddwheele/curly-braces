#include "DrawMap.h"

void DrawMap::drawColoredNode(const Node& n, const cv::Scalar& color) const {
  cv::circle(mat, n.getCvPoint(), RADIUS_PX, color, -1);
}

void DrawMap::drawObstacle(const Obstacle& o) const {
  cv::rectangle(mat, o.getMinCvPoint(), o.getMaxCvPoint(), GRAY, -1);
}