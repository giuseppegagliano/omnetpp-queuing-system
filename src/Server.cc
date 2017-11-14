#include "Server.h"
#include "Job_m.h"
Define_Module(Server);

//
// _______________________________________________________________________________
// The following function initialize statistics and parameter
//
void Server::initialize()
{
    stSig=registerSignal("stSig");
    rtSig=registerSignal("rtSig");
    serviceTime=0;
}

//
// ______________________________________________________________________________________
// The following function mainly simulate the server of the system. When a job comes from
// the queue, it will served for a "serviceTime" time i.e. a RV:
//  -> exponential distributed, when "isScenario1" is true
//  -> lognormal distributed, when isScenario1 is false
// Then it emits some signal for statistics collection and finally it sends the "serverFree"
// status to the queue.
//
void Server::handleMessage(cMessage *msg)
{
    Job *j=check_and_cast<Job*>(msg);

    if(par("isScenario1").boolValue())      serviceTime=(simtime_t)exponential((double)par("meanST"));
    else                                    serviceTime=(simtime_t)lognormal((double)par("scaleST"),(double)par("shapeST"));

    emit(rtSig,serviceTime+simTime()-j->getDepartureTime());
    emit(stSig,serviceTime);
    delete msg;

    cMessage *serverStatus=new cMessage();
    serverStatus->setKind(1);
    sendDelayed(serverStatus,serviceTime,"out");

}
