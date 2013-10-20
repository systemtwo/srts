#ifndef COMPONENT_WEAPON_H
#define COMPONENT_WEAPON_H

#include <cmath>

class ComponentWeapon {
	public:
		ComponentWeapon(double firingArc, double range) 
			: _firingArc(fireArc),
			  _range(range) {
		}

		bool inFiringArc(double angle) {
			double diffAngle = fmax(_facingAngle, angle) - fmin(_facingAngle, angle);
			if (diffAngle < (_firingArc/2.0)) 
				return true;
			else 
				return false;

		}

		void setFacingAngle(double facingAngle) { _facingAngle = facingAngle; }
		void setFiringArc(double firingArc) { _firingArc = fireArc; }
		void setRange(double range) { _range = range; }

		double getFacingAngle() { return _facingAngle; }
		double getFiringArc() { return _firingArc; }
		double getRange() { return _range; }

		void fire();
		

	protected:
		double _firingArc;
		double _facingAngle;
		double _range;

};

#endif //COMPONENT_WEAPON_H
