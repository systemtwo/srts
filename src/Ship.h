#ifndef SHIP_H
#define SHIP_H

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class World;
class Ship {
	public:
		/*
		virtual void update (double dt) {}
		virtual void draw(sf::RenderWindow& window) {}
		virtual sf::Vector2f getPosition() { return sf::Vector2f(0,0); };
		virtual std::string getName() { return ""; };

		virtual void setSelected(bool selected) { };
		virtual void setMoveLocation(double x, double y) {};
		*/

		Ship() 
			: _dead(false) {
		}

		void setDead(bool dead) { _dead = dead; }
		bool isDead() { return _dead; }

		virtual void update (double dt, World* world) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual sf::Vector2f getPosition() = 0;
		virtual std::string getName() = 0;
		virtual int getTeam() = 0;

		virtual void setSelected(bool selected) = 0;
		virtual void setMoveLocation(double x, double y) = 0;
		virtual void setTargetShip(Ship* ship) = 0;


	private:
		bool _dead;
};

#endif //SHIP_H
