#include "Simulation.h"
#include "Agent.h"
#include "Party.h"


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), coalitions(vector<Coalition>()), notJoinedParties(graph.getNumVertices() - agents.size()),maxMandates(0)
{
    // You can change the implementation of the constructor, but not the signature!
    for (Agent agent : agents)
    {
        Coalition coalition = Coalition(getParty(agent.getPartyId()));
        coalitions.push_back(coalition);
    }

    for (Coalition coalition : coalitions)
    {
        int current = coalition.getMandates();
        if (current > maxMandates)
        {
            maxMandates = current;
        }
    }
}

void Simulation::step()

{
    // TODO: implement this method
    int numOfPareties = getGraph().getNumVertices();
    for(int i=0; i<numOfPareties;i++)
    {
        mGraph.getPartyNotConst(i).step(*this);
    }
    for(Agent& agent: mAgents)
    {
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    // TODO implement this method
    if ((maxMandates >= 61) | (notJoinedParties == 0))
    {
        return true;
    }
    return false;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}
Party &Simulation::getPartyNotConst(int partyId) 
{
    return mGraph.getPartyNotConst(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> ret;
    for(const Coalition& coalition: coalitions){
        vector<int> coalitionParties;
        vector<Party> cParties = coalition.getParties();
        int size = cParties.size();
        for(int i= 0; i<size;i++){
            int partyId = cParties[i].getId();
            coalitionParties.push_back(partyId);
        }
        ret.push_back(coalitionParties);
    }
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return ret;
}

void Simulation::upadteNotJoinedParties()
{
    notJoinedParties--;
}

int Simulation::getMaxMandates()
{
    return maxMandates;
}

void Simulation::updateMaxMandates(int max)
{
    maxMandates = max;
}

// memory

 vector<int> Simulation::potentialParties(int partyId, int coalitionId)
{
    vector<int> neighbors;
    // bug? what if it's empty?
    int ver = getGraph().getNumVertices();
    for (int i = 0; i < ver; i++)
    {
        // go over neighbors
        int weight = getGraph().getEdgeWeight(i,partyId);
        if (weight > 0)
        {
            int partyId = i;
            Party party = getPartyNotConst(partyId); 
            if (party.getState() != Joined)
            {   
                if (!party.sameCoalitionOffered(coalitionId))
                {
                    neighbors.push_back(partyId);
                }
            }
        }
    }
    return neighbors;
}

const vector<Coalition> Simulation::getCoalitions() const
{
    return coalitions;
}

vector<int> Simulation::getWeights(vector<int> parties, int myId) 
{
    vector<int> weights;
    for(int partyId: parties)
    {
        int weight = getGraph().getEdgeWeight(myId, partyId);
        weights.push_back(weight);
    }
    return weights;
}

Coalition& Simulation::getCoalition(int id)
{
    for(Coalition& coalition: coalitions)
    {
        if(coalition.getId()==id)
        {
            return coalition;
        }
    }
    
    return coalitions[0];
}

Agent& Simulation::getAgent(int partyId)
{
    for(Agent& agent : mAgents)
    {
        if(agent.getPartyId()==partyId)
        {
            return agent;
        }
    }
    return mAgents[0];
}


void Simulation::addAgent(Agent agent)
{
    mAgents.push_back(agent);
}
