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
        // Default constructor
        MoveList();
        // Default destructor
        ~MoveList();

        // add a move to the linked list
        /* Inputs: (move name [string],
                    move type [string],
                    status effect [string],
                    power [int],
                    accuracy 0-100 [int],
                    pp [int]) */
        void addMove(string nameIn, string typeIn, string catIn, int powIn, int accIn, int ppIn);

        // Read in contents of move file and populate LL
        // inputs: (name of file to read [string])
        void loadMoveFile(string filename);

        // Print all moves in the LL 
        void printMoveList();

        // Fetch a random move from the list
        // Output: pointer to random move [Move*]
        Move* getRandomMove();

        // Fetch a move with the given name
        // Inputs: (name of move to search for [string])
        // Output: pointer to move with moveName, or nullptr if move is not found [Move*]
        Move* getMove(string moveName);

        // Return head of the linked list
        // Output: pointer to head of list 
        Move* getHead();

    private:
        // Returns true if LL is empty, false if not
        bool isEmpty();

        // Head of LL
        Move* head;
};

#endif