#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>

//===============Item struct============//

struct Item {
    std::string name;
    int attackBonus;
    int defenseBonus;
    int restoreHp;
    int quantity;
    Item(std::string n, int ab, int db, int rh, int q = 1) : name(n), attackBonus(ab), defenseBonus(db), restoreHp(rh), quantity(q) {}
};

//==================Character Base class==============//

class CharacterBase {
protected:
    std::string name;
    int strength, dexterity, endurance, intelligence, charisma;
    int experience, hp;

public:
    CharacterBase();
    CharacterBase(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience);
    virtual ~CharacterBase();

    std::string get_name();
    int get_strength();
    int get_dexterity();
    int get_endurance();
    int get_intelligence();
    int get_charisma();
    int get_experience();
    int get_hp();


    int getDefense() const;
    void reduceHP(int damage);
    bool isDefeated() const;
};

//================= Character class =================//

class Character : public CharacterBase {

protected:
    int level;
    std::vector<std::string> fightHistory;

public:
    Character();
    Character(int level);
    Character(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience);
    ~Character();



    int getEquipmentDamage() const;
    int get_level();
    const std::vector<std::string>& getFightHistory() const;
    void addFightToHistory(const std::string& fightInfo);  // Add this line
    void increase_experience(int value);
    void save_attributes();

    friend class Mage;
    friend class Warrior;
    friend class Berserker;
    friend class Thief;
};

//=============== Profession virtual class and its classes================//

class Profession {
public:
    virtual void increase_attribute(Character& character) = 0;
};

class Mage : public Profession {
public:
    void increase_attribute(Character& character);
};

class Warrior : public Profession {
public:
    void increase_attribute(Character& character);
};

class Berserker : public Profession {
public:
    void increase_attribute(Character& character);
};

class Thief : public Profession {
public:
    void increase_attribute(Character& character);
};

class Monster : public CharacterBase {
private:
    static const std::vector<std::string> monsterNames;

public:
    Monster();
    Monster(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience);
    ~Monster();

    std::string generate_random_name();
    void generate_attributes();
    void save_monsters();
    void save_monster();
    void clear_monster_list();

    int get_attack();
};

#endif
