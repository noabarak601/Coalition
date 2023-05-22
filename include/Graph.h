#pragma once
#include <vector>
#include "Party.h"

using std::vector;
//class party;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;
    Party &getPartyNotConst(int partyId);
    const vector<vector<int>> getEdges() const; 
    const int getEdge(int i, int j) const;   


private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
    
};
