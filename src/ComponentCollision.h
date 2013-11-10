#ifndef COMPONENT_COLLISION_H
#define COMPONENT_COLLISION_H

class ComponentCollision {
	public:
		ComponentCollision(double radius, double x, double y) 
			: _x(x),
			  _y(y),
			  _radius(radius),
       			  _accuDamage(0) {
	       	}

		void setPosition(double x, double y) { _x = x; _y = y; }
		void setPosition(sf::Vector2f loc) { setPosition(loc.x, loc.y); }

		void update(std::vector<Projectile*> projectiles) {
			for(auto p : projectiles) {
				auto loc = p->getPosition();
				if (hypot(loc.x - _x, loc.y - _y) < _radius) {
					_accuDamage += p->getDamage();
					p->setDead(true);
				}
			}
		}

		double getDamage() {
			double tempDamage = _accuDamage;
			_accuDamage = 0;
			return tempDamage;
		}

	private:
		double _x; 
		double _y;
		double _radius;
		double _accuDamage; //Accumulated damage
};

#endif //COMPONENT_COLLISION_H
