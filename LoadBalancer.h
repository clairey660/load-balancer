#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
#include <fstream>
#include "Webserver.h"
#include "RequestQueue.h"

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer that distributes requests across a set of web servers.
 *
 * The LoadBalancer manages a queue of incoming requests and a pool of Webserver instances.
 * It simulates the passage of time and distributes requests to available servers.
 */
class LoadBalancer
{
private:
    std::ofstream logFile; /**< ofstream log file */

    std::vector<Webserver> servers; /**< Pool of web servers */
    RequestQueue requestQueue;      /**< Queue of pending requests */
    int curTime;                    /**< Current simulation time (in clock cycles) */
    int numRequestsProcessed;       /**< Number of requests processed by the servers */
    int observedMinRequestTime;
    int observedMaxRequestTime;

    /**
     * @brief Distributes requests from the queue to any available (idle) servers.
     */
    void distributeRequests();

public:
    /**
     * @brief Constructs a LoadBalancer with a given number of servers.
     * @param numOfServers The number of web servers to create.
     */
    LoadBalancer(int numOfServers);

    /**
     * @brief Destructs a LoadBalancer.
     */
    ~LoadBalancer();

    /**
     * @brief Populates the request queue with a specified number of random requests.
     * @param fullQueue The number of requests to generate and enqueue.
     */
    void populateQueue(int fullQueue);

    /**
     * @brief Advances the simulation by one clock cycle.
     *
     * This ticks each server and distributes new requests to idle ones.
     */
    void incrementTime();

    /**
     * @brief Prints the final results of the simulation to the console.
     */
    void showResults(int time, int queueSize);

    /**
     * @brief Checks if all requests have been processed by the load balancer.
     *
     * This function returns true only if the request queue is empty and all servers
     * are currently idle (i.e., not processing any tasks).
     *
     * @return true if all requests have been processed; false otherwise.
     */
    bool allRequestsProcessed() const;
};

#endif // LOADBALANCER_H