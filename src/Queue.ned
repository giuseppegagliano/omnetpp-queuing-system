package project6.simulations;

//
// _______________________________________________________________________________
// 
//
simple Queue
{
    parameters:
        @statistic[N_q](title="N_q"; source="N_q";record=vector,stats);
        @statistic[qtSig](title="Queueing_time";source="qtSig";record=vector,mean);
        @statistic[dropCountSig](title="#_of_dropped_jobs";source="dropCountSig";record=count);
        int queueDim=default(100000);
        double Tc=default(50);
    gates:
        input in[];
        output out;
}
