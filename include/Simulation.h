#pragma once

#include <vector>
#include "Coalition.h"
#include "Graph.h"

using std::string;
using std::vector;

class Agent;
class Party;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    Party &getPartyNotConst(int partyId);
    const vector<vector<int>> getPartiesByCoalitions() const;
    void upadteNotJoinedParties();
    int  getMaxMandates();
    void updateMaxMandates(int max);
    void addAgent(Agent agent);
    vector<int> potentialParties(int partyID, int coalitionId);
    const vector<Coalition> getCoalitions() const; 
    vector<int> getWeights(vector<int> parties, int myId);
    Coalition& getCoalition(int id);
    Agent& getAgent(int partyId);

    

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> coalitions;
    int notJoinedParties;
    int maxMandates;
};
