#include "Event.h"
#include <iostream>

void Event::SetForestEvent() {
	int RandomForestEvent = 1, EventChoice = 0;
	srand((unsigned int)time(0));
	//RandomForestEvent = rand() % 14 + 1;
	/////////////////////////////////////// EVENT 1 ///////////////////////////////////////
	if (RandomForestEvent == 1) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "As you traverse the forest, you hear the sounds of crackling fire.\n"
				"Upon closer inspection, you see a glowing light.\n"
				"A campfire burns brightly in front of you. \n\n"
				"1. Rest by the fire \n"
				"2. Ignore it.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You sat beside the campfire. Warmth soon wraps around your body. You feel revitalized!\n" << std::endl;
				// Full heals player
			}
			else if (EventChoice == 2) {
				std::cout << "You walk away from the campfire. The light slowly dims from distance.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 2 ///////////////////////////////////////
	else if (RandomForestEvent == 2) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "While walking, you suddenly see a cottage.The lights inside were turned on. \n"
				"Someones home.As you approach the cottage, the door suddenly opens. \n"
				"Oh, surprised to see you here, an adventurer per chance?\n"
				"I could let you rest here for a while if needed, an old lady said. \n\n"
				"1. Accept the offer.\n"
				"2. Refuse the offering.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "Dont worry about payment dear. Feel free to rest.\n" << std::endl;
				// Full heals player
			}
			else if (EventChoice == 2) {
				std::cout << "Oh you are busy I see. Well no worries my dear, have this piece of bread for the journey.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 3 ///////////////////////////////////////
	else if (RandomForestEvent == 3) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "You hear the sounds of a river flowing.As you approach,\n"
				"you see a flowing river of clear water. \n\n"
				"1. Scoop up some of the water.\n"
				"2. Drink the water.\n"
				"3. Ignore it.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You kneel down beside the river and scoop a bottle of the water.\n" << std::endl;
				// +1 Fresh water (item)
			}
			else if (EventChoice == 2) {
				std::cout << "You kneel down beside the river and started drinking.\n" << std::endl;
				// Full heals player
			}
			else if (EventChoice == 3) {
				std::cout << "You walk away from the river, the water continues to flow.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 4 ///////////////////////////////////////
	else if (RandomForestEvent == 4) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "While walking, you suddenly met a wandering traveller. \n"
				"He greets you, and you both start conversing.\n\n"
				"1. Ask for information.\n"
				"2. Ask for help.\n"
				"3. Say goodbye.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "Oh, Valdrek? They are a powerful force, that's for sure. \n"
					"I would not go messing around with them if I were you. Especially their Enforcers" << std::endl;
			}
			else if (EventChoice == 2) {
				std::cout << "Well, I cannot really follow you but, I can give you this from my travels.\n"
					"Hope it benefits you in your adventure.\n" << std::endl;
				// +1 Shark Tooth Charm (equipment)
			}
			else if (EventChoice == 3) {
				std::cout << "See you around adventurer, and stay safe.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 5 ///////////////////////////////////////
	else if (RandomForestEvent == 5) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "On your way, you stumbled upon a random chest. \n"
				"Upon closer inspection, you realised the lock was broken. \n\n"
				"1. Open Chest. \n"
				"2. Investigate closer.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "As you open the chest, you found a small trinket of what looks to be a sculpture of an idol.\n" << std::endl;
				// +1 Idol Trinket (Equipment)
			}
			else if (EventChoice == 2) {
				std::cout << "You careful inspected it, and opened it. And found a small trinket of what looks to be a sculpture of an idol.\n" << std::endl;
				// +1 Idol Trinket (Equipment)
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 6 ///////////////////////////////////////
	else if (RandomForestEvent == 6) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "You hear the sounds of water crashing down. \n"
				"Curious, you went that direction to take a look. \n"
				"What lies in front of you is a lake with a waterfall that seems like 10 houses tall!\n\n"
				"1. Rest by the lake. \n"
				"2. Swim into the waterfall. \n"
				"3. Scoop the water.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You rest your body by the river.\n"
					"You feel calm and relaxed as you sat, listening to the waterfall.\n" << std::endl;
				//full heals player
			}
			else if (EventChoice == 2) {
				std::cout << "You dove into the water. You then noticed a shining object underneath the waterfall. \n"
					"As you swam to the object, you discovered it was a ring.\n" << std::endl;
				// +1 HP ring (equipment)
			}
			else if (EventChoice == 3) {
				std::cout << "You kneel down beside the lake and scoop a bottle of the water.\n" << std::endl;
				// +1 Fresh water (item)
			}
			else {
				std::cout << "Invalid choice.";
			}
		}
	}
	/////////////////////////////////////// EVENT 7 ///////////////////////////////////////
	else if (RandomForestEvent == 7) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "As you walk, you feel droplets above you. And as you look up, you see dark clouds forming \n\n"
				"1. Continue Forward. \n"
				"2. Take shelter nearby.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You push on, ignoring the clouds.\n"
					"A sudden downpour hits you as you make your way.\n" << std::endl;
				// -10 HP
			}
			else if (EventChoice == 2) {
				std::cout << "tree big enough to cover you.\n"
					"The moment you settle under the cover of the tree, a sudden downpour happens.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 8 ///////////////////////////////////////
	else if (RandomForestEvent == 8) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "You chanced upon an open field.\n"
				"In the center of the field, a glowing plant can be seen.\n"
				"You approach the plant, curious, and see that it is abundant.\n\n"
				"1. Harvest a plant. \n"
				"2. Leave it be.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You bent down and plucked a few of the plants out.\n" << std::endl;
				// +2 Medicinal Herb (item)
			}
			else if (EventChoice == 2) {
				std::cout << "As you walk away, a sudden gust breezes past you.\n"
					"You suddenly feel energized, as if the plants were thanking you for not uprooting them.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 9 ///////////////////////////////////////
	else if (RandomForestEvent == 9) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "You approach a clearing in the forest.\n"
				"You then see what looks like a training ground, or what used to be one. \n"
				"You see a weapons rack and approach it. Surprisingly there were a few weapons scattered around, looks usable too!\n\n"
				"1.Pick up a weapon. \n"
				"2.Ignore and rest.\n"
				"3.Search around.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You picked up a weapon to your liking. It feels nice having something new.\n" << std::endl;
				// +1 Iron sword (Berserker) (equipment) or
				// +1 Iron Bow (Archer) (equipment) or
				// +1 Iron Staff (Mage) (equipment)
			}
			else if (EventChoice == 2) {
				std::cout << "You ignored the weapons and decided to take a power nap.\n" << std::endl;
				// +20 HP
			}
			else if (EventChoice == 3) {
				std::cout << "You decided to ignore the weapons and searched around.\n"
					"Surprisingly you found bread that did not seem mouldy. \n" << std::endl;
				// +2 Bread
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 10 ///////////////////////////////////////
	else if (RandomForestEvent == 10) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "On the way, you spot a white crow. An unusual sight.\n"
				"Upon closer inspection, you see the crow holding something in its beak.\n\n"
				"1.Get closer to the crow. \n"
				"2.Leave the crow.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "As you approach the crow, it flies away, leaving behind the item in its beak.\n"
					"Maybe you were destined to get it, maybe you will see the crow again.\n" << std::endl;
				// +1 silver bracelet (equipment)
			}
			else if (EventChoice == 2) {
				std::cout << "You decided to leave the animal alone. \n"
					"As you turn back, you see its red eyes constantly staring, never turning.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 11 ///////////////////////////////////////
	else if (RandomForestEvent == 11) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "You decided to take a short break under a tree. \n"
				"While resting, you realised that this was an apple tree. Above you an apple hangs.\n\n"
				"1.Attempt to jump and reach the apple. \n"
				"2.Hit the tree. \n"
				"3.Use your weapon to reach the apple.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You decided to jump for the apple. With each attempt you nearly reach it, but it was never enough. \n" << std::endl;
			}
			else if (EventChoice == 2) {
				std::cout << "You picked up your weapon and decided to strike the tree with it.\n"
					"The moment it impacts, multiple apples drop from the tree. \n" << std::endl;
				// +3 apples
			}
			else if (EventChoice == 3) {
				std::cout << "You picked up your weapon and start jumping, swinging at it. \n"
					"Eventually, your weapon knocks it down and you get the apple. \n" << std::endl;
				// +1 apples
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 12 ///////////////////////////////////////
	else if (RandomForestEvent == 12) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "You trekked through the forest, when you stumbled upon an active bee hive. \n"
				"You can hear the bees buzzing around. Looking closer, there seems to be sufficient honey available.\n\n"
				"1. Ignore the hive. \n"
				"2. Attempt to extract the honey. \n"
				"3. Hit the bee hive down.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You walked away from the hive. Bees still buzzing. \n" << std::endl;
			}
			else if (EventChoice == 2) {
				std::cout << "As you slowly approach the hive. Some of the bees curiously land on you.\n"
					"Despite it, you managed to get a bottle of honey.\n" << std::endl;
				// +1 Honey bottle
			}
			else if (EventChoice == 3) {
				std::cout << "Taking a page from wild bears, you picked up your weapon and swung hard at the hive.\n"
					"The impact causes the hive to fall, enraging the bees. But you are not letting this opportunity pass, \n"
					"you quickly extracted as much honey as you can as bees stung you from all sides. \n" << std::endl;
				// -15 HP
				// +2 Bottles of honey
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	/////////////////////////////////////// EVENT 13 ///////////////////////////////////////
	else if (RandomForestEvent == 13) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "While walking, you met a fellow adventurer. He greets you and you both engage in a conversation.\n\n"
				"1. Ask for information. \n"
				"2. Ask for help. \n"
				"3. Say goodbye.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "Hmm, Valdrek eh. I have not fought any of their warriors yet. But I heard their enforcers are strong. \n"
					"Especially their leader, you should not cross his path. \n" << std::endl;
			}
			else if (EventChoice == 2) {
				std::cout << "Sorry man, I can't help you out physically, but I can give you this. Hope it helps. \n" << std::endl;
				// +1 Wood Carved Necklace
			}
			else if (EventChoice == 3) {
				std::cout << "Pleasure meeting you. Here, take this for the road. Hope we get to adventure together another time.\n" << std::endl;
				// +1 fresh water
				// +2 bread
			}
			else {
				std::cout << "Invalid choice.";
			}
		}
	}
	/////////////////////////////////////// EVENT 14 ///////////////////////////////////////
	else if (RandomForestEvent == 14) {
		while (EventChoice != 1 && EventChoice != 2) {
			std::cout << "Walking along the road, you stumbled upon an abandoned caravan.\n"
				"Upon inspection, it seems that the owners were either robbed or left in a hurry.\n\n"
				"1. Loot what's left. \n"
				"2. Leave it behind.\n" << std::endl;
			std::cout << "What do you do? ";
			std::cin >> EventChoice;
			if (EventChoice == 1) {
				std::cout << "You went to the back of the caravan and checked around. To your luck, you found a charm inside.\n" << std::endl;
				//+1 Gem Charm
			}
			else if (EventChoice == 2) {
				std::cout << "You walk away from the caravan. It doesn't seem like it holds anything worth your time.\n" << std::endl;
			}
			else {
				std::cout << "Invalid choice.\n";
			}
		}
	}
	RandomForestEvent, EventChoice = 0;
}
/////////////////////////////////////// TRANSITION EVENT ///////////////////////////////////////
void Event::SetTransitionEvent() {
	int EventTransitionChoice = 0;
	while (EventTransitionChoice != 1 && EventTransitionChoice != 2) {
		std::cout << "After what felt like forever, you made it back. In front lies your hometown, \n"
			"captured by your enemies, now it is time to reclaim it back and avenge your loved ones. \n\n"
			"1. Move Forward. \n"
			"2. Try to run away.\n" << std::endl;
		std::cout << "What do you do? ";
		std::cin >> EventTransitionChoice;
		if (EventTransitionChoice == 1) {
			std::cout << "As you entered a hole in the wall, what awaits you are enemies everywhere, they have not noticed you, \n"
				"taking advantage of that, you hid somewhere safe in town.\n" << std::endl;
			//Go to Havenbrook events
		}
		else if (EventTransitionChoice == 2) {
			std::cout << "You try to run. But your hatred is build in too deep. You cannot run...\n" << std::endl;
			//Go to Havenbrook events
		}
		else {
			std::cout << "Invalid choice.\n" << std::endl;
		}
	}
}
