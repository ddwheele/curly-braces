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
    cout << "A" << endl;
  for(auto node : dStarLite.getNodes()) {
    cout << node->getName() << endl;
    drawNode(*node);
    cv::imshow("D* Lite Map", mat);
    cv::waitKey(0);
    cout << "a.5" <<endl;
  }

  //cout << "B" << endl;
  //cout << "Fetching obstacles " << endl;
  cout << dStarLite.getCurrentObstacles().empty() << endl;
  for(auto node : dStarLite.getCurrentObstacles()) {
    obstacleNode(*node);
  }
  cout << "C" << endl;
   highlightNode(*dStarLite.getStartNode());
  cout << "D" << endl;
    cv::imshow("D* Lite Map", mat);
    cv::waitKey(0);
}

void DrawMapDStarLite::drawNode(const DStarNode& dnode) {
  cout << "Drawing Node " << dnode.getName() <<endl;
  cv::Point nodeLoc = getCvPoint(dnode);

  cv::circle(mat, nodeLoc, RADIUS_PX, LT_GRAY, FILL_SHAPE);

  std::string text = dnode.getName();
  
  cv::putText(mat, text, nodeLoc + NODE_LABEL_OFFSET, 
    FONT_FACE, FONT_SCALE_LARGE, BLACK, FONT_THICK);
    cout<<"Node drawing complete" << endl;
}

void DrawMapDStarLite::drawEdge(const DStarNode& n1, const DStarNode& n2, double weight) {
  cv::line(mat, getCvPoint(n1), 
              getCvPoint(n2),
              BLACK, 1);


  // drawLabeledAStarNode(n1);
  // drawLabeledAStarNode(n2);

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
