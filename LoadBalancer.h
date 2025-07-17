#include <iostream>
#include "Webserver.h"
#ifndef LOADBALANCER_H
#define LOADBALANCER_H

class LoadBalancer
{
private:
    std::vector<Webserver> servers;

public:
    LoadBalancer(int numOfServers);
    void populateQueue(int fullQueue);
    void incrementTime();
    void showResults();
};

#endif