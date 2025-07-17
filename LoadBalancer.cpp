#include "LoadBalancer.h"
#include "Webserver.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

LoadBalancer::LoadBalancer(int numOfServers) : curTime(0), numRequestsProcessed(0)
{
    // create the number of webservers requesteds
    srand(time(0));
    for (int i = 0; i < numOfServers; ++i)
    {
        servers.push_back(Webserver());
    }
}
void LoadBalancer::populateQueue(int fullQueue)
{
    for (int i = 0; i < fullQueue; ++i)
    {
        Request r;
        r.ip_in = std::to_string(rand() % 256) + "." +
                  std::to_string(rand() % 256) + "." +
                  std::to_string(rand() % 256) + "." +
                  std::to_string(rand() % 256);

        r.ip_out = std::to_string(rand() % 256) + "." +
                   std::to_string(rand() % 256) + "." +
                   std::to_string(rand() % 256) + "." +
                   std::to_string(rand() % 256);

        r.time_required = 1 + (rand() % 10);
        requestQueue.push_back(r);
    }
}
void LoadBalancer::distributeRequests()
{
    for (Webserver &server : servers)
    {
        if (!server.isBusy() && !requestQueue.isEmpty())
        {
            Request r = requestQueue.pop();
            server.createRequest(r);
        }
    }
}
void LoadBalancer::incrementTime()
{
    ++curTime;
    for (Webserver &server : servers)
    {
        if (server.isBusy())
        {
            server.incrementTime();
            if (!server.isBusy())
            {
                numRequestsProcessed++;
            }
        }
    }

    distributeRequests();
}
void LoadBalancer::showResults()
{
    std::cout << "Simulation Time Elapsed: " << curTime << " cycles\n";
    std::cout << "Total Requests Processed: " << numRequestsProcessed << "\n";
    std::cout << "Requests Remaining in Queue: " << requestQueue.size() << "\n";
}