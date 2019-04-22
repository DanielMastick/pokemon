#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include "MoveList.hpp"
#include "Pokedex.hpp"
#include "TypeGraph.hpp"

using namespace std;

struct teamMember
{
    Pokemon mon;
    teamMember *next;
};

class Team{
    public:
        Team();
        ~Team();
        teamMember* addMember(string name, Pokemon* root);
        Pokemon* getMon(Pokemon* root, string name);
        Pokemon* getBattlingPokemon();
        void makeTeam(int teamSize, Pokemon* root);
        void applyDamage(Pokemon* attacker, Move* move, TypeGraph* tg);
        void printTeam();
		bool checkStatus();

    private:

        teamMember* head;
};

#endif