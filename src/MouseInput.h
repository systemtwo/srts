#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include "InputDevice.h"

//These are implementation specific
#include <SFML/Window.hpp>

class MouseInput : public InputDevice {
	public:
		MouseInput(sf::Window& window) 
			: _window(window) {
		}


		bool isSelecting() override {
			return sf::Mouse::isButtonPressed(sf::Mouse::Left);
		}

		bool isMoving() override {
			return sf::Mouse::isButtonPressed(sf::Mouse::Right);
		}

		double getX() override {
			return sf::Mouse::getPosition(_window).x;
		}

		double getY() override {
			return sf::Mouse::getPosition(_window).y;
		}
	
	private:
		sf::Window& _window;
};

#endif //MOUSE_INPUT_H
