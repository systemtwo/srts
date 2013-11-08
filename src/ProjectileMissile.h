#ifndef PROJECTILE_MISSILE_H
#define PROJECTILE_MISSILE_H

#include <cmath>

#include "Projectile.h"
#include "ProjectileLaser.h"

#include "World.h"
#include "GeomUtil.h"

class ProjectileMissile : public Projectile {
	public:
		ProjectileMissile(double x, double y, double angle, int team, World* world)
			: Projectile(30.0, x, y, angle, team),
			  _world(world){
		}

		void update(double dt) { 
			double xspeed = SPEED * cos(_angle) * dt;
			double yspeed = SPEED * sin(_angle) * dt;

			_x += xspeed;
			_y += yspeed;

			//Find angle of closest ships

			for (auto ship : _world->getEnemyShips(_team)) {
				auto spos = ship->getPosition();
				if (hypot(spos.x - _x, spos.y - _y) < 100) {
					for (int i = 0; i <= 5; ++i) {
						double angle = atan2(spos.y - _y, spos.x - _x);
						_world->addProjectile(new ProjectileLaser(_x, _y, _angle + (i*PI/24), _team));
						_world->addProjectile(new ProjectileLaser(_x, _y, _angle - (i*PI/24), _team));
					}
					setDead(true);
				}
			}
		}

		void draw(sf::RenderWindow& window) { 
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color::Cyan);
			rect.setSize(sf::Vector2f(2, 5));
			rect.setPosition(getPosition());
			rect.setRotation(GeomUtil::radToDeg(_angle + PI/2));
			window.draw(rect);
		}

	private:
		const double SPEED = 200.0;
		World* _world;
};

#endif //PROJECTILE_MISSILE_H
