#include "Event.h"
#include <iostream>

void Event::SetEvent() {
	int RandomEvent = 9; int EventChoice = 0;
	srand((unsigned int)time(0));
	//RandomEvent = rand() % 15 + 1;
/////////////////////////////////////// EVENT 1 ///////////////////////////////////////
	if (RandomEvent == 1) {
		std::cout << "As you traverse the forest, you hear the sounds of crackling fire.\n"
			"Upon closer inspection, you see a glowing light.\n"
			"A campfire burns brightly in front of you. \n"
			"1. Rest by the fire \n"
			"2. Ignore it" << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "You sat beside the campfire. Warmth soon wraps around your body. You feel revitalized!" << std::endl;
			// Full heals player
		}
		else if (EventChoice == 2) {
			std::cout << "You walk away from the campfire. The light slowly dims from distance" << std::endl;
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 2 ///////////////////////////////////////
		else if (RandomEvent == 2) {
			std::cout << "While walking, you suddenly see a cottage.The lights inside were turned on. \n"
				"Someones home.As you approach the cottage, the door suddenly opens. \n"
				"Oh, surprised to see you here, an adventurer per chance?\n"
				"I could let you rest here for a while if needed, an old lady said. \n"
				"1. Accept the offer.\n"
				"2. Refuse the offering." << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "Dont worry about payment dear. Feel free to rest" << std::endl;
				// Full heals player
			}
			else if (EventChoice == 2) {
				std::cout << "Oh you are busy I see. Well no worries my dear, have this piece of bread for the journey"<<std::endl;
			}
			else {
				std::cout << "Invalid choice.";
			}
		}
/////////////////////////////////////// EVENT 3 ///////////////////////////////////////
		else if (RandomEvent == 3) {
		std::cout << "You hear the sounds of a river flowing.As you approach,\n"
			"you see a flowing river of clear water. \n"
			"1. Scoop up some of the water.\n"
			"2. Drink the water.\n" 
			"3. Ignore it" << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "You kneel down beside the river and scoop a bottle of the water." << std::endl;
			// +1 Fresh water (item)
		}
		else if (EventChoice == 2) {
			std::cout << "You kneel down beside the river and started drinking." << std::endl;
			// Full heals player
		}
		else if (EventChoice == 3) {
			std::cout << "You walk away from the river, the water continues to flow." << std::endl;
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 4 ///////////////////////////////////////
		else if (RandomEvent == 4) {
		std::cout << "While walking, you suddenly met a wandering traveller. \n"
			"He greets you, and you both start conversing.\n"
			"1. Ask for information.\n"
			"2. Ask for help.\n"
			"3. Say goodbye." << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "Oh, Valdrek? They are a powerful force, that's for sure. \n"
				"I would not go messing around with them if I were you. Especially their Enforcers" << std::endl;
		}
		else if (EventChoice == 2) {
			std::cout << "Well, I cannot really follow you but, I can give you this from my travels.\n"
				"Hope it benefits you in your adventure." << std::endl;
			// +1 Shark Tooth Charm (equipment)
		}
		else if (EventChoice == 3) {
			std::cout << "See you around adventurer, and stay safe." << std::endl;
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 5 ///////////////////////////////////////
		else if (RandomEvent == 5) {
		std::cout << "On your way, you stumbled upon a random chest. \n"
			"Upon closer inspection, you realised the lock was broken. \n"
			"1. Open Chest. \n"
			"2. Investigate closer." << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "As you open the chest, you found a small trinket of what looks to be a sculpture of an idol." << std::endl;
			// +1 Idol Trinket (Equipment)
		}
		else if (EventChoice == 2) {
			std::cout << "You careful inspected it, and opened it. And found a small trinket of what looks to be a sculpture of an idol." << std::endl;
			// +1 Idol Trinket (Equipment)
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 6 ///////////////////////////////////////
		else if (RandomEvent == 6) {
		std::cout << "You hear the sounds of water crashing down. \n"
			"Curious, you went that direction to take a look. \n"
			"What lies in front of you is a lake with a waterfall that seems like 10 houses tall!\n"
			"1. Rest by the lake. \n"
			"2. Swim into the waterfall. \n"
			"3. Scoop the water." << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "You rest your body by the river.\n"
				"You feel calm and relaxed as you sat, listening to the waterfall." << std::endl;
			//full heals player
		}
		else if (EventChoice == 2) {
			std::cout << "You dove into the water. You then noticed a shining object underneath the waterfall. \n"
				"As you swam to the object, you discovered it was a ring"<< std::endl;
			// +1 HP ring (equipment)
		}
		else if (EventChoice == 3) {
			std::cout << "You kneel down beside the lake and scoop a bottle of the water" << std::endl;
			// +1 Fresh water (item)
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 7 ///////////////////////////////////////
		else if (RandomEvent == 7) {
		std::cout << "As you walk, you feel droplets above you. And as you look up, you see dark clouds forming \n"
			"1. Continue Forward. \n"
			"2. Take shelter nearby." << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "You push on, ignoring the clouds.\n"
				"A sudden downpour hits you as you make your way." << std::endl;
			// -10 HP
		}
		else if (EventChoice == 2) {
			std::cout << "tree big enough to cover you.\n"
				"The moment you settle under the cover of the tree, a sudden downpour happens." << std::endl;
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 8 ///////////////////////////////////////
		else if (RandomEvent == 8) {
		std::cout << "You chanced upon an open field.\n"
			"In the center of the field, a glowing plant can be seen.\n"
			"You approach the plant, curious, and see that it is abundant.\n"
			"1. Harvest a plant. \n"
			"2. Leave it be." << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "You bent down and plucked a few of the plants out." << std::endl;
			// +2 Medicinal Herb (item)
		}
		else if (EventChoice == 2) {
			std::cout << "As you walk away, a sudden gust breezes past you.\n"
				"You suddenly feel energized, as if the plants were thanking you for not uprooting them." << std::endl;
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 9 ///////////////////////////////////////
		else if (RandomEvent == 9) {
		std::cout << "You approach a clearing in the forest.\n"
			"You then see what looks like a training ground, or what used to be one. \n"
			"You see a weapons rack and approach it. Surprisingly there were a few weapons scattered around, looks usable too!\n"
			"1.Pick up a weapon. \n"
			"2.Ignore and rest.\n"
			"3.Search around." << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "You picked up a weapon to your liking. It feels nice having something new." << std::endl;
			// +1 Iron sword (Berserker) (equipment) or
			// +1 Iron Bow (Archer) (equipment) or
			// +1 Iron Staff (Mage) (equipment)
		}
		else if (EventChoice == 2) {
			std::cout << "You ignored the weapons and decided to take a power nap." << std::endl;
			// +20 HP
		}
		else if (EventChoice == 3) {
			std::cout << "You decided to ignore the weapons and searched around.\n"
				"Surprisingly you found bread that did not seem mouldy" << std::endl;
			// +2 Bread
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 10 ///////////////////////////////////////
		else if (RandomEvent == 10) {
		std::cout << "On the way, you spot a white crow. An unusual sight.\n"
			"Upon closer inspection, you see the crow holding something in its beak.\n"
			"1.Get closer to the crow. \n"
			"2.Leave the crow."<< std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventChoice;
		if (EventChoice == 1) {
			std::cout << "As you approach the crow, it flies away, leaving behind the item in its beak.\n"
				"Maybe you were destined to get it, maybe you’ll see the crow again" << std::endl;
			// +1 silver bracelet (equipment)
		}
		else if (EventChoice == 2) {
			std::cout << "You decided to leave the animal alone. \n"
				"As you turn back, you see its red eyes constantly staring, never turning." << std::endl;
		}
		else {
			std::cout << "Invalid choice.";
		}
	}
/////////////////////////////////////// EVENT 11 ///////////////////////////////////////
		else if (RandomEvent == 11) {}
		else if (RandomEvent == 12) {}
		else if (RandomEvent == 13) {}
		else if (RandomEvent == 14) {}
		else if (RandomEvent == 15) {}
}