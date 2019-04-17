#ifndef TYPEGRAPH_HPP
#define TYPEGRAPH_HPP
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class TypeGraph{
    public:
        TypeGraph();
        ~TypeGraph();
        float typeMatchup(string typeAttMon, string typeAtt, string typeDef);
        int typeIndex(string type);

    private:

        float *typeChart;
};

#endif