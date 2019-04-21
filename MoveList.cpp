#include "MoveList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;


MoveList::MoveList()
{// Default constructor - initialize head as nullptr
    head = nullptr;
}

MoveList::~MoveList()
{// Default destructor
    Move* toDelete = head;
    Move* tmp;
    while (toDelete != nullptr)
    {
        tmp = toDelete->next;
        delete toDelete;
        toDelete = tmp;
    }
    head = nullptr;
}

bool MoveList::isEmpty()
{
    if (head == nullptr){
        return true;
    } else {
        return false;
    }
}

void MoveList::addMove(string nameIn, string typeIn, string catIn, int powIn, int accIn, int ppIn)
{// Add a move to the list
    Move *newMove = new Move;
    newMove->next = nullptr;
    newMove->name = nameIn;
    newMove->type = typeIn;
    // newMove->string status;
    newMove->cat = catIn;
    newMove->pow = powIn;
    newMove->acc = accIn;
    newMove->pp = ppIn;

    // Check if list is empty
    if (isEmpty())
    {// Add move as head of list
        head = newMove;
    }
    else 
    {// Traverse list and add move to the end
        Move* traverse = head;
        while (traverse->next != nullptr)
        {
            traverse = traverse->next;
        }
        traverse->next = newMove;
    }
}

void MoveList::loadMoveFile(string filename)
{// Load contents of movefile into MoveList
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
            string name, type, cat, pow, acc, pp;
            //go through comma seperated file
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, cat, ',');
            getline(ss, pow, ',');
            getline(ss, acc, ',');
            getline(ss, pp, ',');
            addMove(name, type, cat, stoi(pow), stoi(acc), stoi(pp));

            ss.clear();
        }
        myfile.close();
    }
    return;
}

void MoveList::printMoveList()
{// Print all moves

    // Check if list is empty
    if (isEmpty())
    {
        cout << "err: move list is empty, cannot print" << endl;
        return;
    }

    Move* printer = head;
    while (printer != nullptr)
    {
        cout << printer->name << "   ";
        printer = printer->next;
    }
    cout << endl;
}

Move *MoveList::getRandomMove()
{// Return a random move
    if (isEmpty()){
        cout << "err: list is empty" << endl;
        return nullptr;
    }
    
    // get length of list
    int listLen = 0;
    Move* traverse = head;
    while (traverse != nullptr)
    {
        traverse = traverse->next;
        listLen++;
    }

    // Get random index
    int randInd = rand()%listLen;

    // Return move at randInd
    int currInd = 0;
    Move* result = head;
    while (currInd != randInd)
    {
        result = result->next;
        currInd++;
    }
    return result;
}

Move* MoveList::getMove(string moveName)
{// Get move with moveName, if it doesn't exist return nullptr
    // Check if list is empty
    if (isEmpty())
    {
        cout << "err: move list is empty" << endl;
        return nullptr;
    }

    // Traverse through list
    Move* search = head;
    while (search->name != moveName && search != nullptr)
    {
        search = search->next;
    }
    return search;
}

Move *MoveList::getHead()
{
    return head;
}