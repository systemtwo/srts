#include <iostream>
#include <cmath>

#include "GeomUtil.h"


//Note this does not follow naming convention because it would not make sense
Line::Line(double _x1, double _y1, double _x2, double _y2) 
	: x1(_x1),
	  y1(_y1),
	  x2(_x2),
	  y2(_y2) {
	//Cheat to make NaNs (0 slope) and inf slope go away
	if (x1 == x2) {
		x1 += 0.01;
	}
	if (y1 == y2) {
		y1 += 0.01;
	}

}

double Line::slope() {
	return (y2 - y1) / (x2 - x1);
}

std::ostream& operator<< (std::ostream& os, const Line& line) {
	os << "(" << line.x1 << ", " << line.y1 << "), (" << line.x2 << ", " << line.y2 << ")";
	return os;
}


bool GeomUtil::lineIntersection(Line l1, Line l2) {
	//Notation: m and b from "y = mx + b"
	//Get line 1 slope 
	
	double b1 = l1.y1 - (l1.slope() * l1.x1);
	double b2 = l2.y1 - (l2.slope() * l2.x1);
	
	//double intersectX = (l1.x1 - l2.x1) / (b2 - b1);
	double intersectX = (b2 - b1) / (l1.slope() - l2.slope());

	double minX1 = fmin(l1.x1, l1.x2);
	double maxX1 = fmax(l1.x1, l1.x2);

	double minX2 = fmin(l2.x1, l2.x2);
	double maxX2 = fmax(l2.x1, l2.x2);
	
	//std::cout << "Intersection at " << intersectX << std::endl;
	//Check for NaN
	if (intersectX != intersectX)
		return false;

	if (intersectX <= maxX1 && intersectX >= minX1 && intersectX <= maxX2 && intersectX >= minX2 ) 
		return true;
	else 
		return false;
}

bool GeomUtil::pointInPolygon(std::vector<sf::Vector2f> polygon, double x, double y) {
	Line ray(-1000, y, x, y);
	int intersectCount = 0;
	for (unsigned int i = 0; i < polygon.size() - 1; i++) {
		Line l(polygon[i].x, polygon[i].y, polygon[i + 1].x, polygon[i + 1].y);
		//std::cout << l << std::endl;
		if (lineIntersection(l, ray)) {
			intersectCount++;
		}
	}

	//And last point to first point
	Line l(polygon[polygon.size() - 1].x, polygon[polygon.size() - 1].y, polygon[0].x, polygon[0].y);
	if (lineIntersection(l, ray))
		intersectCount++;

	std::cout << intersectCount << " intersections" << std::endl;
	if (intersectCount % 2 == 0)
		return false;
	else 
		return true;
}

double GeomUtil::degToRad(double deg) {
	return deg * (PI/180.0);
}

double GeomUtil::radToDeg(double rad) {
	return rad * (180.0/PI);
}
