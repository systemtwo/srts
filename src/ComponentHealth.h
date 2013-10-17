#ifndef COMPONENT_HEALTH
#define COMPONENT_HEALTH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ComponentHealth {
	public:
		ComponentHealth(double maxHealth)
			: _maxHealth(maxHealth),
	       		  _health(maxHealth) {
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
			r.setFillColor(_color);
			r.setSize(_size);
			r.setPosition(x, y);
			window.draw(r);
		}
	
	private:
		sf::Color _color;
		double _maxHealth;
		double _health;
		sf::Vector2f _size;
};

#endif //COMPONENT_HEALTH
