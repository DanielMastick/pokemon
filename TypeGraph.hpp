#ifndef TYPEGRAPH_HPP
#define TYPEGRAPH_HPP
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class TypeGraph{
    public:
        // Default constructor - reads in type_matchup.csv
        TypeGraph();

        // Default destructor
        ~TypeGraph();

        // return the modifier float for the given type matchup
        /* Inputs: (attacking pokemon type [string],
                    type of the attack [string],
                    defending pokemon type [string])*/
        // Output: attack multiplier [float]
        float typeMatchup(string typeAttMon, string typeAtt, string typeDef);

        // Return the index of the move, used to search for type matchups
        // Inputs: (type [string])
        // Output: index of type in typeGraph [int]
        int typeIndex(string type);

    private:

        // Array of floats containing type matchup info
        float *typeChart;
};

#endif