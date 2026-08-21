///////////////////////////// OUT-DATED DONT USE /////////////////////////////
#include "Event2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool Event2::IsUsed(int event)
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

void Event2::PathChoice()
{
    ifstream inputFile("eventnames.txt");
    vector<string> eventNames;
    string line;
    while (getline(inputFile, line))
    {
        eventNames.push_back(line);
    }
    inputFile.close();
    if (eventNames.size() < 3)
    {
        cout << "Not enough events!\n";
        return;
    }
    int path1;  // Pick Path 1
    do
    {
        path1 = rand() % eventNames.size();
    } while (IsUsed(path1));
    int path2;   // Pick Path 2

    do
    {
        path2 = rand() % eventNames.size();
    } while (IsUsed(path2) || path2 == path1);
    int path3;   // Pick Path 3

    do
    {
        path3 = rand() % eventNames.size();
    } while (IsUsed(path3) || path3 == path1 || path3 == path2);
    cout << "=====================================\n";
    cout << "Pick a Path\n\n";
    cout << "Path 1: " << eventNames[path1] << "\n";
    cout << "Path 2: " << eventNames[path2] << "\n";
    cout << "Path 3: " << eventNames[path3] << "\n";
    int choice;
    cout << "\nChoice: ";
    cin >> choice;
    int selectedEvent;
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
    usedEvents.push_back(selectedEvent);    // Remember the selected event
    ForestEvent(selectedEvent);  // Run the selected event
}


void Event2::ForestEvent(int event)
{
    ifstream inputFile("input.txt");
    vector<string> eventLines;
    string line;
    string eventMarker = "======EVENT " + to_string(event + 1) + "======";  // Read 1 to 15

    bool readingEvent = false;
    while (getline(inputFile, line))
    {
        if (line == eventMarker)
        {
            readingEvent = true;
            continue;
        }
        if (readingEvent && line.find("======EVENT ") == 0)  // Finds and stop
        {
            break;
        }
        if (readingEvent)
        {
            eventLines.push_back(line);
        }
    }
    inputFile.close();
    int choicePrompt = -1;  // Find the choice prompt
    for (int i = 0; i < eventLines.size(); i++)
    {
        if (eventLines[i] == "What do you do? Choice:")
        {
            choicePrompt = i;
            break;
        }
    }
    if (choicePrompt == -1)     // Make sure the prompt was found
    {
        cout << "Choice prompt not found!\n";
        return;
    }
    for (int i = 0; i < choicePrompt; i++)  // Print the event description and choices
    {
        cout << eventLines[i] << '\n';
    }
    cout << eventLines[choicePrompt] << " ";    // Print choice prompt

    int choice;
    cin >> choice;
    int responseIndex = choicePrompt + choice;  // Response starts immediately after the choice prompt
    if (responseIndex < eventLines.size())  // Check that the response exists
    {
        cout << '\n' << eventLines[responseIndex] << '\n';
    }
    else
    {
        cout << "Invalid choice.\n";
    }
}
