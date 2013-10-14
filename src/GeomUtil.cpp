#include <cmath>

#include "GeomUtil.h"


//Note this does not follow naming convention because it would not make sense
Line::Line(double _x1, double _y1, double _x2, double _y2) 
	: x1(_x1),
	  y1(_y1),
	  x2(_x2),
	  y2(_y2) {
}

double Line::slope() {
	return (y2 - y1) / (x2 - x1);
}


bool GeomUtil::lineIntersection(Line l1, Line l2) {
	//Notation: m and b from "y = mx + b"
	//Get line 1 slope 
	
	double b1 = l1.y1 - (l1.slope() * l1.x1);
	double b2 = l2.y1 - (l2.slope() * l2.x1);
	
	double intersectX = (l1.x1 - l2.x1) / (b2 - b1);

	double minX = fmin(l1.x1, l1.x2);
	double maxX = fmax(l1.x1, l1.x2);


	if (intersectX < maxX && intersectX > minX) 
		return true;
	else 
		return false;
}

bool GeomUtil::pointInPolygon(std::vector<sf::Vector2f> polygon, double x, double y) {
	Line ray(-1000, y, x, y);
	int intersectCount = 0;
	for (int i = 0; i < polygon.size() - 1; i++) {
		Line l(polygon[i].x, polygon[i].y, polygon[i + 1].x, polygon[i + 1].y);
		if (lineIntersection(l, ray)) 
			intersectCount++;
	}

	//And last point to first point
	Line l(polygon[polygon.size() - 1].x, polygon[polygon.size() - 1].y, polygon[0].x, polygon[0].y);
	if (lineIntersection(l, ray))
		intersectCount++;

	if (intersectCount % 2 == 0)
		return false;
	else 
		return true;
}
