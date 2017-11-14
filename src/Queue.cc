#include "Queue.h"
#include<stack>
#include "Job_m.h"

Define_Module(Queue);

using namespace std;

//
// _______________________________________________________________________________________
// The following function initialize some statistics and, according to the assumption
// set the server to free, throught its boolean status flag "isServerFree"
//
void Queue::initialize()
{
    isServFree=true;
    N_q=registerSignal("N_q");
    qtSig=registerSignal("qtSig");
    scheduleAt(simTime(),new cMessage("",2));
}

//
// _______________________________________________________________________________________
// The following function handle the incoming message "msg" and discriminate it through its
// attribute "kind", a default short int defined into the cMessage class. If:
//    ->kind=2, the message is an Self-message for the sampling and is handled by the
//              sample() function;
//    ->kind=1, the message is a server status message and is handled by the
//              handleServStat() function;
//    ->kind=0, the message is a job and is handled by the handleJob() function.
//
void Queue::handleMessage(cMessage *msg)
{

    if(msg->getKind()==0)  handleJob(msg);
    if(msg->getKind()==1)  handleServStat(msg);
    if(msg->getKind()==2)  sample(msg);
}

//
//      The following function handle incoming server status information, updating  the
//      "isServerFree" boolean inside the queue module.
//      The message will be deleted after that "isServFree" flag is set to true.
//      Then it checks if the queue contains at least one job, in this case, the server
//      flag will be set to false (server busy) and a new job will be popped and sent to
//      the server.
//
void Queue::handleServStat(cMessage *msg)
    {
        delete msg;
        isServFree=true;
        EV<<"Server free"<<endl;
        if(!simQueue.empty())
        {
            isServFree=false;
            Job *j=new Job();
            *j=simQueue.top();
            simQueue.pop();
            send(j,"out");
            EV<<"Job popped and sent."<<endl;
            emit(qtSig,simTime().dbl()-j->getDepartureTime()); // to calculate Queue-time
        }
    }

//
//      The following function handle incoming cMessages as Jobs, they are forwarded in case
//      of the server is free, enqueued otherwise.
//
void Queue::handleJob(cMessage *msg)
    {
        Job *j=check_and_cast<Job*>(msg);
        j->setID(simQueue.size());
        if(isServFree)
        {
            isServFree=false;
            send(j,"out");
            EV<<"Job sent directly."<<endl;
            emit(qtSig,simTime().dbl()-j->getDepartureTime());
        }
        else
        {
            if((int)simQueue.size()<(int)par("queueDim"))
            {
                simQueue.push(*j);
                EV<<"Job pushed at position "<<simQueue.size()<<endl;
            }
            delete j;
        }
    }

//
//      The following function only samples queue dimension every Tc seconds in order to emit
//      signals for N_q statistic.
//

void Queue::sample(cMessage *msg)
    {
    emit(N_q,simQueue.size());
    scheduleAt(simTime()+par("Tc"),new cMessage("",2));
    delete msg;
    }
