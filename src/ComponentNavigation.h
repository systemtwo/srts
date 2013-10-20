#ifndef COMPONENT_NAVIGATION_H
#define COMPONENT_NAVIGATION_H

#include "GeomUtil.h"

class ComponentNavigation {
	public:
		ComponentNavigation(double x, double y, double speed, double turningSpeed)
			: _speed(speed),
			  _turningSpeed(turningSpeed),
       			  _x(x), 
			  _y(y),
       			  _targetX(x),
			  _targetY(y) {
		}

		virtual void update(double dt) = 0;

		void setTarget(double x, double y) { 
			_targetX = x; 
			_targetY = y;
			_atTargetLocation = false;
	       	}

		void setTarget(sf::Vector2f location) {
			setTarget(location.x, location.y);
		}

		void setPosition(double x, double y) { _x = x; _y = y; }
		void setAngle(double radians) { _angle = radians; } 
		

		sf::Vector2f getTarget() { return sf::Vector2f(_targetX, _targetY); }
		sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }
		double getAngle() { return _angle; }
		bool atTargetLocation() { return _atTargetLocation; };

	protected:
		double _speed;
		double _turningSpeed;
		double _angle;
		double _targetX;
		double _targetY;
		double _x;
		double _y;

		bool _atTargetLocation;

};

#endif //COMPONENT_NAVIGATION_H
