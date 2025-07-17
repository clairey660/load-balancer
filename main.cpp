#include <iostream>
#include "LoadBalancer.h"
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

    lb.showResults();
    return 0;
}