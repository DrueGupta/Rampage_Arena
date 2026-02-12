#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Effect
{
	string effectType;
	int effectDMG;
	int duration;
};

class Player
{
protected:
	string name;
	vector<Effect> effects;
	int health;
	int armor;
	int dodge;
	int toHit;
	int critChance;
	int fixedDamage;
	int varDamage;
	int resource;
	string resourceName;
	string specialOneName;
	int specialOneCost;
	string specialTwoName;
	int specialTwoCost;
	int durabilityLossPercent;
public:
	Player(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return this->name;
	}
	string getSpecialOneName()
	{
		return this->specialOneName;
	}
	string getSpecialTwoName()
	{
		return this->specialTwoName;
	}
	int getSpecialOneCost()
	{
		return this->specialOneCost;
	}
	int getSpecialTwoCost()
	{
		return this->specialTwoCost;
	}
	bool startTurn()
	{

	}
	bool endTurn()
	{

	}
	bool takeDamage(int damage, string type)
	{
		//armor
		if (type == "PHYS" && this->armor > 0)
		{
			cout << this->name << "'s armor reduced damage by" << this->armor << endl;
			damage -= this->armor;
			this->armor -= (damage * this->durabilityLossPercent);
			if (armor <= 0)
				cout << this->name << "'s armor has broken and shattered into inumberable pieces" << endl;
			if (this->armor < 0)
				this->armor = 0;
		}
		this->health -= damage;
		return this->health <= 0;
	}
	bool attack(Player* target, string type)
	{
		//is attack successful?
		int atkRoll = rand() % 100 + 1;
		if (atkRoll < 100 - (this->toHit - target->dodge))
		{
			//unsuccessful
			cout << this->name << " swung their weapon at " << target->name << " and missed like a dumbass." << endl;
			return false;
		}
		//successful
		int damage = rand() % this->varDamage + 1 + this->fixedDamage;
		if (atkRoll > (100 - this->critChance))
		{
			cout << "!!CRITICAL STRIKE!!" << endl;
			damage *= 2;

		}
		cout << this->name << " sung their weapon at " << target->name << " and hit them for " << damage << endl;
		//damage resistance
		return target->takeDamage(damage, "PHYS");
	}
	void die()
	{

	}
	void displayStatus()
	{
		cout << left << setw(18) << this->name << "Health: " << right << setw(5) << this->health
			<< this->resourceName << ": " << setw(5) << this->resource <<
			"Armor: " << setw(5) << this->armor << "    [ ";
		for (Effect effect : this->effects)
		{
			cout << effect.effectType << " ";
		}
		cout << "]" << endl;
	}
	bool processEffects()
	{

	}
	bool specialOne(Player* target)
	{

	}
	bool specialTwo(Player* target)
	{

	}
};
