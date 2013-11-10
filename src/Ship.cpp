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
	  _selected(false),
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

double Ship::getAngle() {
	return _navigation->getAngle();
}

void Ship::setSelected(bool selected) {
	_selected = selected;
}

void Ship::setTargetShip(Ship* ship) {
	_targetting->setTargetShip(ship);
	_state = ATTACKING;
}

//Controller MUST call this! (AI or Player)
void Ship::setMoveLocation(double x, double y) {
	_navigation->setTarget(x, y);
	_state = MOVING;
}

void Ship::updateComponents(double dt, World* world) {
	_navigation->update(dt);
	_targetting->setOrigin(_navigation->getPosition());
	_weapon->setOrigin(_navigation->getPosition());
	_weapon->setFacingAngle(_navigation->getAngle());
	//Should be:
	//1) If move command is given discard any targetting and do not scan
	//2) If not moving + no move command, target an enemy
	//3) If we already have a target, keep following it unless 1)
	
	//Move this into a switch() {case}?
	if (_state == MOVING && _navigation->atTargetLocation()) {
		//Ship arrived where player directed, so begin scanning to attack
		_state = SCANNING;
		_targetting->setOrigin(_navigation->getPosition());

	}

	if (_state == MOVING) {
		//Should also scan for ships in front of it so it can fire while moving
		if (_targetting->checkInAngle(world->getEnemyShips(_team), _navigation->getAngle(), _weapon->getFiringArc()))
			_weapon->fire(dt, world);
	}

	if (_state == SCANNING) {
		if (_targetting->getTargetShip() == NULL) {
			//No Ship targetted
			_targetting->scan(world->getEnemyShips(_team));
		} else if (world->isShipDead(_targetting->getTargetShip())) {
			//Targetted ship is dead / does not exist
			_targetting->scan(world->getEnemyShips(_team));
		} else {
			//Ship has been found
			_state = ATTACKING;
		}
	}

	if (_state == ATTACKING) {
		if (world->isShipDead(_targetting->getTargetShip())) {
			std::cout << "Ship is dead" << std::endl;
			_state = SCANNING;
		} else {
			_navigation->setTarget(_targetting->getTargetShip()->getPosition());
			_targetting->setOrigin(_navigation->getPosition());
			_weapon->setOrigin(_navigation->getPosition());
			_weapon->setFacingAngle(_navigation->getAngle());

			if (_weapon->inFiringArc(_targetting->getTargetAngle()))
				_weapon->fire(dt, world);
		}
	}

	//Collision code
	_collision->setPosition(_navigation->getPosition());
	_collision->update(world->getEnemyProjectiles(_team));
	_health->add(_collision->getDamage()*-1.0);

	if (_health->getHealthValue() <= 0)
		setDead(true);
}
