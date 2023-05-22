#include "Coalition.h"
#include "Party.h"

Coalition::Coalition(const Party &party) : cId(party.getId()),cMandates(party.getMandates()),cParties(vector<Party>())
{
    cParties.push_back(party);
}


int Coalition::getMandates()
{
    return cMandates;
}

void Coalition::addParty(Party party)
{
    // add a party to the vector
    cParties.push_back(party);
    cMandates += party.getMandates();
}

int Coalition::getId()
{
    return cId;
}

const vector<Party> Coalition::getParties() const
{
    return cParties;
}

