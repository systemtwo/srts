#include "Ship.h"
#include "ComponentHealth.h"
#include "ComponentNavigation.h"
#include "ComponentTargetting.h"
#include "ComponentWeapon.h"
#include "ComponentCollision.h"

Ship::Ship(std::string name, int team, ComponentNavigation* nav, ComponentTargetting* targ,
	   ComponentHealth* health, ComponentWeapon* weapon, ComponentCollision* coll)
	: _name(name),
	  _team(team),
	  _dead(false),
	  _state(MOVING),
	  _navigation(nav),
	  _targetting(targ),
	  _health(health),
	  _weapon(weapon),
	  _collision(coll)
{
}

Ship::~Ship() {
	//Clean up the rest of the ship
}

std::string Ship::getName() {
	return _name;
}

int Ship::getTeam() {
	return _team;
}

sf::Vector2f Ship::getPosition() {
	return _navigation->getPosition();
}

void Ship::setSelected(bool selected) {
	_selected = selected;
}

void Ship::setTargetShip(Ship* ship) {
	_targetting->setTargetShip(ship);
}

//Controller MUST call this! (AI or Player)
void Ship::setMoveLocation(double x, double y) {
	_navigation->setTarget(x, y);
	_state = MOVING;
}

