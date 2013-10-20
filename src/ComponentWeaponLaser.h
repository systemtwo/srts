#ifndef COMPONENT_WEAPON_LASER_H
#define COMPONENT_WEAPON_LASER_H

#include "ComponentWeapon.h"
#include "ProjectileLaser.h"
#include "GeomUtil.h"

class ComponentWeaponLaser : public ComponentWeapon {
	public:
		ComponentWeaponLaser(double x, double y, double angle, int team)
	       		: ComponentWeapon(0.5, 100, x, y, angle, team) { 
		}

		void fire(World* world) {
			world->addProjectile(new ProjectileLaser(_x, _y, _facingAngle, _team));
		}
	
	private:
		const double RANGE = 100.0;
		const double FIRING_ARC = PI / 6.0;
};


#endif //COMPONENT_WEAPON_LASER_H
