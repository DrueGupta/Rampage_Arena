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
		this->specialOneCost = 30;
		this->specialTwoName = "Comprehend Infinity";
		this->specialTwoCost = 60;
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
};
