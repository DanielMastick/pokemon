#include "Team.hpp"
#include "MoveList.hpp"
#include <iostream>

using namespace std;


Team::Team()
{// Default constructor
    head = nullptr;
}

Team::~Team()
{// Default destructor - deallocate memory
    teamMember *tmp = head;
    teamMember *toDelete;
    if (tmp != nullptr)
    {
        while (tmp->next != nullptr)
        {
            toDelete = tmp;
            tmp = tmp->next;
            delete toDelete;
        }
        delete tmp;
        head = nullptr;
    }
    else
    {
        cout << "Team already empty" << endl;
    }
}

teamMember* Team::addMember(string name, Pokemon* pokeListRoot)
{// Add node to the end of the team LL
    teamMember* tmp = head;

    // Search for the pokemon with name
    cout << "Fetching " << name << endl;
    Pokemon *tempMon = getMon(pokeListRoot, name);
    cout << name << " is stored in " << tempMon << endl;

    if (tempMon != nullptr)
    {
        // Generate new team member and point it to the appropriate pokemon
        teamMember *newMember = new teamMember;

        Pokemon *newMon = new Pokemon;
        *newMon = *tempMon;
        newMember->mon = *newMon;
        newMember->next = nullptr;

        if (tmp != nullptr)
        {// Traverse to end of the team

            while (tmp->next != nullptr){
                tmp = tmp->next;
            }

            // Set end of list's next 
            tmp->next = newMember;
        } 
        else 
        {// Insert new pokemon as head of team
            head = newMember;
        }
    } else {
        cout << name << " is not a Pokemon, check your spelling" << endl;
    }
}

Pokemon* Team::getMon(Pokemon* root, string name)
{
    if (root == nullptr)
    {
        return root;
    }
    Pokemon *traverse = root;
    int check = 0;
    while (check == 0)
    {
        if (traverse->leftChild != nullptr && name < traverse->name)
        {
            traverse = traverse->leftChild;
        }
        else if (traverse->rightChild != nullptr && name > traverse->name)
        {
            traverse = traverse->rightChild;
        }
        else if (traverse->name == name)
        {
            check = 0;
            return traverse;
        }
        else
        {
            return nullptr;
        }
    }
}

void Team::makeTeam(int teamSize, Pokemon *pokeListRoot)
{// Prompt user for inputs and build a team
    int monCount = 0;
    string name;
    teamMember* tmp = head;
    while (monCount < teamSize)
    {
        cout << "Name of #" << monCount << " Mon: " << endl;
        getline(cin, name);

        // Call the addMember function
        addMember(name, pokeListRoot);
        monCount++;
    }
}

void Team::printTeam()
{// Print out contents of the team
    teamMember *traverse = head;
    while (traverse != nullptr)
    {
        cout << traverse->mon.name << "--" << traverse->mon.m1.name << "--";
        cout << traverse->mon.m2.name << "--" << traverse->mon.m3.name << "--" << traverse->mon.m4.name << endl;
        traverse = traverse->next;
    }
    cout << endl;
}