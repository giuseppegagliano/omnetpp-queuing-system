package project6.simulations;

//
// _______________________________________________________________________________
//
network ProjectNet
{
    @display("bgb=547,175;i=background/green,,10");
    submodules:
        Snd: Sender {
            @display("p=59,74;is=l;i=msg/job;t=Sender,,#004080");
        }
        Srv: Server {
            @display("p=440,74;i=abstract/server;t=Server,,#004080;is=l");
        }
        Q: Queue {
            @display("p=245,74;is=l;i=block/queue;t=Stack,,#004080");
        }
    connections:
        Snd.out --> Q.in++;
        Srv.out --> Q.in++;
        Q.out --> Srv.in;
}
