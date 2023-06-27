#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <limits>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <memory>

#include "character.h"

using namespace std;

std::string fightResult;

template <typename CharacterType, typename MonsterType>
void fight(CharacterType& character, MonsterType& monster) {

    int damage;
    int iter = 0;

    std::cout << "\n\nmonster loaded successfully?" << std::endl;
    std::cout << "Name: " << monster.get_name() << std::endl;
    std::cout << "Strength: " << monster.get_strength() << std::endl;
    std::cout << "Dexterity: " << monster.get_dexterity() << std::endl;
    std::cout << "Endurance: " << monster.get_endurance() << std::endl;
    std::cout << "Intelligence: " << monster.get_intelligence() << std::endl;
    std::cout << "Charisma: " << monster.get_charisma() << std::endl;
    std::cout << "Current HP: " << monster.get_hp() << std::endl;
    std::cout << "Current Experience: " << monster.get_experience() << std::endl;

    std::cout << "\n\ncharacter: " << character.get_name() << std::endl;
    std::cout << "Strength: " << character.get_strength() << std::endl;
    std::cout << "Dexterity: " << character.get_dexterity() << std::endl;
    std::cout << "Endurance: " << character.get_endurance() << std::endl;
    std::cout << "Intelligence: " << character.get_intelligence() << std::endl;
    std::cout << "Charisma: " << character.get_charisma() << std::endl;
    std::cout << "HP: " << character.get_hp() << std::endl;
    std::cout << "Experience: " << character.get_experience() << std::endl;
    std::cout << "Level: " << character.get_level() << "\n\n" << std::endl;


    while (!character.isDefeated() && !monster.isDefeated()) {

        damage = character.getEquipmentDamage() - monster.getDefense();
        monster.reduceHP(damage);
        cout << character.get_name() << "  attacked with power:  " << character.getEquipmentDamage() << "  against monster:  " << monster.get_name() << " with deffence:  " << monster.getDefense() << "  for: " << damage << "  damage" << endl;
        cout << "monster's hp:  " << monster.get_hp() << endl;
        if (monster.isDefeated()) {
            std::cout << monster.get_name() << " has been defeated!\n";
            character.increase_experience(monster.get_experience());
            cout << character.get_name() << " got:  " << monster.get_experience() << "  ex" << endl;
            fightResult = "Hero won the fight!";
            character.addFightToHistory(fightResult);
            character.slayMonster();
            std::cout << "\nInventory after slaying a monster: " << std::endl;
            character.displayInventory();
            break;
        }

        damage = monster.get_attack() - character.getDefense();
        character.reduceHP(damage);
        cout << monster.get_name() << "  attacked with power:  " << monster.get_attack() << "  against monster:  " << character.get_name() << " with deffence:  " << character.getDefense() << "  for: " << damage << "  damage" << endl;
        cout << "Alchemist's hp:  " << character.get_hp() << endl;
        if (character.isDefeated()) {
            std::cout << character.get_name() << " has been defeated!\n";
            character.increase_experience(-monster.get_experience());
            cout << character.get_name() << " lost:  " << monster.get_experience() << "  ex" << endl;
            fightResult = "Hero lost the fight!";
            character.addFightToHistory(fightResult);
            break;
        }

        if (iter > 100){
            cout << "Fight ended in a draw" << endl;
            fightResult = "Draw!";
            character.addFightToHistory(fightResult);
            break;
        }
        iter++;
    }

}

void displayFightHistory(const Character& character) {
    std::cout << "Fight History:\n";
    const std::vector<std::string>& fightHistory = character.getFightHistory();
    for (auto it = fightHistory.rbegin(); it != fightHistory.rend(); ++it) {
        std::cout << "- " << *it << '\n';
    }
}

