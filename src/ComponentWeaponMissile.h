#ifndef COMPONENT_WEAPON_MISSILE_H
#define COMPONENT_WEAPON_MISSILE_H

#include "ComponentWeapon.h"
#include "ProjectileMissile.h"
#include "GeomUtil.h"

class ComponentWeaponMissile : public ComponentWeapon {
	public:
		ComponentWeaponMissile(double x, double y, double angle, int team)
	       		: ComponentWeapon(3.14, 400, 1, 2.5, x, y, angle, team) { 
		}

		void fire(double dt, World* world) {
			if (_cooldownLeft < 0) {
				world->addProjectile(new ProjectileMissile(_x, _y, _facingAngle, _team, world));
				_cooldownLeft = _cooldown;
			} else  {
				_cooldownLeft -= dt;
			}

		}
	
	private:
		int _burstLeft;
		double _cooldownLeft;
};


#endif //COMPONENT_WEAPON_MISSILE_H

