#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MoveTable.hpp"

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

struct team
{
    Pokemon *mon;
    team *next;
};

void menu()
{
    cout << "============Main Menu============" << endl;
    cout << "1. Add Pokemon" << endl;
    cout << "2. Print Pokemon List" << endl;
    cout << "3. Print Move List" << endl;
    cout << "4. Battle" << endl;
    cout << "5. Quit" << endl;
}

Pokemon *addMon(Pokemon *root, int dexNum, string name, string type, int hp, int atk, int def, int spd, int spc, MoveTable mt, Move move1, Move move2, Move move3, Move move4)
{
    cout << "Creating new pokemon node" << endl;
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
        return root;
    }
}

Pokemon *loadPokemonFile(Pokemon *root, MoveTable mt, string filename)
{
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
            cout << "Getting moves" << endl;
            move1 = mt.getRandomMove();
            move2 = mt.getRandomMove();
            move3 = mt.getRandomMove();
            move4 = mt.getRandomMove();
            cout << "Adding Pokemon" << endl;
            root = addMon(root, stoi(dexNum), name, type, stoi(hp), stoi(atk), stoi(def), stoi(spd), stoi(spc), mt, *move1, *move2, *move3, *move4);

            ss.clear();
        }
        myfile.close();
    }
    return root;
}

Pokemon *getMon(Pokemon *root, string name)
{
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

void printPokemonList(Pokemon *root)
{
    if (root == nullptr)
        return;
    printPokemonList(root->leftChild);
    cout << root->dexNum << "-" << root->name << " " << root->type << " hp:" << root->hp;
    cout << " atk:" << root->atk << " def:" << root->def << " spd:" << root->spd << " spc:" << root->spc << endl;
    printPokemonList(root->rightChild);
}

int typeIndex(string name)
{
    int index = 0;
    string types[19] = {"Fail", "Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};
    for (int i = 0; i < 19; i++)
    {
        if (name == types[i])
        {
            return i;
        }
    }
    return -1;
}

float *loadTypeMatchup(string typeAtt, string typeDef)
{
    float *typeChart;
    int count = 1;

    string num;
    ifstream myfile("type_matchup.csv");

    if (myfile.is_open())
    {
        while (getline(myfile, num))
        {
            stringstream ss;
            ss << num;
            string val;
            //go through comma seperated file
            getline(ss, val, ',');
            *(typeChart + count) = stof(val);
            count++;
            ss.clear();
        }
        myfile.close();
    }
    return typeChart;
}

float *typeMatchup(float *typeChart, string typeAtt, string typeDef)
{
    int typeAttInd = typeIndex(typeAtt);
    int typeDefInd = typeIndex(typeDef);
    cout << typeAttInd << " " << typeDefInd << endl;
}

team *makeTeam(Pokemon *root, int teamSize)
{
    int monCount = 0;
    string name;
    team *p1 = new team;
    while (monCount < teamSize)
    {
        cout << "Name of #" << monCount << " Mon: " << endl;
        getline(cin, name);
        Pokemon *tempMon = getMon(root, name);

        if (tempMon != nullptr)
        {
            cout << "Adding " << tempMon->name << endl;
            if (monCount == 0)
            {
                p1->mon = tempMon;
                p1->next = nullptr;
            }
            else
            {
                team *tempTeam = new team;
                tempTeam->mon = tempMon;
                tempTeam->next = nullptr;
                team *traverse = p1;
                while (traverse->next != nullptr)
                {
                    traverse = traverse->next;
                }
                traverse->next = tempTeam;
            }
            monCount++;
        }
        else
        {
            cout << name << " is not a Pokemon, check your spelling" << endl;
        }
    }
    return p1;
}

void battle(team *p1, team *p2)
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
    Pokemon *root = new Pokemon;
    root = nullptr;

    // Initialize new movetable with given size
    int numMoves = 25;
    MoveTable mt(numMoves);

    cout << "loading moves" << endl;
    mt.loadMoveFile("pokemon_moves_attack_only.csv");
    cout << "finished loading moves"
         << "\n"
         << endl;

    cout << "loading pokemon" << endl;
    root = loadPokemonFile(root, mt, "pokemon_data.csv");
    cout << "finished loading pokemon"
         << "\n"
         << endl;

    int finish = 0;
    while (finish == 0)
    {
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
            int check = typeIndex(type);
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

            root = addMon(root, dexNum, name, type, stoi(hp), stoi(atk), stoi(def), stoi(spd), stoi(spc), mt, move1, move2, move3, move4);
            cout << "Nice Pokemon! It has been added to the Pokedex (Binary Tree)." << endl;
            break;
        }
        case 2:
        {
            cout << "Printing Pokemon list" << endl;
            printPokemonList(root);
            break;
        }
        case 3:
        {
            cout << "Printing moves list" << endl;
            mt.printMoveList();
            break;
        }
        case 4:
        {
            cout << "Lets Battle!" << endl;
            cout << "Chose the size of the teams" << endl;
            string in;
            getline(cin, in);
            int teamSize = stoi(in);

            cout << "Select " << teamSize << " Pokemon for Player 1." << endl;
            team *p1 = makeTeam(root, teamSize);
            cout << "Here is team 1: ";
            team *traverse = p1;
            cout << traverse->mon->name << "--" << traverse->mon->m1.name << "--";
            cout << traverse->mon->m2.name << "--" << traverse->mon->m3.name << "--" << traverse->mon->m4.name << endl;
            for (size_t i = 0; i < teamSize - 1; i++)
            {
                traverse = traverse->next;
                cout << traverse->mon->name << "--" << traverse->mon->m1.name << "--";
                cout << traverse->mon->m2.name << "--" << traverse->mon->m3.name << "--" << traverse->mon->m4.name << endl;
            }
            cout << endl;

            cout << "Select " << teamSize << " Pokemon for Player 2." << endl;
            team *p2 = makeTeam(root, teamSize);
            cout << "Here is team 1: ";
            traverse = p2;
            cout << traverse->mon->name << "--" << traverse->mon->m1.name << "--";
            cout << traverse->mon->m2.name << "--" << traverse->mon->m3.name << "--" << traverse->mon->m4.name << endl;
            for (size_t i = 0; i < teamSize - 1; i++)
            {
                p2 = p2->next;
                cout << traverse->mon->name << "--" << traverse->mon->m1.name << "--";
                cout << traverse->mon->m2.name << "--" << traverse->mon->m3.name << "--" << traverse->mon->m4.name << endl;
            }
            cout << endl;

            battle(p1, p2);
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