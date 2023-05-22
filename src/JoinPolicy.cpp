#include "JoinPolicy.h"
#include "Party.h"
#include "Coalition.h"
#include "Simulation.h"

JoinPolicy* LastOfferJoinPolicy:: pClone()
{
    return new LastOfferJoinPolicy();
}

int LastOfferJoinPolicy::join(vector<int> offers, Simulation& sim)
{
    return offers[offers.size()-1];
}

JoinPolicy* MandatesJoinPolicy:: pClone()
{
    return new MandatesJoinPolicy();
}

int MandatesJoinPolicy::join(vector<int> offers, Simulation& sim)
{
    if(offers.size()>0)
    {
        int selected = offers[0];
        for(int coalitionId:offers)
        {   
                if(sim.getCoalition(coalitionId).getMandates()>sim.getCoalition(selected).getMandates())
                {
                    selected = coalitionId;
                }
        }
        return selected;
    }
    return -1;
}