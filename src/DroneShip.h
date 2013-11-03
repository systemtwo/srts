#ifndef DRONE_SHIP_H
#define DRONE_SHIP_H

#include <string>

#include <SFML/System.hpp>

#include "Ship.h"
#include "ComponentHealth.h"
#include "ComponentNavigation.h"
#include "ComponentTargetting.h"
#include "ComponentWeapon.h"
#include "ComponentCollision.h"
#include "World.h"

class DroneShip : public Ship {
	public:
		DroneShip(double x, double y, int team);

		void update(double dt, World* world);
		void draw(sf::RenderWindow& window);
		
	private:
		const double SPEED = 100.0;
		const double TURNING_SPEED = 3.14;

};

#endif //DRONE_SHIP_H
