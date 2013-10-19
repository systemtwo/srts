#ifndef COMPONENT_NAVIGATION_MOVING_H
#define COMPONENT_NAVIGATION_MOVING_H

#include "ComponentNavigation.h"

class ComponentNavigationMoving : public ComponentNavigation {
	public:
		ComponentNavigationMoving(double x, double y, double speed, double turningSpeed) 
			: ComponentNavigation(x, y, speed, turningSpeed) {
		}

		void update(double dt) {
			//Fix angle if needed
			if (_angle > (3.0 * PI))
				_angle -= 2.0 * PI;
			if (_angle < -PI) 
				_angle += 2.0 * PI;


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
};

#endif //COMPONENT_NAVIGATION_MOVING_H
