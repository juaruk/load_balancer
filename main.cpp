#include <iostream>
#include "loadbalancer.h"
#include "request.h"
#include <fstream>

int main() {
    int numServers, totalTime;
    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter simulation time (in clock cycles): ";
    std::cin >> totalTime;


    LoadBalancer lb(numServers);
    for (int i = 0; i < numServers * 100; ++i) {
        lb.addRequest(Request("1.2.3.4", "5.6.7.8", 1 + rand() % 10));
    }

    // Open log file
    std::ofstream logFile("simulation_log.txt");
    lb.simulate(totalTime, logFile);
    logFile.close();
    
    std::cout << "Simulation complete." << std::endl;
    return 0;
}