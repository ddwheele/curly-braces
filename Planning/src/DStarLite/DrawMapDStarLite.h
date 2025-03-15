#ifndef DRAW_MAP_ASTAR_H
#define DRAW_MAP_ASTAR_H

#include <memory>
#include <opencv2/opencv.hpp>

#include "DStarLite.h" 
#include "Obstacle.h"
#include "DStarNode.h"
#include "StarNode.h"
#include "DrawMap.h"

class DStarLite;

class DrawMapDStarLite : public DrawMap {
public:
	DrawMapDStarLite(const DStarLite& _dstar);
	
  void drawMap() override;
  void drawMapAndWait() override; 
  void drawFinalPath() override;

private:
  const DStarLite& dStarLite;

  void drawNode(const DStarNode& dnode);
  void drawEdge(const DStarNode& n1, const DStarNode& n2, double weight);
  void highlightNode(const DStarNode &node);
  void obstacleNode(const DStarNode &node);

  static constexpr int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
  static constexpr int FILL_SHAPE = -1;
  static constexpr double FONT_SCALE_LARGE = 0.75;
  static constexpr double FONT_SCALE_SMALL = 0.75;
  static constexpr double FONT_THIN = 1;
  static constexpr double FONT_THICK = 2;
  static constexpr double LABEL_OFFSET_RATIO = 0.6;
  static inline cv::Point NODE_LABEL_OFFSET = 
    cv::Point(-RADIUS_PX*LABEL_OFFSET_RATIO, RADIUS_PX*LABEL_OFFSET_RATIO);

  static inline cv::Point G_LABEL_OFFSET = 
    cv::Point(-RADIUS_PX*LABEL_OFFSET_RATIO, 3*RADIUS_PX*LABEL_OFFSET_RATIO);

  static inline cv::Point R_LABEL_OFFSET = 
    cv::Point(-RADIUS_PX*LABEL_OFFSET_RATIO, 5*RADIUS_PX*LABEL_OFFSET_RATIO);

  static inline cv::Point KEY_LABEL_OFFSET = 
    cv::Point(-RADIUS_PX*LABEL_OFFSET_RATIO, 7*RADIUS_PX*LABEL_OFFSET_RATIO);

  // size of map, in "world units"
  double UNIT_X_SIZE = 20;
  double UNIT_Y_SIZE = 20;
};

#endif