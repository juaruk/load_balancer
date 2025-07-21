/**
 * @file main.cpp
 * @brief Entry point for simulating a load balancer with multiple web servers.
 * 
 * This program prompts the user to enter the number of servers and the total
 * simulation time (in clock cycles). It initializes a load balancer, preloads
 * it with requests, and logs the simulation output to a file.
 */

#include <iostream>
#include "loadbalancer.h"
#include "request.h"
#include <fstream>

/**
 * @brief Main function for running the load balancer simulation.
 * 
 * Prompts user input for number of servers and simulation time. Pre-loads
 * the request queue and writes simulation logs to "simulation_log.txt".
 * 
 * @return int Returns 0 on successful completion.
 */
int main() {
    int numServers, totalTime;

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;

    std::cout << "Enter simulation time (in clock cycles): ";
    std::cin >> totalTime;

    LoadBalancer lb(numServers);

    // Pre-load the request queue with initial traffic
    for (int i = 0; i < numServers * 100; ++i) {
        lb.addRequest(Request("1.2.3.4", "5.6.7.8", 10 + rand() % 11)); // 10–20 cycles
    }

    // Open log file and start simulation
    std::ofstream logFile("simulation_log.txt");
    lb.simulate(totalTime, logFile);
    logFile.close();

    std::cout << "Simulation complete." << std::endl;
    return 0;
}
