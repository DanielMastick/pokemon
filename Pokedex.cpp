#include "Pokedex.hpp"
#include "MoveTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


Pokedex::Pokedex()
{// Default constructor
    root = nullptr;
}


Pokedex::~Pokedex()
{// Default destructor

}

void Pokedex::addMon(int dexNum, string name, string type, int hp, int atk, int def, int spd, int spc, MoveTable *mt, Move move1, Move move2, Move move3, Move move4)
{// Add pokemon to the pokedex tree
    Pokemon *node = new Pokemon;
    node->dexNum = dexNum;
    node->name = name;
    node->type = type;
    node->hp = hp;
    node->atk = atk;
    node->def = def;
    node->spd = spd;
    node->spc = spc;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    node->m1 = move1;
    node->m2 = move2;
    node->m3 = move3;
    node->m4 = move4;

    if (root == nullptr)
    {
        root = node;
    }
    else
    {
        int check = 0;
        Pokemon *traverse = root;

        while (check == 0)
        {

            //if (traverse->leftChild != NULL && node->name.at(0)<traverse->name) {
            if (traverse->leftChild != NULL && node->name < traverse->name)
            {
                //title is earlier in alphabet and there is an entry
                traverse = traverse->leftChild;
            }
            else if (traverse->rightChild != NULL && node->name > traverse->name)
            {
                //title is later in alphabet and there is an entry
                traverse = traverse->rightChild;
            }
            else if (node->name < traverse->name)
            {
                //title is earlier and it is null
                traverse->leftChild = node;
                node->parent = traverse;
                check = 1;
            }
            else if (node->name > traverse->name)
            {
                //title is later and it is null
                traverse->rightChild = node;
                node->parent = traverse;
                check = 1;
            }
        }
    }
}

void Pokedex::loadPokemonFile(MoveTable *mt, string filename)
{// Load file into pokedex tree
    string line;
    ifstream myfile(filename);

    if (myfile.is_open())
    {
        string skipline;
        getline(myfile, skipline);
        while (getline(myfile, line))
        {

            stringstream ss;
            ss << line;
            string dexNum, name, type, hp, atk, def, spd, spc, tot, avg;
            Move *move1, *move2, *move3, *move4;
            //go through comma seperated file
            getline(ss, dexNum, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, hp, ',');
            getline(ss, atk, ',');
            getline(ss, def, ',');
            getline(ss, spd, ',');
            getline(ss, spc, ',');
            getline(ss, tot, ',');
            getline(ss, avg, ',');
            move1 = (*mt).getRandomMove();
            move2 = (*mt).getRandomMove();
            move3 = (*mt).getRandomMove();
            move4 = (*mt).getRandomMove();

            addMon(stoi(dexNum), name, type, stoi(hp), stoi(atk), stoi(def), stoi(spd), stoi(spc), mt, *move1, *move2, *move3, *move4);

            ss.clear();
        }
        myfile.close();
    }
}

void Pokedex::printPokemonListHelper(Pokemon* root)
{// Print contents of the pokedex
    if (root == nullptr)
        return;
    printPokemonListHelper(root->leftChild);
    cout << root->dexNum << "-" << root->name << " " << root->type << " hp:" << root->hp;
    cout << " atk:" << root->atk << " def:" << root->def << " spd:" << root->spd << " spc:" << root->spc << endl;
    printPokemonListHelper(root->rightChild);
}

void Pokedex::printPokemonList()
{// Run the helper function starting at root
    printPokemonListHelper(root);
}

Pokemon* Pokedex::getRoot()
{// Accesor function that returns root of the binary tree
    return root;
}