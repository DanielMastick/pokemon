#include "Pokedex.hpp"
#include "MoveList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;


Pokedex::Pokedex()
{// Default constructor
    root = nullptr;
}


Pokedex::~Pokedex()
{// Default destructor - call eraseDex helper
    eraseDex(root);
}

void Pokedex::eraseDex(Pokemon* root)
{// Helper function to recursively delete the BST - called by destructor
    if (root != nullptr)
    {
        eraseDex(root->leftChild);
        eraseDex(root->rightChild);
        delete root;
    }
}

void Pokedex::addMon(int dexNum, string name, string type, int hp, int atk, int def, int spd, int spc, Move move1, Move move2, Move move3, Move move4)
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

    // Base case - add pokemon as root node
    if (root == nullptr)
    {
        root = node;
    }
    else
    {
        int check = 0;
        Pokemon *traverse = root;

        while (check == 0)
        {// Traverse through BST to find apppropriate place to insert the pokemon

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

void Pokedex::loadPokemonFile(MoveList *mt, string filename)
{// Load file into pokedex tree
    string line;
    ifstream myfile(filename);

    // Check if file opened correctly
    if (myfile.is_open())
    {
        // Skip one line
        string skipline;
        getline(myfile, skipline);

        // Give rand a unique seed
        srand(time(0));

        // Loop through every line in the file
        while (getline(myfile, line))
        {

            stringstream ss;
            ss << line;

            // Initialize parameters
            string dexNum, name, type, hp, atk, def, spd, spc, tot, avg;
            Move *move1, *move2, *move3, *move4;

            // Populate parameters from csv
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

            // Fetch 4 random moves from the moves LL
            move1 = (*mt).getRandomMove();
            move2 = (*mt).getRandomMove();
            move3 = (*mt).getRandomMove();
            move4 = (*mt).getRandomMove();

            // Call the addMon function
            addMon(stoi(dexNum), name, type, stoi(hp), stoi(atk), stoi(def), stoi(spd), stoi(spc), *move1, *move2, *move3, *move4);

            // clear the stringstream
            ss.clear();
        }
        // Close the file
        myfile.close();
    }
}

void Pokedex::printPokemonListHelper(Pokemon* root)
{// Print contents of the pokedex
    
    // Base case
    if (root == nullptr)
        return;

    // Recur left
    printPokemonListHelper(root->leftChild);

    // Print info
    cout << root->dexNum << "-" << root->name << " " << root->type << " hp:" << root->hp;
    cout << " atk:" << root->atk << " def:" << root->def << " spd:" << root->spd << " spc:" << root->spc << endl;

    // Recur right
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