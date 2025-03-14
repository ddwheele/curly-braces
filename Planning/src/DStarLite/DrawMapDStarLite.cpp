#include <algorithm>
#include <format>
#include "DrawMapDStarLite.h"
#include "Utils.h"

using namespace std;

DrawMapDStarLite::DrawMapDStarLite(const DStarLite& _dStarLite) : dStarLite(_dStarLite) {}

void DrawMapDStarLite::drawMap()
{
 cout << "Drawing the Map" << endl;
  mat = cv::Mat(UNIT_X_SIZE * Utils::SCALE, UNIT_Y_SIZE * Utils::SCALE, CV_8UC3, WHITE);
  cout << "Canvas size = " << UNIT_X_SIZE * Utils::SCALE <<" by " << UNIT_Y_SIZE * Utils::SCALE << endl;

  for( auto& [src, dst_map] : dStarLite.getCostMap()) {
    for(const auto& [dst, wt] : dst_map) {
      drawEdge(*src, *dst, wt);
    }
  }

  cout << dStarLite.getCurrentObstacles().empty() << endl;
  for(auto node : dStarLite.getCurrentObstacles()) {    
    obstacleNode(*node);
  }

  for(auto node : dStarLite.getNodes()) {
    drawNode(*node);
  }

  highlightNode(*dStarLite.getStartNode());

  cv::imshow("D* Lite Map", mat);
  cv::waitKey(5);
}

void DrawMapDStarLite::drawMapAndWait() {
  drawMap();
  cv::waitKey(0);
}

void DrawMapDStarLite::drawNode(const DStarNode& dnode) {
  cv::Point nodeLoc = getCvPoint(dnode);

  cv::circle(mat, nodeLoc, RADIUS_PX, LT_GRAY, FILL_SHAPE);

  std::string text = dnode.getName();
  
  cv::putText(mat, text, nodeLoc + NODE_LABEL_OFFSET, 
    FONT_FACE, FONT_SCALE_LARGE, BLACK, FONT_THICK);
}

void DrawMapDStarLite::drawEdge(const DStarNode& n1, const DStarNode& n2, double weight) {
  int line_wt = FONT_THIN;
  if(weight > 500) {
    line_wt = FONT_THICK;
  }

  cv::line(mat, getCvPoint(n1), 
              getCvPoint(n2),
              BLACK, line_wt);

  // cv::Point midpoint = (getCvPoint(n1) + getCvPoint(n2)) / 2;

  // cv::putText(mat, format("{:.1f}", weight), midpoint, 
  //   FONT_FACE, FONT_SCALE_SMALL, BLACK, FONT_THIN);
}

void DrawMapDStarLite::drawFinalPath()
{

}

void DrawMapDStarLite::obstacleNode(const DStarNode &node)
{
  cv::Point nodeLoc = getCvPoint(node);

  cv::circle(mat, nodeLoc, RADIUS_PX, BLACK, 5);
}

void DrawMapDStarLite::highlightNode(const DStarNode &node)
{
  cv::Point nodeLoc = getCvPoint(node);

  cv::circle(mat, nodeLoc, RADIUS_PX, GREEN, 2);
}
