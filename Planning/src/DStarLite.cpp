#include <iostream>
#include "DStarLite.h"







DStarLite::DStarLite(vector<shared_ptr<DStarNode>> node) : drawMap(*this) {

}

void DStarLite::findPath()  {
	cout << "findPath called" << endl;
}