#ifndef DRAW_MAP_ASTAR_H
#define DRAW_MAP_ASTAR_H

#include <memory>
#include <opencv2/opencv.hpp>

#include "Obstacle.h"
#include "StarNode.h"
#include "DrawMap.h"

class DStarLite;

class DrawMapDStarLite : public DrawMap {
public:
	DrawMapDStarLite(const AStar & _astar);
	
  void drawMap() override;
  void drawFinalPath() override;

private:
  const DStarLite& dStarLite;

  void calculateUnitSize();

  static constexpr int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
  static constexpr int FILL_SHAPE = -1;
  static constexpr double FONT_SCALE_LARGE = 0.75;
  static constexpr double FONT_SCALE_SMALL = 0.75;
  static constexpr double FONT_THIN = 1;
  static constexpr double FONT_THICK = 2;
  static constexpr double LABEL_OFFSET_RATIO = 0.6;
  static inline cv::Point NODE_LABEL_OFFSET = 
    cv::Point(-RADIUS_PX*LABEL_OFFSET_RATIO,RADIUS_PX*LABEL_OFFSET_RATIO);

  // calculated ideal size of map, such that it shows all nodes
  double UNIT_X_SIZE = -1;
  double UNIT_Y_SIZE = -1;
};

#endif