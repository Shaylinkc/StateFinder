#ifndef STATEDATA_H_INCLUDED
#define STATEDATA_H_INCLUDED
#include <string>
#include <vector>

using namespace std;

struct State {
    string name;
    string politicalParty;
    string coastal;
    string costOfLiving;
    string population;
    string avgSummerTemp;
    string avgWinterTemp;
    string snowFall;
    string rainFall;
    string environment;
    string naturalDisasters;
    string food;
};

vector<State> getAllStates();

#endif
