#pragma once

#include <vector>
#include "SelectionPolicy.h"

class Simulation;
class SelectPolicy;
class Party;
class Coalition;
class Graph;
 

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    virtual ~Agent();
    Agent(const Agent& other);
    Agent(Agent&& other);
    Agent& operator=(const Agent& other);
    Agent& operator=(Agent &&other);
    

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void offer(Party party);
    int getMyCoalitionId(vector<Coalition> coalitions);
    SelectionPolicy* getSelectionPolicy();

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    
};
