#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <list>

#include "World.h"
#include "Ship.h"
#include "DroneShip.h"
#include "ShipBomber.h"
#include "ShipType.h"

class Factory {
	public: 
		Factory(int team) 
			: _team(team),
			  _income(100),
			  _currBuildShip(ShipType::NONE),
			  INCOME_CYCLE_DURATION(5) {

		}

		void update(double dt, World* world) {
			_incomeTimer -= dt;
			if (_incomeTimer <= 0) {
				_money += _income;
				_incomeTimer = INCOME_CYCLE_DURATION;
				std::cout << "+$" << _income << std::endl;
			}

			if (_buildTimer <= 0) {
				switch (_currBuildShip) {
					case ShipType::DRONE:
						world->addShip(new DroneShip(rand() % 50, rand() % 50, _team));
						break;
					case ShipType::BOMBER:
						world->addShip(new ShipBomber(rand() % 50, rand() % 50, _team));
						break;
					case ShipType::DESTROYER:
						break;
					case ShipType::NONE:
						break;
				}

				_currBuildShip = ShipType::NONE;

				if (_buildQueue.size() > 0) {
					switch (_buildQueue.front()) {
						case ShipType::DRONE:
							_buildTimer = 1.0;	
							_currBuildShip = _buildQueue.front();
							break;
						case ShipType::BOMBER:
							_buildTimer = 2.0;	
							_currBuildShip = _buildQueue.front();
							break;
						case ShipType::DESTROYER:
							_buildTimer = 5.0;	
							_currBuildShip = _buildQueue.front();
							break;
						default:
							break;
							//We shoudn't get here!
					}
					_buildQueue.pop_front();
				}


			}
			_buildTimer -= dt;
		}


		void createShip(ShipType shipType) {
			//Check to see if we have enough money here
			switch (shipType) {
				case ShipType::DRONE:
					if (_money >= 100) {
						_money -= 100;
						_buildQueue.push_back(shipType);
					}
					break;
				case ShipType::BOMBER:
					if (_money >= 300) {
						_money -= 300;
						_buildQueue.push_back(shipType);
					}
					break;
				case ShipType::DESTROYER:
					if (_money >= 400) {
						_money -= 400;
						_buildQueue.push_back(shipType);
					}
					break;
				default:
					break;
			}
		}

		bool upgrade() { return false; }

		int getMoney() { return _money; }
		int getIncome() { return _income; }

	private:
		int _team;
		int _money;
		int _income;

		std::list<ShipType> _buildQueue;
		ShipType _currBuildShip; //Ship that is being built
		double _buildTimer; //How long until the ship is done


		double _incomeTimer;

		const double INCOME_CYCLE_DURATION;

};

#endif //FACTORY_H

