#include <iostream>
#include "Webserver.h"
#include "RequestQueue.h"
#ifndef LOADBALANCER_H
#define LOADBALANCER_H

class LoadBalancer
{
private:
    std::vector<Webserver> servers;
    RequestQueue requestQueue;
    int curTime;
    int numRequestsProcessed;

    void distributeRequests();

public:
    LoadBalancer(int numOfServers);
    void populateQueue(int fullQueue);

    void incrementTime();
    void showResults();
};

#endif