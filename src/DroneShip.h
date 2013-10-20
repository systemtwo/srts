#ifndef DRONE_SHIP_H
#define DRONE_SHIP_H

#include <string>

#include <SFML/System.hpp>

#include "Ship.h"
#include "ComponentHealth.h"
#include "ComponentNavigation.h"
#include "ComponentTargetting.h"
#include "ComponentWeapon.h"
#include "World.h"

class DroneShip : public Ship {
	enum State { MOVING, SCANNING, ATTACKING };

	public:
		DroneShip(double x, double y, int team);

		void update(double dt, World* world);
		void draw(sf::RenderWindow& window);
		
		sf::Vector2f getPosition();
		std::string getName();
		int getTeam();

		void setSelected(bool selected);
		void setMoveLocation(double x, double y);

	private:
		ComponentNavigation* _navigation;
		ComponentTargetting _targetting;
		ComponentHealth _health;
		ComponentWeapon* _weapon;

		bool _selected;
		int _team;
		State _state;

		const double SPEED = 100.0;
		const double TURNING_SPEED = 3.14;

};

#endif //DRONE_SHIP_H
