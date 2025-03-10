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

  for( auto node : dStarLite.getNodes()) {
    drawNode(*node);
  }

  cv::imshow("D* Lite Map", mat);
  cv::waitKey(0);
}

void DrawMapDStarLite::drawNode(const DStarNode& dnode) {
  cv::Point nodeLoc = getCvPoint(dnode);

  cv::circle(mat, nodeLoc, RADIUS_PX, LT_GRAY, FILL_SHAPE);

  std::string text = dnode.getName();
  
  cv::putText(mat, text, nodeLoc + NODE_LABEL_OFFSET, 
    FONT_FACE, FONT_SCALE_LARGE, BLACK, FONT_THICK);
}

void DrawMapDStarLite::drawFinalPath()
{

}

// void DrawMapDStarLite::highlightNode(const AStarNode &node)
// {
//   // cv::Point nodeLoc = node.getCvPoint();

//   // cv::circle(mat, nodeLoc, RADIUS_PX, GREEN, 2);
// }
