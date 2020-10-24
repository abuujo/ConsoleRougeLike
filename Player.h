#pragma once
// Lets mimic DND stats
class Player
{

public:
	Player();

	void init(int level, int health, int ac, int mod, int dex, int pot, int gold);

	//setters
	void setPosition(int x, int y);
	void setHealth(int healthMod);
	void setArmorClass(int ac);
	void setWeaponMod(int mod);
	void setDexterity(int dex);
	void setHealthPots(int pot);
	void setGold(int gold);

	//getters
	void getPosition(int& x, int& y);
	int getHealth();
	int getArmorClass();
	int getWeaponMod();
	int getDexterirty();
	int getHealthPots();
	int getGold();

private:
	//properties
	int _level;
	int _health;
	int _armorClass;
	int _weaponMod;
	int _dexterity;

	//inventory 
	int _healthPots;
	int _gold;

	//position
	int _x;
	int _y;

};

