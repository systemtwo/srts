#ifndef COMPONENT_WEAPON_BOMB_H
#define COMPONENT_WEAPON_BOMB_H

#include "ComponentWeapon.h"
#include "ProjectileBomb.h"
#include "GeomUtil.h"

class ComponentWeaponBomb : public ComponentWeapon {
	public:
		ComponentWeaponBomb(double x, double y, double angle, int team)
	       		: ComponentWeapon(0.5, 100, 1, 1.0, x, y, angle, team) { 
		}

		void fire(double dt, World* world) {
			if (_cooldownLeft < 0) {
				world->addProjectile(new ProjectileBomb(_x, _y, _facingAngle, _team));
				_cooldownLeft = _cooldown;
			} else  {
				_cooldownLeft -= dt;
			}

		}
	
	private:
		int _burstLeft;
		double _cooldownLeft;
};


#endif //COMPONENT_WEAPON_BOMB_H
