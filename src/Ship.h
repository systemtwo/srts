#ifndef SHIP_H
#define SHIP_H

#include <string>

#include <SFML/System.hpp>

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


		virtual void update (double dt) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual sf::Vector2f getPosition() = 0;
		virtual std::string getName() = 0;

		virtual void setSelected(bool selected) = 0;
		virtual void setMoveLocation(double x, double y) = 0;
};

#endif //SHIP_H