int main() {
    int choice;
    int pool = 30;
    std::string name, filename, inventoryFile;
    int strength, dexterity, endurance, intelligence, charisma, hp, experience, level;

    std::unique_ptr<Character> character;
    Monster monster(name, strength, dexterity, endurance, intelligence, charisma, hp, experience);
    Mage mage;
    Warrior warrior;
    Berserker berserker;
    Thief thief;

    do {
        std::cout << "1. Create new Alchemist\n2. Load Alchemist\n3. Generate list of monsters\n"
                     "4. Clear monster list\n5. Simulate fight with 5 generated monsters\n6. Show list of last 10 fights"
                     "\n7. Show Inventory\n8. Drink a Potion\n9. Exit" << std::endl;
        std::cin >> choice;

        if (choice == 1) {

            std::cout << "Enter character name: ";
            std::cin >> name;
            std::cout << "You have a Pool of 30 points in total to distribute among Character statistics"<< std::endl;
            std::cout << "Enter strength: ";
            std::cin >> strength;
            pool = pool - strength;
            std::cout << pool << " points left in your Pool"<< std::endl;
            std::cout << "Enter dexterity: ";
            std::cin >> dexterity;
            pool = pool - dexterity;
            std::cout << pool << " points left in your Pool"<< std::endl;
            std::cout << "Enter endurance: ";
            std::cin >> endurance;
            pool = pool - endurance;
            std::cout << pool << " points left in your Pool"<< std::endl;
            std::cout << "Enter intelligence: ";
            std::cin >> intelligence;
            pool = pool - intelligence;
            std::cout << pool << " points left in your Pool"<< std::endl;
            std::cout << "Enter charisma: ";
            std::cin >> charisma;
            hp = 100;
            experience = 0;

            character = std::make_unique<Character>(name, strength, dexterity, endurance, intelligence, charisma, hp, experience);

            int profession_choice;
            std::cout << "Choose elemental affinity:\n1. Ice\n2. Earth\n3. Fire\n4. Wind" << std::endl;
            std::cin >> profession_choice;

            switch (profession_choice) {
                case 1:
                    mage.increase_attribute(*character);
                    std::cout << "Intelligence increased by 5." << std::endl;
                    break;

                case 2:
                    warrior.increase_attribute(*character);
                    std::cout << "Endurance increased by 5." << std::endl;
                    break;

                case 3:
                    berserker.increase_attribute(*character);
                    std::cout << "Strength increased by 5." << std::endl;
                    break;

                case 4:
                    thief.increase_attribute(*character);
                    std::cout << "Dexterity increased by 5." << std::endl;
                    break;

                default:
                    std::cout << "Invalid profession choice." << std::endl;
                    break;
            }

            character->save_attributes();
            character->saveInventory();

            std::cout << "Character saved to file." << std::endl;
        }

        if (choice == 2) {
            std::cout << "Enter Character name: ";
            std::cin >> filename;

            std::ifstream file(filename + ".txt");
            if (file.is_open()) {
                file >> name;
                file >> strength;
                file >> dexterity;
                file >> endurance;
                file >> intelligence;
                file >> charisma;
                file >> hp;
                file >> experience;
                file >> level;

                character = std::make_unique<Character>(name, strength, dexterity, endurance, intelligence, charisma, hp, experience);

                std::cout << "Character loaded successfully." << std::endl;
                std::cout << "Name: " << character->get_name() << std::endl;
                std::cout << "Strength: " << character->get_strength() << std::endl;
                std::cout << "Dexterity: " << character->get_dexterity() << std::endl;
                std::cout << "Endurance: " << character->get_endurance() << std::endl;
                std::cout << "Intelligence: " << character->get_intelligence() << std::endl;
                std::cout << "Charisma: " << character->get_charisma() << std::endl;
                std::cout << "Current HP: " << character->get_hp() << std::endl;
                std::cout << "Current Experience: " << character->get_experience() << std::endl;
                std::cout << "Level: " << level << std::endl;
                std::cout << "Here's one PoH on the house ;) " << std::endl;
                character->addItem("Potion_of_Health");
                std::cout << endl;
            } else {
                std::cout << "Error loading file." << std::endl;
            }

            character->displayInventory();
        }

        if (choice == 3) {
            monster.save_monsters();
            std::cout << "Monsters saved to file." << std::endl;
        }

        if (choice == 4) {
            monster.clear_monster_list();
            std::cout << "Monsters liat cleared." << std::endl;
        }

        if (choice == 5) {

           // character = std::make_unique<Character>(name, strength, dexterity, endurance, intelligence, charisma, hp, experience);
            Monster monster;
            monster.save_monster();

//            monster.save_monster();

            std::cout << "monster loaded successfully?" << std::endl;
            std::cout << "Name: " << monster.get_name() << std::endl;
            std::cout << "Strength: " << monster.get_strength() << std::endl;
            std::cout << "Dexterity: " << monster.get_dexterity() << std::endl;
            std::cout << "Endurance: " << monster.get_endurance() << std::endl;
            std::cout << "Intelligence: " << monster.get_intelligence() << std::endl;
            std::cout << "Charisma: " << monster.get_charisma() << std::endl;
            std::cout << "Current HP: " << monster.get_hp() << std::endl;
            std::cout << "Current Experience: " << monster.get_experience() << std::endl;

            std::cout << "character loaded successfully?" << std::endl;
            std::cout << "character: " << character->get_name() << std::endl;
            std::cout << "Strength: " << character->get_strength() << std::endl;
            std::cout << "Dexterity: " << character->get_dexterity() << std::endl;
            std::cout << "Endurance: " << character->get_endurance() << std::endl;
            std::cout << "Intelligence: " << character->get_intelligence() << std::endl;
            std::cout << "Charisma: " << character->get_charisma() << std::endl;
            std::cout << "HP: " << character->get_hp() << std::endl;
            std::cout << "Experience: " << character->get_experience() << std::endl;
            std::cout << "Level: " << character->get_level() << std::endl;

            fight(*character, monster);

            std::cout << "character: " << character->get_name() << std::endl;
            std::cout << "Strength: " << character->get_strength() << std::endl;
            std::cout << "Dexterity: " << character->get_dexterity() << std::endl;
            std::cout << "Endurance: " << character->get_endurance() << std::endl;
            std::cout << "Intelligence: " << character->get_intelligence() << std::endl;
            std::cout << "Charisma: " << character->get_charisma() << std::endl;
            std::cout << "HP: " << character->get_hp() << std::endl;
            std::cout << "Experience: " << character->get_experience() << std::endl;
            std::cout << "Level: " << character->get_level() << std::endl;

            int exp_after_battle = character->get_experience();
            int lv_after_battle = character->get_level();

            std::ifstream inputFile(name + ".txt");
            std::ofstream tempFile("temp.txt");

            if (inputFile.is_open() && tempFile.is_open()) {
                std::string line;
                int lineNumber = 1;

                while (std::getline(inputFile, line)) {
                    if (lineNumber == 8 || lineNumber == 9) {
                        // Write the integer variables to the 6th and 7th lines
                        if (lineNumber == 8) {
                            tempFile << exp_after_battle << "\n";
                        } else if (lineNumber == 9) {
                            tempFile << lv_after_battle << "\n";
                        }
                    } else {
                        // Preserve the existing lines
                        tempFile << line << "\n";
                    }

                    lineNumber++;
                }

                inputFile.close();
                tempFile.close();

                std::cout << "Data written to temp file successfully." << std::endl;
            } else {
                std::cerr << "Unable to open the files." << std::endl;
            }

            std::string sourceFileName = "temp.txt";
            std::string destinationFileName = name + ".txt";

            std::ifstream sourceFile(sourceFileName);
            std::ofstream destinationFile(destinationFileName);

            if (sourceFile.is_open() && destinationFile.is_open()) {
                destinationFile << sourceFile.rdbuf();  // Copy the content from source to destination

                sourceFile.close();
                destinationFile.close();

                std::remove(sourceFileName.c_str());  // Delete the source file

                std::cout << "File content rewritten successfully." << std::endl;
            } else {
                std::cerr << "Unable to open the files." << std::endl;
            }

        }

        if(choice == 6){
            displayFightHistory(*character);
        }

        if(choice == 7){
            std::cout << "Inventory: " << std::endl;
            character->displayInventory();
        }

        if(choice == 8){
            string potinToBeDrunk;
            cout << "What potion do you want to drink? (eg.Potion_of_Health:) " << endl;
            cin >> potinToBeDrunk;
            character->drinkPotion(potinToBeDrunk);
        }

        if(choice == 9){
            character->saveInventory();
        }

    } while (choice != 9);





    return 0;
}
