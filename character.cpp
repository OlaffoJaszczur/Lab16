#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

#include "character.h"


// =========== CharacterBase ==========//


CharacterBase::CharacterBase() = default;

CharacterBase::~CharacterBase() = default;

CharacterBase::CharacterBase(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience)
        : name(name), strength(strength), dexterity(dexterity), endurance(endurance), intelligence(intelligence), charisma(charisma), hp(hp), experience(experience) {
    this->name = name;
    this->strength = strength;
    this->dexterity = dexterity;
    this->endurance = endurance;
    this->intelligence = intelligence;
    this->charisma = charisma;
    this->hp = hp;
    this->experience = experience;
}

int CharacterBase::getDefense() const {
    return endurance;
}

void CharacterBase::reduceHP(int damage) {
    if (damage <= 0){
        hp -= 0;
    } else {
        hp -= damage;
    }
    if (hp < 0) {
        hp = 0;
    }
}

bool CharacterBase::isDefeated() const {
    return hp <= 0;
}



// ===========  Character  ==============//


Character::Character() = default;

Character::Character(int level) : level(level) {
    this->level = level;
}

Character::Character(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience) : CharacterBase(name, strength, dexterity, endurance, intelligence, charisma, hp, experience) {
    this->hp = hp;
    this->experience = experience;

}

Character::~Character() = default;

const std::vector<std::string>& Character::getFightHistory() const {
    return fightHistory;
}

void Character::addFightToHistory(const std::string& fightInfo) {
    fightHistory.insert(fightHistory.begin(), fightInfo);  // Insert the fight at the beginning of the vector
    if (fightHistory.size() > 10) {
        fightHistory.pop_back();  // Remove the oldest fight if the history exceeds 10 fights
    }
}

int Character::getEquipmentDamage() const {
    return (strength);
}

void Character::save_attributes() {
    level = 1;
    hp = 100;
    std::ofstream file(name + ".txt");
    if (file.is_open()) {
        file << name << std::endl;
        file << strength << std::endl;
        file << dexterity << std::endl;
        file << endurance << std::endl;
        file << intelligence << std::endl;
        file << charisma << std::endl;
        file << hp << std::endl;
        file << experience << std::endl;
        file << level << std::endl;
        file.close();
    }
}

std::string CharacterBase::get_name() {
    return name;
}

int CharacterBase::get_strength() {
    return strength;
}

int CharacterBase::get_dexterity() {
    return dexterity;
}

int CharacterBase::get_endurance() {
    return endurance;
}

int CharacterBase::get_intelligence() {
    return intelligence;
}

int CharacterBase::get_charisma() {
    return charisma;
}

int CharacterBase::get_experience() {
    return experience;
}

int CharacterBase::get_hp() {
    return hp;
}

int Character::get_level() {
    return level;
}

void Character::increase_experience(int value) {
    experience += value;
    if (experience < 0){
        experience = 0;
    }
    level = experience / 100 + 1;
}

void Mage::increase_attribute(Character& character) {
    character.intelligence += 5;
}

void Warrior::increase_attribute(Character& character) {
    character.endurance += 5;
}

void Berserker::increase_attribute(Character& character) {
    character.strength += 5;
}

void Thief::increase_attribute(Character& character) {
    character.dexterity += 5;
}


// ============== Monster ==============//


Monster::Monster() = default;

Monster::Monster(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience) : CharacterBase(name, strength, dexterity, endurance, intelligence, charisma, hp, experience) {
    this->hp = hp;
    this->experience = experience;

}

Monster::~Monster() = default;

const std::vector<std::string> Monster::monsterNames = {
        "Goblin",
        "Orc",
        "Troll",
        "Vampire",
        "Werewolf",
        "Zombie",
        "Skeleton",
        "Ghost",
        "Witch"
};

std::string Monster::generate_random_name() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, monsterNames.size() - 1);
    return monsterNames[dis(gen)];
}

void Monster::generate_attributes() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    strength = dis(gen);
    dexterity = dis(gen);
    endurance = dis(gen);
    intelligence = dis(gen);
    charisma = dis(gen);
    hp = rand() % 100 + 1;
    experience = rand() % 100 + 1;
    name = generate_random_name();
}

void Monster::save_monsters() {
    Monster monster;
    srand(time(NULL));
    std::ofstream file;
    file.open(("monsters.txt"), std::ofstream::app);
    if (file.is_open()) {
        int monsterNum = 1;

        monster.generate_attributes(); // Assuming this method generates random attributes for the monster

        file << "\n" << monster.get_name() << monsterNum << std::endl;
        file << monster.get_strength() << std::endl;
        file << monster.get_dexterity() << std::endl;
        file << monster.get_endurance() << std::endl;
        file << monster.get_intelligence() << std::endl;
        file << monster.get_charisma() << std::endl;
        file << monster.get_hp() << std::endl;
        file << monster.get_experience() << "\n" << std::endl;

        file << "--------------------------------------------------------" << std::endl;
        file.close();
    }
}

void Monster::save_monster(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    strength = dis(gen);
    dexterity = dis(gen);
    endurance = dis(gen);
    intelligence = dis(gen);
    charisma = dis(gen);
    hp = rand() % 100 + 1;
    experience = rand() % 100 + 1;
    name = generate_random_name();

    std::ofstream file;
    file.open(("monsters.txt"), std::ofstream::app);
    if (file.is_open()) {
        Monster monster;
        file << "\n" << monster.get_name() << std::endl;
        file << monster.get_strength() << std::endl;
        file << monster.get_dexterity() << std::endl;
        file << monster.get_endurance() << std::endl;
        file << monster.get_intelligence() << std::endl;
        file << monster.get_charisma() << std::endl;
        file << monster.get_hp() << std::endl;
        file << monster.get_experience() << "\n" << std::endl;

        file << "--------------------------------------------------------" << std::endl;
        file.close();
    }
}

void Monster::clear_monster_list() {
    std::ofstream file;
    file.open(("monsters.txt"));
    if (file.is_open()) {
        file << "Monster list:" << std::endl;
        file.close();
    }
}

int Monster::get_attack() {
    return strength;
}

