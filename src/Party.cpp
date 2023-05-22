#include "Party.h"
#include "Agent.h"
#include "JoinPolicy.h"
#include "Coalition.h"
#include "Simulation.h"
#include <vector>
using std::vector;


Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), timer(0),offers(vector<int>())
{
    // You can change the implementation of the constructor, but not the signature!
}
Party::~Party()
{
    if (mJoinPolicy)
    {
        delete mJoinPolicy;
    }
}

Party::Party(const Party &other) : mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(nullptr),mState(other.mState),timer(other.timer),offers(vector<int>())
{
    mJoinPolicy = other.mJoinPolicy->pClone();
    for(int coalitionId: other.offers)
    {
        offers.push_back(coalitionId);
    }
}

Party::Party(Party &&other) : mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy),mState(other.mState),timer(other.timer),offers(vector<int>()) 
{
    other.mJoinPolicy = nullptr;
    for(int coalitionId: other.offers)
    {
        offers.push_back(coalitionId);
    }
}
Party &Party::operator=(const Party &other) 
{
    *mJoinPolicy = (*(other.mJoinPolicy));
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    timer = other.timer;

    return *this;
}

Party& Party::operator=(Party &&other)
{
    if (mJoinPolicy)
    {
        delete mJoinPolicy;
    }
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    timer = other.timer;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;
    return *this;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string &Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    // TODO: implement this method
    if (mState == CollectingOffers)
    {
        timerCheck(s);
    }
}

void Party::timerCheck(Simulation &s)
{
    if (timer < 2)
    {
        timer++;
    }
    else
    {
        int joinedToId = (*mJoinPolicy).join(offers, s);
        s.getCoalition(joinedToId).addParty(*this);
        mState = Joined;
        s.addAgent(Agent(s.getAgents().size(), mId, s.getAgent(joinedToId).getSelectionPolicy()->clone()));
        
        s.upadteNotJoinedParties();
        int joinedToMandates = s.getCoalition(joinedToId).getMandates();
        if (joinedToMandates > s.getMaxMandates())
        {
            s.updateMaxMandates(joinedToMandates);
        }
    }
}

const int Party::getId() const
{
    return mId;
}

vector<int> Party::getOffers()
{
    return offers;
}

bool Party::sameCoalitionOffered(int myCoalitionId)
{
    bool sameCoalition = false;
    for (int coalitionId : offers)
    {
        if (coalitionId == myCoalitionId)
        {
            sameCoalition = true;
        }
    }
    return sameCoalition;
}

void Party::addOffer(int coalition)
{
    offers.push_back(coalition);
}