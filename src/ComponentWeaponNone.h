#ifndef COMPONENT_WEAPON_NONE_H
#define COMPONENT_WEAPON_NONE_H

#include "ComponentWeapon.h"

class ComponentWeaponNone : public ComponentWeapon {
	public:
		ComponentWeaponNone(double x, double y, double angle, int team)
	       		: ComponentWeapon(0.0, 0, 0, 0, x, y, angle, team) { 
		}

		void fire(double dt, World* world) {
		}
};

#endif //COMPONENT_WEAPON_NONE_H
