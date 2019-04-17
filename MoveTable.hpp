#ifndef MOVETABLE_HPP
#define MOVETABLE_HPP

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Stores move parameters
struct Move
{
    Move *next;
    string name;
    string type;
    // string status;
    string cat;
    int pow;
    int acc;
    int pp;
    // string duration;
};


class MoveTable{
    public:
        MoveTable(int numMoves);
        ~MoveTable();

        void addMove(string nameIn, string typeIn, string catIn, int powIn, int accIn, int ppIn);
        void loadMoveFile(string filename);
        void printMoveList();
        Move* getRandomMove();

    private:
        unsigned int getHash(string word);

        Move **hashTable;
        int hashTableSize;
        int numItems;
};

#endif