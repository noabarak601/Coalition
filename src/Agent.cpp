#include "Agent.h"
#include "Graph.h"
#include "SelectionPolicy.h"
#include "Simulation.h"
#include "Party.h"
#include "Coalition.h"
#include <iostream>

using std::cout;

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}

Agent::~Agent()
{
    if (mSelectionPolicy)
    {
        delete mSelectionPolicy;
    }
}

Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(nullptr)
{
    mSelectionPolicy = other.mSelectionPolicy->clone();
}

Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy)
{
    other.mSelectionPolicy = nullptr;
}

Agent &Agent::operator=(Agent &&other)
{
    if (mSelectionPolicy)
    {
        delete mSelectionPolicy;
    }
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;

    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
    return *this;
}

Agent &Agent::operator=(const Agent &other)
{
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    *mSelectionPolicy = (*(other.mSelectionPolicy));

    return *this;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
    int myCoalitionId = getMyCoalitionId(sim.getCoalitions());
    vector<int> potentialParties = sim.potentialParties(mPartyId, myCoalitionId);
    int selectedPartyId = (*mSelectionPolicy).select(potentialParties, mPartyId, sim);
    if (selectedPartyId != -1)
    {
        if (sim.getPartyNotConst(selectedPartyId).getState() == Waiting)
        {
            sim.getPartyNotConst(selectedPartyId).setState(CollectingOffers);
        }
        sim.getPartyNotConst(selectedPartyId).addOffer(myCoalitionId);
    }
}

int Agent::getMyCoalitionId(vector<Coalition> coalitions)
{
    for (Coalition &coalition : coalitions)
    {
        vector<Party> parties = coalition.getParties();
        for (Party party : parties)
        {
            if (mPartyId == party.getId())
            {
                return coalition.getId();
            }
        }
    }
    return -1;
}

SelectionPolicy *Agent::getSelectionPolicy()
{
    return mSelectionPolicy;
}
