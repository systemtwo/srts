#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

class Particle {
	public:
		Particle(double sourceX, double sourceY, double dstX, double dstY)
			: _x(sourceX),
			  _y(sourceY),
			  _dstX(dstX),
			  _dstY(dstY),
       			  _lifetimeLeft(3),
			  _dead(false) {
		}

		bool isDead() { return _dead; }
		
		void update(double dt) {
			_x += (_dstX - _x) * 0.01;
			_y += (_dstY - _y) * 0.01;
			_lifetimeLeft -= dt;
			if (_lifetimeLeft < 0) {
				_dead = true;
			}
		}

		void draw(sf::RenderWindow& window) {
			sf::RectangleShape point;
			point.setSize(sf::Vector2f(1, 1));
			point.setPosition(_x, _y);
			point.setFillColor(sf::Color::White);
			window.draw(point);
		}

	private:
		double _x;
		double _y;
		double _dstX;
		double _dstY;

		double _lifetimeLeft;
		bool _dead;
};

class ParticleManager {
	public:
		//Note frequency as a probability (0 <= x <= 1)
		ParticleManager(double x, double y, double frequency)
	       		: _x(x),
			  _y(y),
			  _probability(frequency),
       			  _emitting(false) {

		}

		void start() { _emitting = true; }
		void stop() { _emitting = false; }

		void setPosition(sf::Vector2f pos) { _x = pos.x; _y = pos.y; }
		void update(double dt) {
			if (_emitting) {
				if (rand() % 1000 < (int)(_probability * 1000.0)) {
					//New particle
					double dstX = (rand() % 50) - 25 + _x;
					double dstY = (rand() % 50) - 25 + _y;
					_particles.push_back(Particle(_x, _y, dstX, dstY));
				}
			}

			//Make p modifiable
			for (Particle& p : _particles) {
				p.update(dt);
			}
			
			//Remove dead particles
			std::vector<Particle>::size_type i = 0;
			while (i < _particles.size()) {
				if (_particles[i].isDead()) {
					_particles.erase(_particles.begin() + i);
				} else {
					i++;
				}
			}
		}

		void draw(sf::RenderWindow& window) { 
			for (auto p : _particles) {
				p.draw(window);
			}
		}

	private:
		double _x;
		double _y;
		double _probability;
		bool _emitting;
		std::vector<Particle> _particles;


};

#endif //PARTICLE_H
