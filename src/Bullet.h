#ifndef BULLET_H
#define BULLET_H

class Bullet {
	public:
		Bullet(double x, double y, double angle, double speed, int team) 
			: _x(x),
			  _y(y),
			  _speed(speed),
			  _angle(angle),
			  _team(team) {
		}

		sf::Vector2f getPosition();
		sf::Vector2f getSize();
		int getTeam();

	private:
		double _x;
		double _y;
		double _speed;
		double _angle;
		double _team;
};

#endif //BULLET_H
