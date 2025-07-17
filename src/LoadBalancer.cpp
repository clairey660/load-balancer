#include "LoadBalancer.h"
#include "Webserver.h"
#include "RequestQueue.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

/**
 * @brief Constructs the LoadBalancer and initializes web servers.
 *
 * Also seeds the random number generator for request generation.
 *
 * @param numOfServers The number of Webserver instances to create.
 */
LoadBalancer::LoadBalancer(int numOfServers) : curTime(0), numRequestsProcessed(0),
                                               minRequestTime(INT_MAX),
                                               maxRequestTime(INT_MIN)
{
    // create the number of webservers requesteds
    srand(time(0));
    logFile.open("simulation_log.txt");
    if (!logFile.is_open())
    {
        std::cerr << "Error opening simulation_log.txt for writing.\n";
    }

    for (int i = 0; i < numOfServers; ++i)
    {
        servers.push_back(Webserver());
    }
}

/**
 * @brief Deconstructs the LoadBalancer.
 *
 * Closes the log file.
 */
LoadBalancer::~LoadBalancer()
{
    if (logFile.is_open())
        logFile.close();
}

/**
 * @brief Generates a random IP address and converts to a string.
 *
 * @return string value of random IP address.
 */
std::string LoadBalancer::generateRandIP()
{
    return std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256);
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
    logFile << "Populating queue with " << fullQueue << " requests.\n";
    for (int i = 0; i < fullQueue; ++i)
    {
        Request r;
        r.ip_in = generateRandIP();
        r.ip_out = generateRandIP();
        r.time_required = 1 + (rand() % 10);

        // Update observed min/max
        if (r.time_required < minRequestTime)
            minRequestTime = r.time_required;
        if (r.time_required > maxRequestTime)
            maxRequestTime = r.time_required;

        logFile << "Request " << i + 1 << ": from " << r.ip_in << " to " << r.ip_out
                << " requires " << r.time_required << " cycles\n";

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
    for (size_t i = 0; i < servers.size(); ++i)
    {
        if (!servers[i].isBusy() && !requestQueue.isEmpty())
        {
            Request r = requestQueue.pop();
            servers[i].assignRequest(r);

            logFile << "[Time " << curTime << "] Server " << i + 1 << " assigned request from "
                    << r.ip_in << " to " << r.ip_out << " ("
                    << r.time_required << " cycles)\n";
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
    const int maxServers = 100;
    const int minServers = 1;

    if (requestQueue.size() > servers.size() * 50 && servers.size() < maxServers)
    {
        servers.push_back(Webserver());
        logFile << "[Time " << curTime << "] Added a new server. Total servers: " << servers.size() << "\n";
    }

    // Remove servers (if you implemented shutdown logic)
    else if (requestQueue.size() < servers.size() * 10 && servers.size() > minServers)
    {
        servers.pop_back();
        logFile << "[Time " << curTime << "] Removed a server. Total servers: " << servers.size() << "\n";
    }

    int activeServers = 0;
    int idleServers = 0;

    for (size_t i = 0; i < servers.size(); ++i)
    {
        if (rand() % 10 < 3)
        { // 30% chance
            int time = rand() % (maxRequestTime - minRequestTime + 1) + minRequestTime;
            Request r;
            r.ip_in = generateRandIP();
            r.ip_out = generateRandIP();
            r.time_required = time;
            requestQueue.push_back(r);
        }

        if (servers[i].isBusy())
        {
            servers[i].incrementTime();

            if (!servers[i].isBusy())
            {
                numRequestsProcessed++;
                logFile << "[Time " << curTime << "] Server " << i + 1 << " finished processing a request.\n";
            }
            activeServers++;
        }
        else
        {
            idleServers++;
        }
    }

    distributeRequests();

    // Log status for this tick
    logFile << "[Time " << curTime << "] Active Servers: " << activeServers
            << ", Idle Servers: " << idleServers
            << ", Requests in Queue: " << requestQueue.size()
            << ", Requests Processed: " << numRequestsProcessed << "\n";
}

/**
 * @brief Prints the simulation results to the console.
 *
 * Displays total clock cycles elapsed, requests processed, and queue size.
 */
void LoadBalancer::showResults(int time, int queueSize)
{
    logFile << "\n=== Simulation Summary ===\n";
    logFile << "Number of Servers        : " << servers.size() << "\n";
    logFile << "Simulation Clock Cycles  : " << curTime << "\n";
    logFile << "Initial Queue Size       : " << queueSize << "\n";
    logFile << "Final Queue Size         : " << requestQueue.size() << "\n";
    logFile << "Request Time Range       : "
            << minRequestTime << " to " << maxRequestTime << " cycles\n";
    logFile << "Total Requests Processed : " << numRequestsProcessed << "\n";

    bool allProcessed = allRequestsProcessed();
    logFile << "All Requests Fully Processed: " << (allProcessed ? "Yes" : "No") << "\n";
    logFile << "==========================\n";

    logFile.flush();
}

/**
 * @brief Determines whether all requests have been processed.
 *
 * This method verifies that both the internal request queue is empty and that
 * every server is currently idle. This ensures that no request is waiting or
 * being processed.
 *
 * @return true if the queue is empty and all servers are idle; false otherwise.
 */
bool LoadBalancer::allRequestsProcessed() const
{
    if (!requestQueue.isEmpty())
        return false;

    for (const Webserver &server : servers)
    {
        if (!server.isIdle())
            return false;
    }

    return true;
}
