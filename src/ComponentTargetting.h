#ifndef COMPONENT_TARGETTING
#define COMPONENT_TARGETTING

#include "Ship.h"

//Finds (or user sets) a target that it attempts to follow
class ComponentTargetting {
	public:
		ComponentTargetting(double x, double y)
	       		: _x(x),
			  _y(y) { }

		void setTarget(double x, double y) { }
		void setOrigin(double x, double y) { }
		void setScanRadius(double rad) { _scanRadius = rad; }

		sf::Vector2f getTargetPosition() { }
		sf::Vector2f getOrigin() { }
		double getScanRadius() { return _scanRadius; }


		void update(double dt) { }

	
	private: 
		Ship   _targetShip;
		double _targetX;
		double _targetY;
		double _x; //Origin
		double _y;
		double _scanRadius;
};

#endif //COMPONENT_TARGETTING
