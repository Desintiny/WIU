#pragma once
#include "Entity.h"
#include "Equipment.h"

class Player : public Entity
{
	int staminaPts, maxStaminaPts;

	int minRange;
	int maxRange;

	Equipment AttackRing;
	Equipment HpRing;
	Equipment SharkToothCharm;
	Equipment IdolTrinket;
	Equipment SilverBracelet;
	Equipment WoodCarvedNecklace;
	Equipment GemCharm;
	Equipment TreeEmblem;

public:
	Player(string n);
	~Player();

	void PlayerMovement(char sym, char input, char mapGrid[12][12]);
	bool PlayerAtkDirection(char input, int& dirRow, int& dirCol);

	virtual void PlayerAttack(Entity* enemy);
	virtual void EquipWeapon();

	void setStamina(int);
	int getStamina(void);

	void setMaxStamina(int);
	int getMaxStamina(void);

	void setMinRange(int);
	int getMinRange(void);

	void setMaxRange(int);
	int getMaxRange(void);

	int GetTotalHealth();	//Dsplay health w Equipment

	int GetAccuracy();	//Equipment Stats	
	int GetEquipmentHealth();
	int GetEquipmentDamage();

	void GetAttackRing();	//Indiv equipment
	void GetHpRing();
	void GetSharkToothCharm();
	void GetIdolTrinket();
	void GetSilverBracelet();
	void GetWoodCarvedNecklace();
	void GetGemCharm();
	void GetTreeEmblem();
};

