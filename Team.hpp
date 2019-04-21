#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include "MoveList.hpp"
#include "Pokedex.hpp"

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
        void makeTeam(int teamSize, Pokemon* root);
        void printTeam();
    private:

        teamMember* head;
};

#endif