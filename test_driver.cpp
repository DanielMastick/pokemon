#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MoveList.hpp"
#include "Team.hpp"
#include "Pokedex.hpp"
#include "TypeGraph.hpp"

using namespace std;


void menu()
{
    cout << "============Main Menu============" << endl;
    cout << "1. Add Pokemon" << endl;
    cout << "2. Print Pokemon List" << endl;
    cout << "3. Print Move List" << endl;
    cout << "4. Battle" << endl;
    cout << "5. Quit" << endl;
}

Move* selectMove(Team *p1)
{// Prompt user to select a move from the current battling pokemon

    // Initialize variables
    string input;
    int inInt = 10;
    
    // Get the current battling pokemon
    Pokemon* battling = p1->getBattlingPokemon();

    // Prompt user to select a move from the battling pokemon
    cout << "==========================================================================" << endl;
    cout << "Select one of " << battling->name << "'s moves:" << endl;
    cout << "1. " << battling->m1.name << " [" << battling->m1.type << "]  power:" << battling->m1.pow << "   accuracy:" << battling->m1.acc << "   pp:" << battling->m1.pp << "   damage type:" << battling->m1.cat << endl;

    cout << "2. " << battling->m2.name << " [" << battling->m2.type << "]  power:" << battling->m2.pow << "   accuracy:" << battling->m2.acc << "   pp:" << battling->m2.pp << "   damage type:" << battling->m2.cat << endl;

    cout << "3. " << battling->m3.name << " [" << battling->m3.type << "]  power:" << battling->m3.pow << "   accuracy:" << battling->m3.acc << "   pp:" << battling->m3.pp << "   damage type:" << battling->m3.cat << endl;

    cout << "4. " << battling->m4.name << " [" << battling->m4.type << "]  power:" << battling->m4.pow << "   accuracy:" << battling->m4.acc << "   pp:" << battling->m4.pp << "   damage type:" << battling->m4.cat << endl;
    cout << "==========================================================================" << endl;

    while (inInt < 1 || inInt > 4)
    {
        getline(cin, input);
        inInt = stoi(input);

        switch(inInt)
        {
        case 1:
        {
            return &(battling->m1);
        }
        case 2:
        {
            return &(battling->m2);
        }
        case 3:
        {
            return &(battling->m3);
        }
        case 4:
        {
            return &(battling->m4);
        }
        default:
            cout << "err: Given number is not between 1 and 4" << endl;
        }
    }

}


void battle(Team *p1, Team *p2, TypeGraph* tg)
{//State battle system with selected teams
    Move* move;
    Pokemon *p1_current, *p2_current;
    cout << "lets battle my dudes" << endl;
	bool end = 1;

	while (end == 1) {

        end = p1->checkStatus();
		if (end == 0) {
			cout << "All Pokemon on team 1 have fainted" << endl;
			cout << "Player 2 Wins!" << endl;
		}

        //select move
        move = selectMove(p1);

        // Get pointer to the attacking pokemon
        p1_current = p1->getBattlingPokemon();

        //calculate damage
        p2->applyDamage(p1_current, move, tg);

        end = p2->checkStatus();
		if (end == 0) {
			cout << "All Pokemon on team 2 have fainted" << endl;
			cout << "Player 1 Wins!" << endl;
		}

        //select move
        move = selectMove(p2);

        // Get pointer to the attacking pokemon
        p2_current = p2->getBattlingPokemon();

        //calculate damage
        p1->applyDamage(p2_current, move, tg);

    }

}

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        cout << "This program doesn't require any initial command line inupts" << endl;
        return -1;
    }

    // Initialize new movelist with given size
    MoveList ml;

    // Load moves into moveTable
    cout << "loading moves" << endl;
    ml.loadMoveFile("pokemon_moves_attack_only.csv");
    cout << "finished loading moves"
         << "\n"
         << endl;

    // Instantiate pokedex binary tree
    Pokedex dex;
    cout << "loading pokemon" << endl;
    dex.loadPokemonFile(&ml, "pokemon_data.csv");
    cout << "finished loading pokemon"
         << "\n"
         << endl;

    // Read type matchups into graph
    TypeGraph types;

    int finish = 0;
    while (finish == 0)
    {
        // Prompt user with menu and get input
        menu();
        string input;
        getline(cin, input);
        int option = stoi(input);
        int newMonCount = 0;
        switch (option)
        {
        case 1:
        {	//Adding a new Pokemon
            int dexNum;
            string name, type, hp, atk, def, spd, spc, tot, avg;
            Move move1, move2, move3, move4;
            cout << "Adding Pokemon!" << endl;
            newMonCount++;
            dexNum = 151 + newMonCount;
            cout << "What is the name of this Pokemon?" << endl;
            getline(cin, name);
            cout << "What is this Pokemon's type?" << endl;
            getline(cin, type);
            int check = types.typeIndex(type);
            if (check == -1)
            {
                cout << "Not a valid type, try again." << endl;
                getline(cin, type);
            }
            cout << "The Pokemon's hp?" << endl;
            getline(cin, hp);
            cout << "Attack?" << endl;
            getline(cin, atk);
            cout << "Defense?" << endl;
            getline(cin, def);
            cout << "Speed?" << endl;
            getline(cin, spd);
            cout << "Speicial?" << endl;
            getline(cin, spc);

            move1 = *(ml.getRandomMove());
            move2 = *(ml.getRandomMove());
            move3 = *(ml.getRandomMove());
            move4 = *(ml.getRandomMove());

            dex.addMon(dexNum, name, type, stoi(hp), stoi(atk), stoi(def), stoi(spd), stoi(spc), &ml, move1, move2, move3, move4);
            cout << "Nice Pokemon! It has been added to the Pokedex (Binary Tree)." << endl;
            break;
        }
        case 2:
        {   // Print all loaded pokemon
            cout << "Printing Pokemon list" << endl;
            dex.printPokemonList();
            break;
        }
        case 3:
        {   // Print all loaded moves
            cout << "Printing moves list" << endl;
            ml.printMoveList();
            break;
        }
        case 4:
        {   // Battle!
            cout << "Lets Battle!" << endl;
            cout << "Chose the size of the teams" << endl;
            string in;
            getline(cin, in);
            int teamSize = stoi(in);

            cout << "Select " << teamSize << " Pokemon for Player 1." << endl;

            // Initialize first team
            Team p1;
            // Populate p1
            p1.makeTeam(teamSize, dex.getRoot());
            // Display contents
            cout << "Here is team 1: " << endl;
            p1.printTeam();

            cout << "Select " << teamSize << " Pokemon for Player 2." << endl;
            
            // Initialize second team
            Team p2;
            // Populate p2
            p2.makeTeam(teamSize, dex.getRoot());
            // Display contents
            cout << "Here is team 2: " << endl;
            p2.printTeam();

            battle(&p1, &p2, &types);
            break;
        }
        case 5:
        {	//Quitting
            cout << "Hope you had fun :P" << endl;
            finish = 1;
            break;
        }
        }
    }
}