#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
	public:
		Projectile(double damage, double x, double y, double angle, int team) 
			: _x(x),
			  _y(y),
			  _angle(angle),
			  _team(team), 
       			  _damage(damage),
       			  _dead(false) {
		}

		sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }
		sf::Vector2f getSize() { return sf::Vector2f(0,0); }
		int getTeam() { return _team; }
		double getDamage() { return _damage; }

		void setDead(bool dead) { _dead = dead; }
		bool isDead() { return _dead; }

		virtual void update(double dt) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;

	protected:
		double _x;
		double _y;
		double _angle;
		double _team;
		double _damage;
		bool _dead;
};

#endif //PROJECTILE_H
