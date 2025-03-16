#include <algorithm>
#include <format>
#include "DrawMapDStarLite.h"
#include "Utils.h"

using namespace std;

DrawMapDStarLite::DrawMapDStarLite(const AbstractDStarLite& _dStarLite) : dStarLite(_dStarLite) {}

void DrawMapDStarLite::drawMap()
{
 cout << "Drawing the Map" << endl;
  mat = cv::Mat(UNIT_X_SIZE * Utils::SCALE, UNIT_Y_SIZE * Utils::SCALE, CV_8UC3, WHITE);

  for( auto& [src, dst_map] : dStarLite.getCostMap()) {
    for(const auto& [dst, wt] : dst_map) {
      drawEdge(*src, *dst, wt);
    }
  }
  for(auto node : dStarLite.getNodes()) {
    drawNode(*node);
  }

  for(auto node : dStarLite.getCurrentObstacles()) {    
    obstacleNode(*node);
  }

  highlightNode(*dStarLite.getStartNode());

  cv::imshow("D* Lite Map", mat);
  cv::waitKey(5);
}

void DrawMapDStarLite::drawMapAndWait() {
  drawMap();
  cv::waitKey(0);
}

void DrawMapDStarLite::drawEdge(const DStarNode& n1, const DStarNode& n2, double weight) {
  int line_wt = FONT_THIN;
  if(weight > 500) {
    line_wt = FONT_THICK;
  }

  cv::line(mat, getCvPoint(n1), 
              getCvPoint(n2),
              BLACK, line_wt);

  if(PRINT_LABELS) {
    cv::Point midpoint = (getCvPoint(n1) + getCvPoint(n2)) / 2;

    cv::putText(mat, format("{:.1f}", weight), midpoint, 
       FONT_FACE, FONT_SCALE_SMALL, BLACK, FONT_THIN);
  }
}

void DrawMapDStarLite::drawFinalPath()
{

}

void DrawMapDStarLite::drawNode(const DStarNode& dnode, const cv::Scalar color) {
  cv::Point nodeLoc = getCvPoint(dnode);

  cv::circle(mat, nodeLoc, RADIUS_PX, color, FILL_SHAPE);

  std::string nameText = dnode.getName();
  std::string gText = Utils::infString(dnode.getGn());
  std::string rText = Utils::infString(dnode.getRhs());

  cv::Scalar labelColor = BLACK;
  if(color == BLACK) {
    labelColor = WHITE;
  }

  cv::putText(mat, nameText, nodeLoc + NODE_LABEL_OFFSET, 
    FONT_FACE, FONT_SCALE_LARGE, labelColor, FONT_THICK);

  cv::putText(mat, "g=" + gText, nodeLoc + G_LABEL_OFFSET, 
    FONT_FACE, FONT_SCALE_SMALL, BLACK, FONT_THIN);

  cv::putText(mat, "rhs=" + rText, nodeLoc + R_LABEL_OFFSET, 
    FONT_FACE, FONT_SCALE_SMALL, BLACK, FONT_THIN);

  if(dnode.isInOpenSet()) {
    std::string keyText = dnode.getKey().toShortString();
    cv::putText(mat, keyText, nodeLoc + KEY_LABEL_OFFSET, 
      FONT_FACE, FONT_SCALE_SMALL, BLACK, FONT_THIN);
  }
}

void DrawMapDStarLite::obstacleNode(const DStarNode &node)
{
  drawNode(node, BLACK);
}

void DrawMapDStarLite::highlightNode(const DStarNode &node)
{
  drawNode(node, GREEN);
}
