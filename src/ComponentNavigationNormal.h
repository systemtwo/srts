#ifndef COMPONENT_NAVIGATION_NORMAL_H
#define COMPONENT_NAVIGATION_NORMAL_H

class ComponentNavigationNormal : public ComponentNavigation {
	public:
		ComponentNavigationNormal(double x, double y, double speed, double turningSpeed) 
			: ComponentNavigation(x, y, speed, turningSpeed) {
		}

		void update(double dt) {
			//Fix angle if needed
			if (_angle > (3.0 * PI))
				_angle -= 2.0 * PI;
			if (_angle < -PI) 
				_angle += 2.0 * PI;


			//Create vectors for cross product
			double vecTargetX = _targetX - _x;
			double vecTargetY = _targetY - _y;

			double vecFacingX = cos(_angle);
			double vecFacingY = sin(_angle);

			double distanceToTarget = hypot(vecTargetX, vecTargetY);

			//We don't need the ship to be pixel perfect at this spot
			bool arrivedAtTarget;
			if (distanceToTarget < 5.0)
				arrivedAtTarget = true;
			else
				arrivedAtTarget = false;


			double currSpeed = _speed;
			//Slow down as we get closer
			if (distanceToTarget < 50.0)
				currSpeed /= 2.0;
			
			if (!arrivedAtTarget) {
				//Cross product method (Calculate which way to turn)
				if (((vecTargetX * vecFacingY) - (vecTargetY * vecFacingX)) > 0) 
					_angle -= _turningSpeed * dt;
				else
					_angle += _turningSpeed * dt;

				//Move with turning
				double xmove = currSpeed * cos(_angle) * dt;
				double ymove = currSpeed * sin(_angle) * dt;

				_x += xmove;
				_y += ymove;
			}
		}
	
	private:
};

#endif //COMPONENT_NAVIGATION_NORMAL_H
