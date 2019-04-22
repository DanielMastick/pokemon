#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <random>
#include "MoveList.hpp"
#include "Pokedex.hpp"
#include "TypeGraph.hpp"

using namespace std;

struct teamMember
{
    // Pokemon object
    Pokemon mon;
    // Pointer to next element of LL
    teamMember *next;
};

class Team{
    public:
        // Default constructor
        Team();
        // Defualt destructor
        ~Team();

        // Add a teamMember to the linked list
        // Inputs: (Name of pokemon to add [string], pointer to root of Pokedex BST [Pokemon*])
        // Outputs: pointer to new teamMember or nullptr if pokemon with name is not found
        teamMember* addMember(string name, Pokemon* root);

        // Search Pokedex BST for pokemon with given name
        // Inputs: (pointer to root of Pokedex BST [Pokemon*], name of pokemon to add [string])
        // Outputs: pointer to pokemon with name, or nullptr if no matching pokemon is found
        Pokemon* getMon(Pokemon* root, string name);

        // Get the current battling pokemon
        // Outputs: Pointer to the first healthy pokemon in the LL, nominally this will be head
        Pokemon* getBattlingPokemon();

        // Build a team with user input
        // Inputs: (Size of team [int], root node of the Pokedex BST [Pokemon*])
        void makeTeam(int teamSize, Pokemon* root);

        // Apply damage to the currently battling pokemon
        // Inputs: (pointer to the attacking pokemon [Pokemon*], pointer to the move used by the attacking pokemon [Move*],
        //          pointer to the type graph [TypeGraph*])
        void applyDamage(Pokemon* attacker, Move* move, TypeGraph* tg);

        // Print contents of the team
        void printTeam();

        // Check the teams status and switch head with the next healthy pokemon if need be
        // Output: false if all pokemon have 0 hp, true otherwise
		bool checkStatus();

    private:

        // Head of LL
        teamMember* head;
};

#endif