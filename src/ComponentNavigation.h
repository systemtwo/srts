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

		void update(double dt) {
			//Fix angle if needed
			if (_angle > (3.0 * PI))
				_angle -= 2.0 * PI;
			if (_angle < -PI) 
				_angle += 2.0 * PI;


			//Turn towards target
			double targetAngle = atan2(_targetY - _y, _targetX - _x);
			if (targetAngle < 0)
				targetAngle = (2.0 * PI) + targetAngle;

			//Cross product method
			double vecTargetX = _targetX - _x;
			double vecTargetY = _targetY - _y;

			double vecFacingX = cos(_angle);
			double vecFacingY = sin(_angle);


			if (((vecTargetX * vecFacingY) - (vecTargetY * vecFacingX)) > 0) 
				_angle -= _turningSpeed * dt;
			else
				_angle += _turningSpeed * dt;

			
			//Move with turning
			double xmove = _speed * cos(_angle) * dt;
			double ymove = _speed * sin(_angle) * dt;

			_x += xmove;
			_y += ymove;

			/*
			std::cout << "dt: " << dt << std::endl;
			std::cout << "_speed: " << _speed << std::endl;
			std::cout << "Non-dt speeds: " << _speed * cos(_angle) << ", " << _speed * sin(_angle) << std::endl;
			std::cout << "Moving speed: " << xmove << ", " << ymove << std::endl;
			std::cout << "Current Angle: " << _angle << std::endl;
			std::cout << "Target Angle: " << targetAngle << std::endl;
			std::cout << "Cross product" << ((vecTargetX * vecFacingY) - (vecTargetY * vecFacingX)) << std::endl;
			*/
	       	}

		void setTarget(double x, double y) { _targetX = x; _targetY = y; }
		void setPosition(double x, double y) { _x = x; _y = y; }
		void setAngle(double radians) { _angle = radians; } 
		

		sf::Vector2f getTarget() { return sf::Vector2f(_targetX, _targetY); }
		sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }
		double getAngle() { return _angle; }

	private:
		double _speed;
		double _turningSpeed;
		double _angle;
		double _targetX;
		double _targetY;
		double _x;
		double _y;

};

#endif //COMPONENT_NAVIGATION_H
