#include "Event.h"
#include "Item.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;


// ============================================================
// CHECK IF EVENT WAS ALREADY USED
// ============================================================

bool Event::IsUsed(int event)
{
    for (int i = 0; i < usedEvents.size(); i++)
    {
        if (usedEvents[i] == event)
        {
            return true;
        }
    }

    return false;
}


// ============================================================
// HEAL FUNCTIONS
// ============================================================

void Event::HealToMax(Player* player)
{
    if (player == nullptr) return;

    player->setHealth(player->getMaxHealth());
    cout << "You have been fully healed!" << endl;
}

void Event::Heal20(Player* player)
{
    if (player == nullptr) return;

    int newHp = player->getHealth() + 20;
    if (newHp > player->getMaxHealth())
    {
        newHp = player->getMaxHealth();
    }
    player->setHealth(newHp);
    cout << "You recovered 20 HP." << endl;
}


// ============================================================
// DAMAGE FUNCTIONS
// ============================================================

void Event::Damage25Per(Player* player)
{
    if (player == nullptr) return;
    int dmg = (int)ceil(player->getHealth() * 0.25);
    int newHp = player->getHealth() - dmg;
    if (newHp < 0) {
        newHp = 0;
    }
    player->setHealth(newHp);
    cout << "You took " << dmg << " damage." << endl;
}

// ============================================================
// PLAYER CHOOSES ONE OF THREE RANDOM PATHS
// ============================================================

void Event::PathChoice(Player* player)
{
    ifstream inputFile("eventnames.txt");

    cout << "Current folder: "
        << filesystem::current_path()
        << endl;

    if (!inputFile.is_open())
    {
        cout << "ERROR: eventnames.txt could not be opened!" << endl;
        cout << "Current working directory may be wrong." << endl;
        return;
    }


    vector<string> eventNames;
    string line;

    // Read all event names from file
    while (getline(inputFile, line))
    {
        eventNames.push_back(line);
    }

    inputFile.close();


    // Make sure enough events exist
    if (eventNames.size() < 3)
    {
        cout << "Not enough events!\n";
        return;
    }


    // ---------------- PATH 1 ----------------

    int path1;

    do
    {
        path1 = rand() % eventNames.size();

    } while (IsUsed(path1));


    // ---------------- PATH 2 ----------------

    int path2;

    do
    {
        path2 = rand() % eventNames.size();

    } while (IsUsed(path2) || path2 == path1);


    // ---------------- PATH 3 ----------------

    int path3;

    do
    {
        path3 = rand() % eventNames.size();

    } while (IsUsed(path3) ||
        path3 == path1 ||
        path3 == path2);


    // ---------------- DISPLAY PATHS ----------------

    cout << "=====================================\n";
    cout << "Pick a Path\n\n";

    cout << "Path 1: " << eventNames[path1] << "\n";
    cout << "Path 2: " << eventNames[path2] << "\n";
    cout << "Path 3: " << eventNames[path3] << "\n";


    int choice;

    cout << "\nChoice: ";
    cin >> choice;


    int selectedEvent;


    // ---------------- PLAYER CHOICE ----------------

    if (choice == 1)
    {
        selectedEvent = path1;
    }
    else if (choice == 2)
    {
        selectedEvent = path2;
    }
    else if (choice == 3)
    {
        selectedEvent = path3;
    }
    else
    {
        cout << "Invalid choice.\n";
        return;
    }


    // Remember that the event has been used
    usedEvents.push_back(selectedEvent);


    // Run selected event
    ForestEvent(selectedEvent, player);
}


// ============================================================
// FOREST EVENT
// ============================================================

