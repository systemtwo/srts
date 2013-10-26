#include <algorithm>

#include "World.h"

World::World(double arenaWidth, double arenaHeight) 
	: _arenaWidth(arenaWidth),
	  _arenaHeight(arenaHeight) {
}

std::vector<Ship*> World::getAllShips() {
	return _ships;
}

std::vector<Ship*> World::getTeamShips(int team) {
	std::vector<Ship*> marked;
	for (auto ship : _ships) {
		if (ship->getTeam() == team)
			marked.push_back(ship);
	}
	return marked;
}

std::vector<Ship*> World::getEnemyShips(int myTeam) {
	std::vector<Ship*> marked;
	for (auto ship : _ships) {
		if (ship->getTeam() != myTeam)
			marked.push_back(ship);
	}
	return marked;
}

std::vector<Projectile*> World::getAllProjectiles() {
	return _projectiles;
}

void World::addShip(Ship* ship) {
	_ships.push_back(ship);
}

void World::addProjectile(Projectile* projectile) {
	_projectiles.push_back(projectile);
}

bool World::isShipDead(Ship* ship) {
	if (std::find(_ships.begin(), _ships.end(), ship) != _ships.end())
		return false;
	else
		return true;
}

void World::cleanProjectiles() {
	//Remove bullets that are off the field
	//See: http://stackoverflow.com/questions/8597240/how-to-delete-an-element-from-a-vector-while-looping-over-it/8597330#8597330
	//See: http://stackoverflow.com/a/8628963
	
	std::vector<Projectile*>::size_type i = 0;
	while (i < _projectiles.size()) {
		auto ploc = _projectiles[i]->getPosition();
		if (ploc.x < 0 ||
		    ploc.x > _arenaWidth ||
		    ploc.y < 0 ||
		    ploc.y > _arenaHeight) {
			delete _projectiles[i];
			_projectiles.erase(_projectiles.begin() + i);
		} else {
			i++;
		}
	}
}
