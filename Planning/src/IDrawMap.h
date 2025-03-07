#ifndef I_DRAW_MAP_H
#define I_DRAW_MAP_H

// An interface class so that PathPlanners can include a DrawMap without
// requiring OpenCV
class IDrawMap {
public:
	virtual void drawMap() = 0;
	virtual void drawFinalPath() = 0;
	virtual ~IDrawMap() = default;
};


#endif