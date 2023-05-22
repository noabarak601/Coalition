#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;
class Coalition;
class Party;
class Simulation;

class JoinPolicy {
    public:
    virtual ~JoinPolicy() = default;
    virtual int join(vector<int> coalitions, Simulation &sim) = 0;
    virtual JoinPolicy* pClone() = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
    virtual int join(vector<int> coalitions, Simulation &sim);  
    virtual JoinPolicy* pClone();
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
    virtual int join(vector<int> coalitions, Simulation &sim); 
    virtual JoinPolicy* pClone(); 
};