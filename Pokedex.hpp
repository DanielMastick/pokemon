#ifndef POKEDEX_HPP
#define POKEDEX_HPP

#include "MoveTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Pokemon
{
    // Pointers
    Pokemon *parent;
    Pokemon *leftChild;
    Pokemon *rightChild;
    // Data
    int dexNum;  //1-151
    string name; //pokemon name
    string type; //grass/fire/ect
    int hp;      //hit points
    int atk;     //attack
    int def;     //defense
    int spd;     //speed
    int spc;     //special
    Move m1;
    Move m2;
    Move m3;
    Move m4;
};

class Pokedex
{
    public:
        Pokedex();
        ~Pokedex();
        void loadPokemonFile(MoveTable *mt, string filename);
        void printPokemonList();
        Pokemon* getRoot();
        void addMon(int dexNum, string name, string type, int hp, int atk, int def, int spd, int spc, MoveTable *mt, Move move1, Move move2, Move move3, Move move4);

    private:
        void printPokemonListHelper(Pokemon* root);
        Pokemon* root;
};

#endif