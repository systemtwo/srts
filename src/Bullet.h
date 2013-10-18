#ifndef BULLET_H
#define BULLET_H

class Bullet {
	public:
		Bullet(double x, double y);
		sf::Vector2f getPosition();
		sf::Vector2f getSize();

	private:
		double _x;
		double _y;
};

#endif //BULLET_H
