#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Party;

class Coalition
{
public:
    Coalition(const Party& party);
    
    int getMandates();
    void addParty(Party party);
    int getId();
    const vector<Party> getParties() const;

private:
    int cId;
    int cMandates;
    vector<Party> cParties;
};