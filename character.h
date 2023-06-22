#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>

class Item {
protected:
    std::string itemName;
    int itemDamage;
    int itemQuantity;
    static const std::vector<std::string> itemList;
    std::vector<std::string> tempItemList;
    const std::string itemListFile = "itemList.txt";
//    static std::map<std::string, double> itemDropRates;

public:
    Item();
    Item(std::string itemName, int itemQuantity, int itemDamage);
    virtual ~Item();

    std::vector<Item> itemListCreate();
    std::map<std::string, int> inventory;  // Map to store the items and their quantities
//    static std::map<std::string, double> getItemDropRates();

    void loadInventoryFromFile(const std::string& itemListFile);  // Load inventory from a file
    void saveInventoryToFile(const std::string& itemListFile);  // Save inventory to a file

    std::string get_itemName() const;
    int get_itemQuantity();
    int get_itemDamage() const;
};

class CharacterBase : public Item {
protected:
    std::string name;
    int strength, dexterity, endurance, intelligence, charisma;
    int experience, hp;

public:
    CharacterBase();
    CharacterBase(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience);
    CharacterBase(std::string itemName, int itemQuantity, int itemDamage);
    virtual ~CharacterBase();

    std::string get_name();
    int get_strength();
    int get_dexterity();
    int get_endurance();
    int get_intelligence();
    int get_charisma();
    int get_experience();
    int get_hp();

    int getEquipmentDamage() const;
    int getDefense() const;
    void reduceHP(int damage);
    bool isDefeated() const;

    void addItem(const Item& item, int quantity = 1);  // Add an item to the inventory
    void removeItem(const Item& item, int quantity = 1);  // Remove an item from the inventory
    void printInventory();  // Print the items in the inventory
    bool equipItem(const Item& item);  // Equip an item from the inventory
};

class Character : public CharacterBase {
protected:
    int level;
    std::vector<std::string> fightHistory;

public:
    Character();
    Character(int level);
    Character(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int hp, int experience);
    ~Character();

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
