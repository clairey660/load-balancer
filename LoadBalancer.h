#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <iostream>
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
    std::vector<Webserver> servers; /**< Pool of web servers */
    RequestQueue requestQueue;      /**< Queue of pending requests */
    int curTime;                    /**< Current simulation time (in clock cycles) */
    int numRequestsProcessed;       /**< Number of requests processed by the servers */

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
    void showResults();
};

#endif // LOADBALANCER_H