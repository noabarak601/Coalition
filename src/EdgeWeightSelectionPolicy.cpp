#include "SelectionPolicy.h"
#include "Simulation.h"
#include <iostream>
using std::cout;
SelectionPolicy* EdgeWeightSelectionPolicy:: clone()
{
    return new EdgeWeightSelectionPolicy();
}

int EdgeWeightSelectionPolicy::select(vector<int> potentialParties, int partyId, Simulation &sim)
{
    int size = potentialParties.size();
    if (size>0)
    {
        vector<int>weights = sim.getWeights(potentialParties,partyId);
        int selectedWeightIndex = 0;
        int weightSize = weights.size();
        for (int i=0; i < weightSize; i++)
        { 
            if (weights[i]>weights[selectedWeightIndex])
            {
                selectedWeightIndex = i;
            }
        }
        return potentialParties[selectedWeightIndex];
    }
    return -1;
}