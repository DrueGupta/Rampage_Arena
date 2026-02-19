#pragma once
#include "Player.h"
using namespace std;

class Cthulhu : public Player
{
public:
	Cthulhu(string name) : Player(name)
	{
		this->health = 450;
		this->armor = 20;
		this->dodge = 10;
		this->toHit = 50;
		this->critChance = 10;
		this->fixedDamage = 10;
		this->varDamage = 40;
		this->resource = 0;
		this->resourceName = "Insanity";
		this->specialOneName = "Mind breaker";
		this->specialOneCost = 40;
		this->specialTwoName = "Comprehend Mortality";
		this->specialTwoCost = 90;
		this->durabilityLossPercent = 0.10;
	}
	void startTurn() override
	{
		this->resource += 15;
		if (this->resource > 200)
		{
			this->resource = 200;
		}
	}
	bool specialOne(Player* target) override
	{
		if (this->resource < this->specialOneCost)
		{
			cout << "Not enough " << this->resourceName << " to do that." << endl;
			return false;
		}
		this->resource -= this->specialOneCost;
		bool stunned = false;
		for (Effect effect : target->getEffects())
		{
			if(effect.effectType == "STUN")
			{
				stunned = true;
			}
			if (stunned)
			{
				cout << target->getName() << " is stunned and cannot hurt themselves" << endl;
				return false;
			}
		}
		int ogCritChance = target->getCritChance();
		int ogDodge = target->getDodge();
		int ogToHit = target->getToHit();
		bool dead = false;
		cout << this->name << " used their psychic powers to implant the knowledge of the Old in " << target->getName() 
			<< ", driving them insane and causing them to hurt themselves." << endl;
		target->setCritChance(100);
		target->setToHit(100);
		target->setDodge(0);
		target->attack(target, "PHYS");
		target->setCritChance(ogCritChance);
		target->setDodge(ogDodge);
		target->setToHit(ogToHit);
		return dead;
	}
	bool specialTwo(Player* target) override
	{
		if (this->resource < this->specialTwoCost)
		{
			cout << "Not enough " << this->resourceName << " to do that." << endl;
			return false;
		}
		this->resource -= this->specialTwoCost;
		Effect death;
		death.effectType = "MORT";
		death.effectDMG = 0;
		death.duration = rand() % 5 + 4;
		cout << this->name << " cast an ancient spell on " << target->getName() << ". " << target->getName()
			<< " lifespan has been shorten by an exponential amount. How much is unknown, but what they do know is that they don't have long..." << endl;
		target->getEffects().push_back(death);
		return false;
	}
};
