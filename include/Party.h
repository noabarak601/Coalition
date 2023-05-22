#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

class JoinPolicy;
class Coalition;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    virtual ~Party();
    Party(const Party& other);
    Party(Party&& other);
    Party& operator=(const Party& party);
    Party& operator=(Party &&other);

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    void timerCheck(Simulation &s);
    const int getId() const;
    vector<int> getOffers();
    bool sameCoalitionOffered(int coalitionId);
    void addOffer(int coalition);
    
private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    vector<int> offers;
};
