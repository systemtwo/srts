#ifndef COMPONENT_HEALTH_H
#define COMPONENT_HEALTH_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ComponentHealth {
	public:
		ComponentHealth(double maxHealth)
			: _maxHealth(maxHealth),
	       		  _health(maxHealth),
       			  _color(sf::Color::Red) {
		}

		void setColor(sf::Color color) { _color = color; }
		void setHealthPercent(double percent) { _health = _maxHealth * percent / 100.0; }
		void setHealthValue(double value) { _health = value; }
		bool add(double value) { _health += value; return _health > _maxHealth; }
		void setSize(sf::Vector2f size) { _size = size; }
		
		sf::Color getColor() { return _color; }
		double getHealthPercent() { return (_health/_maxHealth) * 100.0; }
		double getHealthValue() { return _health; }
		sf::Vector2f getSize() { return _size; }

		void draw(sf::RenderWindow& window, double x, double y) {
			sf::RectangleShape r;
			sf::Vector2f modSize(_size.x * getHealthPercent()/100.0, _size.y);
			r.setFillColor(_color);
			r.setSize(modSize);
			r.setPosition(x, y);
			window.draw(r);
		}
	
	private:
		sf::Color _color;
		double _maxHealth;
		double _health;
		sf::Vector2f _size;
};

#endif //COMPONENT_HEALTH_H
