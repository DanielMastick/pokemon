#ifndef POKEDEX_HPP
#define POKEDEX_HPP

#include "MoveList.hpp"
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
        // Default constructor
        Pokedex();
        // Default destructor
        ~Pokedex();

        // Read in pokemon file and populate BST
        // Inputs: (pointer to moves LL [MoveList*], name of file to read in [string])
        void loadPokemonFile(MoveList *mt, string filename);

        // Print contents of the tree - calls printPokemonListHelper
        void printPokemonList();

        // Return root of the BST
        // Output: pointer to root node of BST
        Pokemon* getRoot();

        // Add a pokemon with the given parameters to the BST
        /* Inputs: (pokedex number [int],
                    name [string],
                    type [string],
                    hit points [int],
                    attack [int],
                    defense [int],
                    speed [int],
                    special attack/defense [int],
                    first move [Move],
                    second move [Move],
                    third move [Move],
                    fourth move [Move]
        */
        void addMon(int dexNum, string name, string type, int hp, int atk, int def, int spd, int spc, Move move1, Move move2, Move move3, Move move4);

    private:
        // Helper function to recursively delete the BST - called by destructor
        void eraseDex(Pokemon* root);
        // Helper funciton to recursively print contents of BST - called by printPokemonList
        void printPokemonListHelper(Pokemon* root);
        // Root node
        Pokemon* root;
};

#endif