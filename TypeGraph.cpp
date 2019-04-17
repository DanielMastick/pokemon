#include "TypeGraph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

TypeGraph::TypeGraph()
{// Default constructor - load the type graph
    typeChart = new float[324];
    int count = 0;

    string line;
    ifstream myfile("type_matchup.csv");

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream ss;
            ss << line;
            string val;
            //go through comma seperated file
            while (getline(ss, val, ','))
            {
                typeChart[count] = stof(val);
                // count+=sizeof(float);
                count++;
                ss.clear();
            }
        }
        myfile.close();
    }
    
}

TypeGraph::~TypeGraph()
{// Default destructor - deallocate TypeGraph memory
    delete[] typeChart;
}

int TypeGraph::typeIndex(string type)
{// Return index of the given type
    int index = 0;
    string types[18] = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};
    for (int i = 0; i < 18; i++)
    {
        if (type == types[i])
        {
            return i;
        }
    }
    return -1;
}

float TypeGraph::typeMatchup(string typeAttMon, string typeAtt, string typeDef)
{// Return the modifier appropriate for the given type matchup
    int typeAttInd = typeIndex(typeAtt);
    int typeDefInd = typeIndex(typeDef);

    float stab = 1;
    if (typeAttMon == typeAtt)
    {
        stab = 1.5;
    }
    return stab * typeChart[(18 * typeAttInd) + typeDefInd];
}