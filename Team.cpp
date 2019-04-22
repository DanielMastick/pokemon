#include "Team.hpp"
#include "MoveList.hpp"
#include "TypeGraph.hpp"
#include <iostream>
#include <random>

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
    Pokemon *tempMon = getMon(pokeListRoot, name);

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
{//	Get pointer to Pokemon struct
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
        //cout << traverse << endl;
        cout << traverse->mon.name << " [hp:" << traverse->mon.hp << "]   " << traverse->mon.m1.name << "--";
        cout << traverse->mon.m2.name << "--" << traverse->mon.m3.name << "--" << traverse->mon.m4.name << endl;

        //cout << traverse->next << endl;
        traverse = traverse->next;
    }
    cout << endl;
}

bool Team::checkStatus()
{// Check if current or all Pokemon in team are not fainted, return 1 if all is good
	if (head->mon.hp > 0) {
		cout << "Pokemon " << head->mon.name << " has " << head->mon.hp  << " hit points remaining."<< endl;
		return 1;
	}
	else if (head->mon.hp <= 0) {
		cout << head->mon.name << " fainted!" << endl;
		teamMember *traverseParent = head;
		teamMember *traverse = head;
		while (traverse->next != nullptr) {
			if (traverse->next->mon.hp > 0) {//swap with head
				traverse = traverse->next;
				traverseParent->next = traverse->next;
				teamMember *temp = traverse;
				temp->next = head;
				head = temp;
				cout << "Sending out " << head->mon.name << endl;
				return 1;
			}
			else {
				traverseParent = traverseParent->next;
				traverse = traverse->next;
			}
		}
		return 0;
	}

}


Pokemon* Team::getBattlingPokemon()
{// Return a pointer to the pokemon currently battling

    // Base case - team is empty
    if (head == nullptr){
        cout << "err: team is empty, no one can battle" << endl;
        return nullptr;
    }

    // Return the first pokemon in the team whose health is > 0
    teamMember* search = head;
    while (search->mon.hp <= 0 && search != nullptr)
    {
        search = search->next;
    }

    // Make sure that the entire party hasn't fainted
    if (search->mon.hp > 0){
        return &(search->mon);
    } else {
        cout << "All party members have fainted" << endl;
        return nullptr;
    }
}

bool accuracyCheck(int acc)
{ // Return true or false with a probability of acc
    float prob = float(acc)/100;

    //Initialize a bernoulli distribution and return a random value from it
    default_random_engine rand_engine;
    bernoulli_distribution d(prob);
    return d(rand_engine);
}

void Team::applyDamage(Pokemon *attacker, Move *move, TypeGraph *tg)
{// Apply damage to the current battling pokemon

    // Get the current battling pokemon
    Pokemon* defender = getBattlingPokemon();
    float mult;

    // check that move has sufficient pp
    if (move->pp <= 0)
    {
        cout << "Insufficient pp to use " << move->name << endl;
        return;
    }

    cout << attacker->name << " used " << move->name << "!" << endl;

    // Calculate the damage multiplier
    mult = tg->typeMatchup(attacker->type, move->type, defender->type);

    // Check if the move hits
    if (accuracyCheck(move->acc))
    {
        float attack, damage;
        if (move->cat == "ph")
        { // Use physical attack and defense modifiers
            attack = (move->pow + attacker->atk) * mult;
            damage = attack - defender->def;

            // Check that damage done is not positive
            if (damage < 0)
            {
                damage = 0;
            }

            // Decrement the defending pokemon's health
            defender->hp -= damage;

            // Set defender's hp to zero if it is negative
            if (defender->hp < 0)
            {
                defender->hp = 0;
            }
        }
        else if (move->cat == "sp")
        { // Use special attack and defense moodifiers
            attack = (move->pow + attacker->spc) * mult;
            damage = attack - defender->spc;

            // Check that damage done is not positive
            if (damage < 0)
            {
                damage = 0;
            }

            // Decrement the defending pokemon's health
            defender->hp -= damage;

            // Set defender's hp to zero if it is negative
            if (defender->hp < 0)
            {
                defender->hp = 0;
            }
        }
        cout << attacker->name << " inflicted " << damage << " damage on " << defender->name << endl;
    }
    else
    {
        cout << move->name << " missed!" << endl;
        return;
    }

    // Decrement move's pp
    move->pp--;
}