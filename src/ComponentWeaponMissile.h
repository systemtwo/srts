#ifndef COMPONENT_WEAPON_MISSILE_H
#define COMPONENT_WEAPON_MISSILE_H

#include "ComponentWeapon.h"
#include "ProjectileMissile.h"
#include "GeomUtil.h"

class ComponentWeaponMissile : public ComponentWeapon {
	public:
		ComponentWeaponMissile(double x, double y, double angle, int team)
	       		: ComponentWeapon(3.14, 400, 1, 3.0, x, y, angle, team),
	       		  _cooldownLeft(_cooldown) { 
		}

		void fire(double dt, World* world) {
			if (_cooldownLeft < 0) {
				for (int i = 1; i <= 5; i++) {
					world->addProjectile(new ProjectileMissile(_x, _y, _facingAngle + (i * PI/6), _team, world));
					world->addProjectile(new ProjectileMissile(_x, _y, _facingAngle - (i * PI/6), _team, world));
				}
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

