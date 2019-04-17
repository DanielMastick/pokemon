#include "MoveTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

MoveTable::MoveTable(int numMoves)
{// Default constructor - initialize hashtable as with size numMoves
  hashTable = new Move *[numMoves];
  hashTableSize = numMoves;
  numItems = 0;

  // Set all hashTable indices to nullptr
  for (int i = 0; i < hashTableSize; i++)
  {
    hashTable[i] = nullptr;
  }
}

MoveTable::~MoveTable()
{// Default destructor - delete movetable from memory
  // Loop through table and free memory of all nodes in table
  Move *temp, *toDelete;
  for (int i = 0; i < hashTableSize; i++)
  {
    temp = hashTable[i];
    while (temp != nullptr)
    {
      toDelete = temp;
      temp = temp->next;
      delete toDelete;
    }
    hashTable[i] = nullptr;
  }

  // free memory of the table
  delete[] hashTable;

  // Reassing the table size and number of items to zero
  hashTableSize = 0;
  numItems = 0;
}

unsigned int MoveTable::getHash(string word)
{ // Get hash value for word
  int hashValue = 5381;
  int length = word.length();
  for (int i = 0; i < length; i++)
  {
    hashValue = ((hashValue << 5) + hashValue) + word[i];
  }
  hashValue %= hashTableSize;
  return abs(hashValue);
}

void MoveTable::addMove(string nameIn, string typeIn, string catIn, int powIn, int accIn, int ppIn)
{
  unsigned int index = getHash(nameIn);

  Move* newMove = new Move;
  newMove->next = nullptr;
  newMove->name = nameIn;
  newMove->type = typeIn;
  // newMove->string status;
  newMove->cat = catIn;
  newMove->pow = powIn;
  newMove->acc = accIn;
  newMove->pp= ppIn;
  // string duration;
  // Check that the hash value is not already used
  if (hashTable[index] == nullptr)
  {// Add a new word as start of the list
    hashTable[index] = newMove;
    numItems++;
  }
  else
  {// Add the new word at the end of the list
    Move* temp = hashTable[index];
    while (temp->next != nullptr){
      temp = temp->next;
    }
    temp->next = newMove;
    numItems++;
  }
return;
}


void MoveTable::loadMoveFile(string filename)
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

void MoveTable::printMoveList()
{
  for (size_t i = 0; i < hashTableSize; i++)
  {
    cout << "bin #" << i << ": ";
    if (hashTable[i] != nullptr)
    {
      Move *temp = hashTable[i];
      while (temp->next != nullptr)
      {
        cout << temp->name << "   ";
        temp = temp->next;
      }
      cout << temp->name;
    }
    cout << endl;
  }
}

Move* MoveTable::getRandomMove()
{
  int bin = rand() % (hashTableSize-1);
  int exit = 0;
  while (exit != 1)
  {
    exit = rand() % 2; //random number to determine if the list is traversed
    Move *temp = hashTable[bin];
    if (exit == 0 && temp->next != nullptr)
    {
      temp = temp->next;
    }
    else
    {
      return temp;
    }
  }
}