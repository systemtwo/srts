#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class World;
class ComponentNavigation;
class ComponentTargetting;
class ComponentHealth;
class ComponentWeapon;
class ComponentCollision;

class Ship {
	public:
		Ship(std::string name, int team, ComponentNavigation* nav, ComponentTargetting* targ,
		     ComponentHealth* health, ComponentWeapon* weapon, ComponentCollision* coll);
		~Ship();

		void setDead(bool dead) { _dead = dead; }
		bool isDead() { return _dead; }

		void updateComponents(double dt, World* world);
		
		virtual void update (double dt, World* world) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;

		std::string getName();
		int getTeam();
		sf::Vector2f getPosition();

		void setSelected(bool selected);
		void setTargetShip(Ship* ship);
		void setMoveLocation(double x, double y);

		enum State { MOVING, SCANNING, ATTACKING };
		enum ShipType { DRONE, BOMBER, DESTROYER }; 
	protected:
		std::string _name;
		int _team;
		bool _dead;
		bool _selected;

		State _state;

		std::unique_ptr<ComponentNavigation> _navigation;
		std::unique_ptr<ComponentTargetting> _targetting;
		std::unique_ptr<ComponentHealth> _health;
		std::unique_ptr<ComponentWeapon> _weapon;
		std::unique_ptr<ComponentCollision> _collision;
		
};

#endif //SHIP_H

