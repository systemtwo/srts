#ifndef COMPONENT_WEAPON_H
#define COMPONENT_WEAPON_H

#include <cmath>

#include "World.h"
#include "GeomUtil.h"

class ComponentWeapon {
	public:
		ComponentWeapon(double firingArc, double range, double x, double y, double facingAngle, int team)
			: _firingArc(firingArc),
			  _range(range), 
       			  _team(team),
			  _x(x),
			  _y(y),
			  _facingAngle(facingAngle){
		}

		bool inFiringArc(double angle) {
			double diffAngle = fmax(_facingAngle, angle) - fmin(_facingAngle, angle);
			if (diffAngle < (_firingArc/2.0) || diffAngle > ((2 * PI) - _firingArc))
				return true;
			else 
				return false;

		}

		void setFacingAngle(double facingAngle) { _facingAngle = facingAngle; }
		void setFiringArc(double firingArc) { _firingArc = firingArc; }
		void setRange(double range) { _range = range; }
		void setOrigin(double x, double y) { _x = x; _y = y; }
		void setOrigin(sf::Vector2f loc) { setOrigin(loc.x, loc.y); }

		double getFacingAngle() { return _facingAngle; }
		double getFiringArc() { return _firingArc; }
		double getRange() { return _range; }
		sf::Vector2f getOrigin() { return sf::Vector2f(_x, _y); }

		virtual void fire(World* world) = 0;
		

	protected:
		double _firingArc;
		double _facingAngle;
		double _range;
		double _x;
		double _y;
		int _team;

};

#endif //COMPONENT_WEAPON_H
