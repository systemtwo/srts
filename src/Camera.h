#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
	public: 
		Camera(sf::RenderWindow& window) {
		}

	private:
		sf::RenderWindow& _window;
		sf::View _view;
};

#endif //CAMERA_H
