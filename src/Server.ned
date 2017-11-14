package project6.simulations;

//
// _______________________________________________________________________________
// 
//
simple Server
{
    parameters:
        @statistic[stSig](title="Service_Time"; source="stSig";record=vector,mean);
        @statistic[rtSig](title="Response_Time"; source="rtSig";record=vector,stats);
        bool isScenario1=default(true);
        double meanST=default(1);
        double scaleST=default(1);
        double shapeST=default(1);
    gates:
    input in;
    output out;
}
