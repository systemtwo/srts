#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
	public:
		Projectile(double x, double y, double angle, double speed, int team) 
			: _x(x),
			  _y(y),
			  _speed(speed),
			  _angle(angle),
			  _team(team) {
		}

		sf::Vector2f getPosition() { return sf::Vector2f(_x, _y); }
		sf::Vector2f getSize();
		int getTeam();

		void update(double dt);
		void draw(sf::RenderWindow& window);

	private:
		double _x;
		double _y;
		double _speed;
		double _angle;
		double _team;
};

#endif //PROJECTILE_H
