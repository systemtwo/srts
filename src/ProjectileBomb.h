#ifndef PROJECTILE_BOMB_H
#define PROJECTILE_BOMB_H

#include <cmath>

#include "Projectile.h"

class ProjectileBomb : public Projectile {
	public:
		ProjectileBomb(double x, double y, double angle, int team)
			: Projectile(40.0, x, y, angle, team) {
		}

		void update(double dt) { 
			double xspeed = SPEED * cos(_angle) * dt;
			double yspeed = SPEED * sin(_angle) * dt;

			_x += xspeed;
			_y += yspeed;
		}

		void draw(sf::RenderWindow& window) { 
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color::Cyan);
			rect.setSize(sf::Vector2f(2, 2));
			rect.setPosition(getPosition());
			rect.setRotation(GeomUtil::radToDeg(_angle + PI/2));
			window.draw(rect);
		}

	private:
		const double SPEED = 200.0;
};

#endif //PROJECTILE_BOMB_H
