#include "LoadBalancer.h"
#include "Webserver.h"

LoadBalancer::LoadBalancer(int numOfServers)
{
    // create the number of webservers requesteds
    for (int i = 0; i < numOfServers; ++i)
    {
        servers.push_back(Webserver());
    }
}
void LoadBalancer::populateQueue(int fullQueue)
{
}
void LoadBalancer::distributeRequests() {}
void LoadBalancer::incrementTime()
{
    ++curTime;
}
void LoadBalancer::showResults()
{
}