#include "SelectionPolicy.h"
#include "Party.h"
#include "Simulation.h"
SelectionPolicy* MandatesSelectionPolicy:: clone()
{
    return new MandatesSelectionPolicy();
}

int MandatesSelectionPolicy::select(vector<int> potentialParties, int myCoalitionId, Simulation &sim)
{
    
    if(abs(potentialParties.size())>0)
    {
        int selectedId = potentialParties[0];
        for(int partyId:potentialParties)
        { 
            Party party = sim.getPartyNotConst(partyId);
            Party selected = sim.getPartyNotConst(selectedId);  
                if(party.getMandates()>selected.getMandates())
                {
                    selectedId = partyId;
                }
        }
        return selectedId;
    }
    return -1;
}