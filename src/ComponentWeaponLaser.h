#ifndef COMPONENT_WEAPON_LASER_H
#define COMPONENT_WEAPON_LASER_H

#include "ComponentWeapon.h"
#include "ProjectileLaser.h"
#include "GeomUtil.h"

class ComponentWeaponLaser : public ComponentWeapon {
	public:
		ComponentWeaponLaser(double x, double y, double angle, int team)
	       		: ComponentWeapon(0.5, 100, 4, 0.20, x, y, angle, team) { 
		}

		void fire(double dt, World* world) {
			if (_cooldownLeft < 0) {
				world->addProjectile(new ProjectileLaser(_x, _y, _facingAngle, _team));
				_cooldownLeft = _cooldown;
			} else  {
				_cooldownLeft -= dt;
			}

		}
	
	private:
		const double RANGE = 100.0;
		const double FIRING_ARC = PI / 6.0;

		int _burstLeft;
		double _cooldownLeft;
};


#endif //COMPONENT_WEAPON_LASER_H
