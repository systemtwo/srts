#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
	public: 
		Camera(sf::RenderWindow& window, double x, double y) 
			: _window(window),
			  _x(x),
			  _y(y){
			
			_view.setSize(_window.getDefaultView().getSize());

		}

		void move(double x, double y) {
			_x += x;
			_y += y;
		}

		void setPosition(double x, double y) {
			_x = x;
			_y = y;
		}

		void resetPosition() {
			_view.setCenter(_window.getDefaultView().getCenter());
			_window.setView(_view);
		}

		sf::Vector2f getPosition() {
			return sf::Vector2f(_x, _y);
		}

		void update() {
			double tx = _x + _view.getSize().x/2.0;
			double ty = _y + _view.getSize().y/2.0;

			_view.setCenter(sf::Vector2f(tx, ty));
			_window.setView(_view);
		}

	private:
		sf::RenderWindow& _window;
		sf::View _view;

		//Note: these are top left coordinates
		double _x;
		double _y;

};

#endif //CAMERA_H
