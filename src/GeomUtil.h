#ifndef GEOM_UTIL_H
#define GEOM_UTIL_H

#include <iostream>
#include <vector>

#include <SFML/System.hpp>

//Geometry utilities
class Line {
	public:
		Line(double, double, double, double);
		double slope();

		double x1;
		double y1;
		double x2;
		double y2;
};
std::ostream& operator<< (std::ostream& os, const Line& line);

class GeomUtil {
	public:
		static bool lineIntersection(Line, Line);
		static bool pointInPolygon(std::vector<sf::Vector2f> polygon, double x, double y);
};



#endif //GEOM_UTIL_H
