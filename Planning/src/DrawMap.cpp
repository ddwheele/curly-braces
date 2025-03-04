#import "DrawMap.h"
#import "AStar.h"
#import "RRT.h"

DrawMap::DrawMap(const PathPlanner& _planner) : planner(_planner) {}

void DrawMap::drawRrtTree() {
	auto* rrt = dynamic_cast<const RRT*>(&planner);
  if (!rrt) {
    std::cout << "Do not have an RRT, aborting" << endl;
    return;
  } 

  mat = cv::Mat(Constants::HEIGHT_PX, Constants::WIDTH_PX, CV_8UC3, Constants::WHITE);
  for(auto& o : rrt->getObstacles()) {
    drawObstacle(o);
  }
  drawColoredNode(rrt->getStart(), Constants::GREEN);
  drawColoredNode(rrt->getGoal(), Constants::RED);

  for(auto nd : rrt->getStartTree()) {
    if (nd->parent) {
      drawRrtNode(*nd, Constants::BLACK);
    }
  }

  for(auto nd : rrt->getGoalTree()) {
    if (nd->parent) {
      drawRrtNode(*nd, Constants::BLACK);
    }
  }

  cv::imshow("RRT Tree", mat);
  cv::waitKey(Constants::SHOW_DELAY);
}


void DrawMap::drawFinalRrtPath() {
	auto* rrt = dynamic_cast<const RRT*>(&planner);
  if (!rrt) {
    std::cout << "Do not have an RRT, aborting" << endl;
    return;
  } 
  shared_ptr<RrtNode> curr = rrt->getLinkRrtNode1();

  while(curr && curr->parent) {
    drawRrtNode(*curr, Constants::BLUE, 2);
    curr = curr->parent;
  }
  curr = rrt->getLinkRrtNode2();
  while(curr && curr->parent) {
    drawRrtNode(*curr, Constants::BLUE, 2);
    curr = curr->parent;
  }

  cv::line(mat, rrt->getLinkRrtNode1()->getCvPoint(), 
              rrt->getLinkRrtNode2()->getCvPoint(),
              Constants::BLUE, 2);

  cv::imshow("Tree", mat);
  cv::waitKey(0);
}

void DrawMap::drawRrtNode(const RrtNode& n, const cv::Scalar& color, int width) const {
  cv::line(mat, n.getCvPoint(), 
                n.parent->getCvPoint(),
                color, width);
}

void DrawMap::drawColoredNode(const Node& n, const cv::Scalar& color) const {
  cv::circle(mat, n.getCvPoint(), Constants::RADIUS_PX, color, -1);
}

void DrawMap::drawObstacle(const Obstacle& o) const {
  cv::rectangle(mat, o.getMinCvPoint(), o.getMaxCvPoint(), Constants::GRAY, -1);
}