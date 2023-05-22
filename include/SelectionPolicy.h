#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Simulation;
class Party;

class SelectionPolicy { 
    public:
    virtual ~SelectionPolicy() = default;
    virtual int select(vector<int> neighbors, int partyId,Simulation& sim) = 0;
    virtual SelectionPolicy* clone() = 0;    
};

class MandatesSelectionPolicy: public SelectionPolicy{ 
    
    //virtual ~MandatesSelectionPolicy();
    virtual int select(vector<int> neighbors,int partyId,Simulation& sim);
    virtual SelectionPolicy* clone();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    //virtual ~EdgeWeightSelectionPolicy();
    virtual int select(vector<int> neighbors, int partyId,Simulation& sim);
    virtual SelectionPolicy* clone();
 };