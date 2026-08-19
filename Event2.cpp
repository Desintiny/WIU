#include "Event2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Event2::PathChoice()
{
    ifstream inputFile("eventnames.txt");

    vector<string> eventNames;
    string line;

    while (getline(inputFile, line)) {
        eventNames.push_back(line);
    }

    inputFile.close();

    int path1 = rand() % eventNames.size();

    int path2 = rand() % eventNames.size();
    while (path2 == path1) {
        path2 = rand() % eventNames.size();
    }

    int path3 = rand() % eventNames.size();
    while (path3 == path1 || path3 == path2) {
        path3 = rand() % eventNames.size();
    }

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
        selectedEvent = path1;
    else if (choice == 2)
        selectedEvent = path2;
    else if (choice == 3)
        selectedEvent = path3;
    else {
        cout << "Invalid choice.\n";
        return;
    }

    // Run the selected event
    ForestEvent(selectedEvent);
}

void Event2::ForestEvent(int event)
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cout << "Could not open input.txt!\n";
        return;
    }

    vector<string> eventLines;
    string line;

    // Event numbers in your txt are 1-15
    string eventMarker = "======EVENT " + to_string(event + 1) + "======";

    bool readingEvent = false;

    // Find and read the selected event
    while (getline(inputFile, line))
    {
        if (line == eventMarker)
        {
            readingEvent = true;
            continue;
        }

        // Stop when the next event starts
        if (readingEvent && line.find("======EVENT ") == 0)
        {
            break;
        }

        if (readingEvent)
        {
            eventLines.push_back(line);
        }
    }

    inputFile.close();

    // Find the choice prompt
    int choicePrompt = -1;

    for (int i = 0; i < eventLines.size(); i++)
    {
        if (eventLines[i] == "What do you do? Choice:")
        {
            choicePrompt = i;
            break;
        }
    }

    // Make sure the prompt was found
    if (choicePrompt == -1)
    {
        cout << "Choice prompt not found!\n";
        return;
    }

    // Print the event description and choices
    for (int i = 0; i < choicePrompt; i++)
    {
        cout << eventLines[i] << '\n';
    }

    // Print choice prompt and let player enter choice
    cout << eventLines[choicePrompt] << " ";

    int choice;
    cin >> choice;

    // Response starts immediately after the choice prompt
    int responseIndex = choicePrompt + choice;

    // Check that the response exists
    if (responseIndex < eventLines.size())
    {
        cout << '\n' << eventLines[responseIndex] << '\n';
    }
    else
    {
        cout << "Invalid choice.\n";
    }
}