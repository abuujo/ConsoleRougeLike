#include "Npc.h"

Npc::Npc(int health, int ac, int mod, int dex, int x, int y) {
	_health = health;
	_armorClass = ac;
	_weaponMod = mod;
	_dexterity = dex;
	_x = x;
	_y = y;
}

//setters
void Npc::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Npc::setHealth(int health) {
	_health += health;
}

//getters
void Npc::getPosition(int& x, int& y) {
	x = _x;
	y = _y;
}

int Npc::getHealth() {
	return _health;
}

int Npc::getArmorClass() {
	return _armorClass;
}

int Npc::getWeaponMod() {
	return _weaponMod;
}

int Npc::getDexterirty() {
	return _dexterity;
}