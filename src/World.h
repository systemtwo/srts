#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Ship.h"
#include "Bullet.h"

class World {
	public:
		World();
		std::vector<Ship*> getTeamShips(int team);
		std::vector<Ship*> getAllShips();
		std::vector<Bullet*> getBullets();

		void addShip(Ship* ship);
		void addBullet(Bullet* bullet);
	
	private:
		std::vector<Ship*> _ships;
		std::vector<Bullet*> _bullets;
};


#endif //WORLD_H
