#include "DrawMap.h"

void DrawMap::drawColoredNode(const Node& n, const cv::Scalar& color) const {
  cv::circle(mat, getCvPoint(n), RADIUS_PX, color, -1);
}

void DrawMap::drawObstacle(const Obstacle& o) const {
  cv::rectangle(mat, o.getMinCvPoint(), o.getMaxCvPoint(), GRAY, -1);
}

cv::Point DrawMap::getCvPoint(const Node& n) {
  return cv::Point(static_cast<int>(n.x*Utils::SCALE), static_cast<int>(n.y*Utils::SCALE));
}