#ifndef MOVELIST_HPP
#define MOVELIST_HPP

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


class MoveList{
    public:
        MoveList();
        ~MoveList();

        void addMove(string nameIn, string typeIn, string catIn, int powIn, int accIn, int ppIn);
        void loadMoveFile(string filename);
        void printMoveList();
        Move* getRandomMove();
        Move* getMove(string moveName);
        Move* getHead();

    private:
        bool isEmpty();
        Move* head;
};

#endif