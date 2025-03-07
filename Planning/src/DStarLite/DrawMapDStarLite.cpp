#include <algorithm>
#include <format>
#include "DrawMapDStarLite.h"
#include "Utils.h"

using namespace std;

DrawMapDStarLite::DrawMapDStarLite(const DStarLite& _dStarLite) : dStarLite(_dStarLite) {}

void DrawMapDStarLite::calculateUnitSize()
{
  // if (UNIT_X_SIZE > 0 && UNIT_Y_SIZE > 0)
  // {
  //   return;
  // }
  // double maxX = 0, maxY = 0;
  // for (auto &[node1, _] : astar.getAdjacencyMatrix())
  // {
  //   maxX = std::max(maxX, node1->x);
  //   maxY = std::max(maxY, node1->y);
  // }
  // UNIT_X_SIZE = maxX + 1;
  // UNIT_Y_SIZE = maxY + 1;
}

void DrawMapDStarLite::drawMap()
{
  calculateUnitSize();
  mat = cv::Mat(UNIT_X_SIZE * Utils::SCALE, UNIT_Y_SIZE * Utils::SCALE, CV_8UC3, WHITE);

  // for (auto &[node1, vec] : astar.getAdjacencyMatrix())
  // {
  //   for (const auto &pr : vec)
  //   {
  //     drawAStarEdge(*node1, *pr.first, pr.second);
  //   }
  // }
}

void DrawMapDStarLite::drawFinalPath()
{

}

// void DrawMapDStarLite::highlightNode(const AStarNode &node)
// {
//   // cv::Point nodeLoc = node.getCvPoint();

//   // cv::circle(mat, nodeLoc, RADIUS_PX, GREEN, 2);
// }
