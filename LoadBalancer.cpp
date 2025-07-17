#include "LoadBalancer.h"
#include "Webserver.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructs the LoadBalancer and initializes web servers.
 *
 * Also seeds the random number generator for request generation.
 *
 * @param numOfServers The number of Webserver instances to create.
 */
LoadBalancer::LoadBalancer(int numOfServers) : curTime(0), numRequestsProcessed(0)
{
    // create the number of webservers requesteds
    srand(time(0));
    for (int i = 0; i < numOfServers; ++i)
    {
        servers.push_back(Webserver());
    }
}

/**
 * @brief Populates the request queue with randomly generated requests.
 *
 * Each request has a randomly generated IP address and a processing time between 1 and 10.
 *
 * @param fullQueue The number of requests to generate and enqueue.
 */
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

/**
 * @brief Distributes requests to idle servers from the queue.
 *
 * If a server is not busy and the queue is not empty, a request is assigned.
 */
void LoadBalancer::distributeRequests()
{
    for (Webserver &server : servers)
    {
        if (!server.isBusy() && !requestQueue.isEmpty())
        {
            Request r = requestQueue.pop();
            server.assignRequest(r);
        }
    }
}

/**
 * @brief Advances the simulation by one clock cycle.
 *
 * Ticks each server, updates request completion, and attempts to assign new requests.
 */
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

/**
 * @brief Prints the simulation results to the console.
 *
 * Displays total clock cycles elapsed, requests processed, and queue size.
 */
void LoadBalancer::showResults()
{
    std::cout << "Simulation Time Elapsed: " << curTime << " cycles\n";
    std::cout << "Total Requests Processed: " << numRequestsProcessed << "\n";
    std::cout << "Requests Remaining in Queue: " << requestQueue.size() << "\n";
}