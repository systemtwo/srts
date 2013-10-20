#include <algorithm>

#include "World.h"

World::World() {
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

void World::addShip(Ship* ship) {
	_ships.push_back(ship);
}

void World::addBullet(Bullet* bullet) {
	_bullets.push_back(bullet);
}

bool World::isShipDead(Ship* ship) {
	if (std::find(_ships.begin(), _ships.end(), ship) != _ships.end())
		return false;
	else
		return true;
}

