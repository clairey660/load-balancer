/**
 * @file main.cpp
 * @brief Entry point for the Load Balancer simulation.
 *
 * This program prompts the user for the number of web servers and the
 * duration of the simulation (in clock cycles), then creates a
 * LoadBalancer instance and runs the simulation.
 */

#include <iostream>
#include "LoadBalancer.h"

/**
 * @brief Main function that drives the load balancer simulation.
 *
 * Prompts the user for:
 * - The number of web servers
 * - The number of clock cycles to run the simulation
 *
 * It then:
 * - Initializes the LoadBalancer with the specified number of servers
 * - Populates the request queue (servers * 100)
 * - Simulates the passage of time by calling `incrementTime()` in a loop
 * - Displays the final results using `showResults()`
 *
 * @return int Exit code (0 on success)
 */
int main()
{
    // set up the number of servers (user input), and the time
    // you want to run the load balancer (user input)
    int numOfServers;
    int time;

    std::cout << "Enter number of servers: ";
    std::cin >> numOfServers;

    std::cout << "Enter time (clock cycles): ";
    std::cin >> time;

    LoadBalancer lb(numOfServers);
    // generate a full queue (usually servers * 100).
    lb.populateQueue(numOfServers * 100);

    for (int t = 0; t < time; ++t)
    {
        lb.incrementTime();
    }

    lb.showResults(time, numOfServers * 100);
    if (lb.allRequestsProcessed())
    {
        std::cout << "All requests have been fully processed.\n";
    }
    else
    {
        std::cout << "Warning: Some requests are still in progress or waiting.\n";
    }
    return 0;
}