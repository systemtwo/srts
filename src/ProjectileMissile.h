#ifndef PROJECTILE_MISSILE_H
#define PROJECTILE_MISSILE_H

#include <cmath>

#include "Projectile.h"

#include "World.h"
#include "GeomUtil.h"

class ProjectileMissile : public Projectile {
	public:
		ProjectileMissile(double x, double y, double angle, int team, World* world)
			: Projectile(30.0, x, y, angle, team),
			  _world(world),
       			  _targettedShip(nullptr), 
       			  _angle(angle) {
		}

		void update(double dt) { 
			//Targetting
			if (_targettedShip != nullptr && _world->isShipDead(_targettedShip)) {
				_targettedShip = nullptr;
			}
			if (_targettedShip == nullptr) {
				//Scan for new ship
				for (auto ship : _world->getEnemyShips(_team)) {
					double distX = ship->getPosition().x - _x;
					double distY = ship->getPosition().y - _y;
					if (hypot(distX, distY) < SCAN_RADIUS && ship->getName().compare("Drone") == 0) {
						_targettedShip = ship;
						break;
					}
				}
				for (auto ship : _world->getEnemyShips(_team)) {
					double distX = ship->getPosition().x - _x;
					double distY = ship->getPosition().y - _y;
					if (hypot(distX, distY) < SCAN_RADIUS && ship->getName().compare("Bomber") == 0) {
						_targettedShip = ship;
						break;
					}
				}
				for (auto ship : _world->getEnemyShips(_team)) {
					double distX = ship->getPosition().x - _x;
					double distY = ship->getPosition().y - _y;
					if (hypot(distX, distY) < SCAN_RADIUS && ship->getName().compare("Destroyer") == 0) {
						_targettedShip = ship;
						break;
					}
				}
				for (auto ship : _world->getEnemyShips(_team)) {
					double distX = ship->getPosition().x - _x;
					double distY = ship->getPosition().y - _y;
					if (hypot(distX, distY) < SCAN_RADIUS && ship->getName().compare("Mothership") == 0) {
						_targettedShip = ship;
						break;
					}
				}
			}

			//Moving code
			if (_targettedShip != nullptr) {
				//Fix angle if needed
				if (_angle > (3.0 * PI))
					_angle -= 2.0 * PI;
				if (_angle < -PI) 
					_angle += 2.0 * PI;


				//Cross product method
				double vecTargetX = _targettedShip->getPosition().x - _x;
				double vecTargetY = _targettedShip->getPosition().y - _y;

				double vecFacingX = cos(_angle);
				double vecFacingY = sin(_angle);


				if (((vecTargetX * vecFacingY) - (vecTargetY * vecFacingX)) > 0) 
					_angle -= TURNING_SPEED * dt;
				else
					_angle += TURNING_SPEED * dt;

				
				//Move with turning
				double xmove = SPEED * cos(_angle) * dt;
				double ymove = SPEED * sin(_angle) * dt;

				_x += xmove;
				_y += ymove;
			} else {
				//Go straight
				double xmove = SPEED * cos(_angle) * dt;
				double ymove = SPEED * sin(_angle) * dt;

				_x += xmove;
				_y += ymove;
			}

			/*
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
			}*/
		}

		void draw(sf::RenderWindow& window) { 
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color::Cyan);
			rect.setSize(sf::Vector2f(2, 5));
			rect.setPosition(_x, _y);
			rect.setRotation(GeomUtil::radToDeg(_angle + PI/2));
			window.draw(rect);
		}

	private:
		const double SPEED = 200.0;
		const double TURNING_SPEED = 3.0 * PI;
		const double SCAN_RADIUS = 500;
		World* _world;
		Ship* _targettedShip;
		double _angle;
};

#endif //PROJECTILE_MISSILE_H