void Event::ForestEvent(int event, Player* player)
{
    ifstream inputFile("input.txt");

    vector<string> eventLines;
    string line;


    // event starts from 0 internally
    // so event + 1 matches EVENT 1, EVENT 2, etc.
    string eventMarker =
        "======EVENT " + to_string(event + 1) + "======";


    bool readingEvent = false;


    // ========================================================
    // READ CORRECT EVENT FROM FILE
    // ========================================================

    while (getline(inputFile, line))
    {
        // Start reading when correct event is found
        if (line == eventMarker)
        {
            readingEvent = true;
            continue;
        }


        // Stop when next event starts
        if (readingEvent &&
            line.find("======EVENT ") == 0)
        {
            break;
        }


        // Store event lines
        if (readingEvent)
        {
            eventLines.push_back(line);
        }
    }


    inputFile.close();


    // ========================================================
    // FIND THE CHOICE PROMPT
    // ========================================================

    int choicePrompt = -1;


    for (int i = 0; i < eventLines.size(); i++)
    {
        if (eventLines[i] == "What do you do? Choice:")
        {
            choicePrompt = i;
            break;
        }
    }


    // Make sure prompt exists
    if (choicePrompt == -1)
    {
        cout << "Choice prompt not found!\n";
        return;
    }


    // ========================================================
    // DISPLAY EVENT STORY AND CHOICES
    // ========================================================

    for (int i = 0; i < choicePrompt; i++)
    {
        cout << eventLines[i] << '\n';
    }


    cout << eventLines[choicePrompt] << " ";


    // ========================================================
    // PLAYER MAKES EVENT CHOICE
    // ========================================================

    int choice;

    cin >> choice;


    // Response starts after the choice prompt
    int responseIndex = choicePrompt + choice;


    // ========================================================
    // DISPLAY RESPONSE
    // ========================================================

    if (responseIndex < eventLines.size())
    {
        cout << '\n'
            << eventLines[responseIndex]
            << '\n';


        // ====================================================
        // EVENT ITEM REWARDS
        // ====================================================


        // ----------------------------------------------------
        // EVENT 1 - CAMPFIRE REST
        // Choice 1 gives full heal
        // ----------------------------------------------------

        if (event == 0 && choice == 1)
        {
            HealToMax(player);
        }


        // ----------------------------------------------------
       // EVENT 2 - FOREST COTTAGE
       // Choice 1 gives full heal
       // ----------------------------------------------------

        if (event == 1 && choice == 1)
        {
            HealToMax(player);
        }


        // ----------------------------------------------------
        // EVENT 2 - FOREST COTTAGE
        // Choice 2 gives Bread
        // ----------------------------------------------------

        if (event == 1 && choice == 2)
        {
            Item bread;

            bread.name = "Bread";
            bread.type = "Healing";
            bread.healAmount = 5;
            bread.atkBonus = 0;
            bread.consumable = true;

            player->AddItem(bread);
        }


        // ----------------------------------------------------
        // EVENT 3 - FLOWING RIVER
        // Choice 1 gives Water
        // ----------------------------------------------------

        if (event == 2 && choice == 1)
        {
            Item water;

            water.name = "Bottle of Water";
            water.type = "Healing";
            water.healAmount = 3;
            water.atkBonus = 0;
            water.consumable = true;

            player->AddItem(water);
        }


        // ----------------------------------------------------
       // EVENT 3 - FLOWING RIVER
       // Choice 2 gives full heal
       // ----------------------------------------------------

        if (event == 2 && choice == 2)
        {
            HealToMax(player);
        }


        // ----------------------------------------------------
        // EVENT 4 - WANDERING TRAVELLER
        // Choices can give a Charm
        // ----------------------------------------------------

        if (event == 3 && (choice == 2))
        {
            player->GetSharkToothCharm();
            cout << "You have recieved and equipped --Shark Tooth Charm--" << endl;
        }


        // ----------------------------------------------------
        // EVENT 5 - RANDOM CHEST
        // Choices can give a Trinket
        // ----------------------------------------------------

        if (event == 4 &&
            (choice == 1 || choice == 2 || choice == 3))
        {
            player->GetIdolTrinket();
            cout << "You have recieved and equipped --Idol Trinket--" << endl;
        }


        // ----------------------------------------------------
        // EVENT 6 - WATERFALL
        // Choice 1 gives full heal
        // ----------------------------------------------------

        if (event == 5 && choice == 1)
        {
            HealToMax(player);
        }


        // ----------------------------------------------------
        // EVENT 6 - WATERFALL
        // Choice 2 gives Ring
        // ----------------------------------------------------

        if (event == 5 && choice == 2)
        {
            player->GetHpRing();
            cout << "You have recieved and equipped --HP Ring--" << endl;
        }


        // ----------------------------------------------------
        // EVENT 6 - WATERFALL
        // Choice 3 gives Water
        // ----------------------------------------------------

        if (event == 5 && choice == 3)
        {
            Item water;

            water.name = "Bottle of Water";
            water.type = "Healing";
            water.healAmount = 3;
            water.atkBonus = 0;
            water.consumable = true;

            player->AddItem(water);
        }


        // ----------------------------------------------------
        // EVENT 7 - SUDDEN RAIN
        // Choice 1 loses 10 HP
        // ----------------------------------------------------

        if (event == 6 && choice == 1)
        {
            Damage25Per(player);
        }


        // ----------------------------------------------------
        // EVENT 8 - MEDICINAL HERBS
        // Choice 1 gives Medicinal Herb
        // ----------------------------------------------------

        if (event == 7 && choice == 1)
        {
            Item herb;

            herb.name = "Medicinal Herb";
            herb.type = "Healing";
            herb.healAmount = 8;
            herb.atkBonus = 0;
            herb.consumable = true;

            player->AddItem(herb);
        }


        // ----------------------------------------------------
        // EVENT 8 - MEDICINAL HERBS
        // Choice 2 gives 20 HP
        // ----------------------------------------------------

        if (event == 7 && choice == 2)
        {
            Heal20(player);
        }


        // ----------------------------------------------------
        // EVENT 9 - TRAINING GROUNDS
        // Choice 1 gives a Weapon
        // ----------------------------------------------------

        if (event == 8 && choice == 1)
        {
            Item weapon;

            weapon.name = "Old Weapon";
            weapon.type = "Weapon";
            weapon.healAmount = 0;
            weapon.atkBonus = 2;
            weapon.consumable = false;

            player->AddItem(weapon);
        }


        // ----------------------------------------------------
       // EVENT 9 - TRAINING GROUNDS
       // Choice 2 gives 20 HP
       // ----------------------------------------------------

        if (event == 8 && choice == 2)
        {
            Heal20(player);
        }


        // ----------------------------------------------------
        // EVENT 9 - TRAINING GROUNDS
        // Choice 3 gives Bread
        // ----------------------------------------------------

        if (event == 8 && choice == 3)
        {
            Item bread;

            bread.name = "Bread";
            bread.type = "Healing";
            bread.healAmount = 5;
            bread.atkBonus = 0;
            bread.consumable = true;

            player->AddItem(bread);
        }


        // ----------------------------------------------------
        // EVENT 10 - WHITE CROW
        // Choice 1 gives Mystery Item
        // ----------------------------------------------------

        if (event == 9 && choice == 1)
        {
            player->GetSilverBracelet();
            cout << "You have recieved and equipped --Silver Bracelet--" << endl;
        }


        // ----------------------------------------------------
        // EVENT 11 - APPLE TREE
        // Choice 2 gives Apples
        // ----------------------------------------------------

        if (event == 10 && choice == 2)
        {
            Item apple;

            apple.name = "Apple";
            apple.type = "Healing";
            apple.healAmount = 4;
            apple.atkBonus = 0;
            apple.consumable = true;

            player->AddItem(apple);
        }


        // ----------------------------------------------------
        // EVENT 11 - APPLE TREE
        // Choice 3 also gives Apple
        // ----------------------------------------------------

        if (event == 10 && choice == 3)
        {
            Item apple;

            apple.name = "Apple";
            apple.type = "Healing";
            apple.healAmount = 4;
            apple.atkBonus = 0;
            apple.consumable = true;

            player->AddItem(apple);
        }


        // ----------------------------------------------------
        // EVENT 12 - BEE HIVE
        // Choice 2 gives Honey
        // ----------------------------------------------------

        if (event == 11 &&
            (choice == 2))
        {
            Item honey;

            honey.name = "Honey";
            honey.type = "Healing";
            honey.healAmount = 6;
            honey.atkBonus = 0;
            honey.consumable = true;

            player->AddItem(honey);
        }


        // ----------------------------------------------------
       // EVENT 12 - BEE HIVE
       // Choice 3 give Honey also lose 15 HP
       // ----------------------------------------------------

        if (event == 11 &&
            (choice == 2 || choice == 3))
        {
            Item honey;

            honey.name = "Honey";
            honey.type = "Healing";
            honey.healAmount = 6;
            honey.atkBonus = 0;
            honey.consumable = true;

            player->AddItem(honey);
            Damage25Per(player);
        }


        // ----------------------------------------------------
        // EVENT 13 - FELLOW ADVENTURER
        // Choice 2 gives bread
        // ----------------------------------------------------

        if (event == 11 &&
            (choice == 2))
        {
            player->GetWoodCarvedNecklace();
            cout << "You have recieved and equipped --Wood Carved Necklace--" << endl;
        }

        // ----------------------------------------------------
        // EVENT 13 - FELLOW ADVENTURER
        // Choice 3 gives bread
        // ----------------------------------------------------

        if (event == 11 &&
            (choice == 3))
        {
            Item bread;

            bread.name = "Bread";
            bread.type = "Healing";
            bread.healAmount = 5;
            bread.atkBonus = 0;
            bread.consumable = true;

            player->AddItem(bread);
        }

        // ----------------------------------------------------
        // EVENT 14 - ABANDONED CARAVAN
        // Choice 1 gives Charm
        // ----------------------------------------------------

        if (event == 13 && choice == 1)
        {
            player->GetGemCharm();
            cout << "You have recieved and equipped --Gem Charm--" << endl;
        }


        // ----------------------------------------------------
       // EVENT 15 - GIANT TREE
       // Choice 1 gives full heal
       // ----------------------------------------------------

        if (event == 14 && choice == 1)
        {
            HealToMax(player);
        }


        // ----------------------------------------------------
        // EVENT 15 - GIANT TREE
        // Choice 2 gives Emblem
        // ----------------------------------------------------

        if (event == 14 && choice == 2)
        {
            player->GetTreeEmblem();
            cout << "You have recieved and equipped --Tree Emblem--" << endl;
        }


        // ----------------------------------------------------
        // EVENT 15 - GIANT TREE
        // Choice 3 gives Fruit
        // ----------------------------------------------------

        if (event == 14 && choice == 3)
        {
            Item fruit;

            fruit.name = "Forest Fruit";
            fruit.type = "Healing";
            fruit.healAmount = 5;
            fruit.atkBonus = 0;
            fruit.consumable = true;

            player->AddItem(fruit);
        }


        // ----------------------------------------------------
        // EVENT 16 - ???
        // Choice 1 gives 1/10 of Nail or lose 15 HP
        // ----------------------------------------------------

        if (event == 15 && choice == 1)
        {
            int Nail;
            Nail = rand() % 10;
            if (Nail == 9) {
                player -> GetReaperNail();
                cout << "You have rolled: " << Nail + 1 << endl;
                cout << "You have recieved and equipped --Reapers Nail--" << endl;
            }
            else {
                cout << "You have rolled: " << Nail + 1 << endl;
                Damage25Per(player);
            }
        }


        // ----------------------------------------------------
       // EVENT 16 - ???
       // Choice 2 lose 15 HP
       // ----------------------------------------------------

        if (event == 15 && choice == 2)
        {
            Damage25Per(player);
        }
    }
    else
    {
        cout << "Invalid choice.\n";
    }
}
