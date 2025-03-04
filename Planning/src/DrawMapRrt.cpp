#import "DrawMap.h"

#include "RRT.h"

DrawMapRrt::DrawMapRrt(const RRT& _rrt) : rrt(_rrt) {}

void DrawMapRrt::drawMap() {
  mat = cv::Mat(HEIGHT_PX, WIDTH_PX, CV_8UC3, WHITE);
  for(auto& o : rrt.getObstacles()) {
    drawObstacle(o);
  }
  drawColoredNode(rrt.getStart(), GREEN);
  drawColoredNode(rrt.getGoal(), RED);

  for(auto nd : rrt.getStartTree()) {
    if (nd->parent) {
      drawRrtNode(*nd, BLACK);
    }
  }

  for(auto nd : rrt.getGoalTree()) {
    if (nd->parent) {
      drawRrtNode(*nd, BLACK);
    }
  }

  cv::imshow("RRT Tree", mat);
  cv::waitKey(SHOW_DELAY);
}

void DrawMapRrt::drawFinalPath() {
  shared_ptr<RrtNode> curr = rrt.getLinkRrtNode1();

  while(curr && curr->parent) {
    drawRrtNode(*curr, BLUE, 2);
    curr = curr->parent;
  }
  curr = rrt.getLinkRrtNode2();
  while(curr && curr->parent) {
    drawRrtNode(*curr, BLUE, 2);
    curr = curr->parent;
  }

  cv::line(mat, rrt.getLinkRrtNode1()->getCvPoint(), 
              rrt.getLinkRrtNode2()->getCvPoint(),
              BLUE, 2);

  cv::imshow("Tree", mat);
  cv::waitKey(0);
}

void DrawMapRrt::drawRrtNode(const RrtNode& n, const cv::Scalar& color, int width) const {
  cv::line(mat, n.getCvPoint(), 
                n.parent->getCvPoint(),
                color, width);
}
