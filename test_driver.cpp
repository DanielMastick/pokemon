#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MoveTable.hpp"
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

void battle(Team *p1, Team *p2)
{
    cout << "lets battle my dudes" << endl;
}

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        cout << "This program doesn't require any initial command line inupts" << endl;
        return -1;
    }

    // Initialize new movetable with given size
    int numMoves = 25;
    MoveTable mt(numMoves);

    // Load moves into moveTable
    cout << "loading moves" << endl;
    mt.loadMoveFile("pokemon_moves_attack_only.csv");
    cout << "finished loading moves"
         << "\n"
         << endl;

    // Instantiate pokedex binary tree
    Pokedex dex;
    cout << "loading pokemon" << endl;
    dex.loadPokemonFile(&mt, "pokemon_data.csv");
    cout << "finished loading pokemon"
         << "\n"
         << endl;

    // Read type matchups into graph
    TypeGraph types;

    // test a couple matchups
    cout << "fire vs. water: " << types.typeMatchup("Fire", "Fire", "Water") << endl;
    cout << "normal fire vs. water: " << types.typeMatchup("Fire", "Normal", "Water") << endl;
    cout << "normal fire vs ghost: " << types.typeMatchup("Normal", "Fire", "Ghost") << endl;  

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
        {
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

            dex.addMon(dexNum, name, type, stoi(hp), stoi(atk), stoi(def), stoi(spd), stoi(spc), &mt, move1, move2, move3, move4);
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
            mt.printMoveList();
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
            cout << "Here is team 1: ";
            p1.printTeam();

            cout << "Select " << teamSize << " Pokemon for Player 2." << endl;
            
            // Initialize second team
            Team p2;
            // Populate p2
            p2.makeTeam(teamSize, dex.getRoot());
            // Display contents
            cout << "Here is team 2: ";
            p2.printTeam();

            battle(&p1, &p2);
            break;
        }
        case 5:
        {
            cout << "Hope you had fun :P" << endl;
            finish = 1;
            break;
        }
        }
    }
}