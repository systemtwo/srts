#ifndef COMPONENT_TARGETTING_H
#define COMPONENT_TARGETTING_H

#include <vector>
#include <cmath>

#include "Ship.h"
#include "GeomUtil.h" 

//Finds (or user sets) a target that it attempts to follow

//TODO - Add a enum or something that allows for different targetting techniques
class ComponentTargetting {
	public:
		ComponentTargetting(double x, double y, double scanRadius)
	       		: _x(x),
			  _y(y),
       			  _scanRadius(scanRadius),
       			  _targetShip(nullptr) { }

		void setOrigin(double x, double y) { _x = x; _y = y; }
		void setOrigin(sf::Vector2f loc) { setOrigin(loc.x, loc.y); }
		void setScanRadius(double rad) { _scanRadius = rad; }
		void setTargetShip(Ship* ship) { _targetShip = ship; }

		//sf::Vector2f getTargetPosition() { return sf::Vector2f(_targetX, _targetX); }
		sf::Vector2f getTargetPosition() { return _targetShip->getPosition(); }
		Ship* getTargetShip() { return _targetShip; }
		sf::Vector2f getOrigin() { return sf::Vector2f(_x, _y); }
		double getScanRadius() { return _scanRadius; }
		double getTargetAngle() { 
			//Make sure to call setTarget every time we want info on the enemy ship
			setTarget(_targetShip->getPosition());
			double ang = atan2 (_targetY - _y, _targetX - _x);
			return (ang < 0)? ang + (2.0 * PI) : ang;
		}
		


		void scan(std::vector<Ship*> ships) {
			//Target closest ship
			double minDist = _scanRadius;

			//Don't forget to reset the target ship state
			_targetShip = NULL;
			for (auto ship : ships) {
				double diffX = ship->getPosition().x - _x;
				double diffY = ship->getPosition().y - _y;
				if (hypot(diffX, diffY) < minDist) {
					minDist = hypot(diffX, diffY);
					_targetShip = ship;
					_targetX = ship->getPosition().x;
					_targetY = ship->getPosition().y;
				}
			}
		}

		bool checkInAngle(std::vector<Ship*> ships, double angle, double bound) {
			//Check to see if there is a ship in the arc
			//Scan with bounded +/- angle
			//Select ships within bound radians of angle
			for (auto ship : ships) {
				//double ang = atan2 (ship->getPosition().y - _y, ship->getPosition().x - _x);
				//Using dot product

				//Vector to the ship
				double x1 = ship->getPosition().x - _x;
				double y1 = ship->getPosition().y - _y;

				//Vector we are facing
				double x2 = cos(angle);
				double y2 = sin(angle);

				//A dot B
				double dotproduct = (x1 * x2) + (y1 * y2);

				//Find the angle
				double angDiff = acos(dotproduct/(hypot(x1, y1) * hypot(x2, y2)));

				if (angDiff < bound) {
					return true;
				}
				
			}
			return false;
		}


			  
	
	private: 
		Ship*  _targetShip;
		double _targetX;
		double _targetY;
		double _x; //Origin
		double _y;
		double _scanRadius;

		void setTarget(double x, double y) { _targetX = x; _targetY = y; }
		void setTarget(sf::Vector2f loc) { setTarget(loc.x, loc.y); }
};

#endif //COMPONENT_TARGETTING_H
