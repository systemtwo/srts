#ifndef BULLET_H
#define BULLET_H

class Bullet {
	public:
		Bullet(double x, double y, double angle, double speed);
		sf::Vector2f getPosition();
		sf::Vector2f getSize();

	private:
		double _x;
		double _y;
		double _speed;
		double _angle;
};

#endif //BULLET_H
