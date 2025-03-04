#ifndef DRAW_MAP_ASTAR_H
#define DRAW_MAP_ASTAR_H

#include <memory>
#include <opencv2/opencv.hpp>

#include "Obstacle.h"
#include "Constants.h"
#include "AStarNode.h"
#include "DrawMap.h"

class AStar;

class DrawMapAStar : public DrawMap {
public:
	DrawMapAStar(const AStar & _astar);
	
  void drawMap() override;
  void drawFinalPath() override;

private:
  const AStar& astar;

  void drawAStarEdge(const AStarNode& n1, const AStarNode& n2, double weight);
	void drawLabeledAStarNode(const AStarNode& anode);
};

#endif