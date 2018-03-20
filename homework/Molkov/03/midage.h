#pragma once
#include <string>



class Item {
protected:
	//Unit* item_owner;
	const std::string name;
	unsigned durability;
	bool is_available = true;// ���� durability ���� ���������� ���� ���������� ������, ���� �������� � �� ������ ������ ������������
};

class Unit {
protected:
	Armor* armor;
	Weapon* weapon;
	const std::string name;
	unsigned hp, attack, defense;
};

class Animal
{
protected:
	const std::string name;
	unsigned hp;
};

class Weapon : public Item {
protected:
	unsigned damage;
	unsigned range;
};

////
class Shovel : public Weapon
{

};

class Sword : public Weapon
{

};

class Bow : public Weapon
{

};
////
class Armor : public Item
{

protected:
	unsigned defense;
};

class Hauberk : public Armor
{

};

class Lats : public Armor
{

};
////
class Farmer : public Unit
{

};

class Archer : public Unit
{

};

class Knight : public Unit
{

};


class Pig : public Animal
{

};
