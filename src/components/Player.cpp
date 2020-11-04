#include "Player.h"

Player::Player() {
	_x = 1;
	_y = 1;
}

void Player::init(int level, int health, int ac, int mod, int dex, int pot, int gold, int vision){
	_level = level;
	_health = health;
	_armorClass = ac;
	_weaponMod = mod;
	_dexterity = dex;
	_healthPots = pot;
	_gold = gold;
	_visionRadius = vision;
}

//setters
void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

void Player::setHealth(int healthMod) {
	_health = _health + healthMod;
}

void Player::setArmorClass(int ac) {
	_armorClass = ac;
}

void Player::setWeaponMod(int mod) {
	_weaponMod = mod;
}

void Player::setDexterity(int dex) {
	_dexterity = dex;
}

void Player::setHealthPots(int pots) {
	_healthPots = pots;
}

void Player::setGold(int gold) {
	_gold = gold;
}

//getters
void Player::getPosition(int& x, int& y) {
	x = _x;
	y = _y;
}

int Player::getArmorClass() {
	return _armorClass;
}

int Player::getHealth() {
	return _health;
}

int Player::getDexterirty() {
	return _dexterity;
}

int Player::getHealthPots() {
	return _healthPots;
}

int Player::getWeaponMod() {
	return _weaponMod;
}

int Player::getGold() {
	return _gold;
}

int Player::getVision() {
	return _visionRadius;
}