#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
    
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}
Party &Graph::getPartyNotConst(int partyId) 
{
    return mVertices[partyId];
}

const vector<vector<int>> Graph:: getEdges() const
{
    return mEdges;
}

const int Graph::getEdge(int i, int j)const 
{
    int ret = mEdges[i][j];
    return ret;
}






