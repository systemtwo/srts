#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Ship.h"
#include "Projectile.h"

class World {
	public:
		World();
		std::vector<Ship*> getTeamShips(int team);
		std::vector<Ship*> getEnemyShips(int myTeam);
		std::vector<Ship*> getAllShips();
		std::vector<Projectile*> getAllProjectiles();

		void addShip(Ship* ship);
		void addProjectile(Projectile* projectile);

		bool isShipDead(Ship* ship);
	
	private:
		std::vector<Ship*> _ships;
		std::vector<Projectile*> _projectiles;
};


#endif //WORLD_H
