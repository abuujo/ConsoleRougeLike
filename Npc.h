#pragma once
// Non Playable Character


class Npc
{
public:
	Npc(int health, int ac, int mod, int dex, int x, int y);
	//getters
	void getPosition(int& x, int& y);
	int getHealth();
	int getArmorClass();
	int getWeaponMod();
	int getDexterirty();

	//setters
	void setPosition(int x, int y);
	void setHealth(int healthMod);

private:
	//properties
	int _health;
	int _armorClass;
	int _weaponMod;
	int _dexterity;

	//position
	int _x;
	int _y;
};

