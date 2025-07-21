#include "loadbalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructs a LoadBalancer and initializes the specified number of servers.
 * 
 * Also initializes the random number generator seed based on the current time.
 * @param numServers Number of WebServer instances to create.
 */
LoadBalancer::LoadBalancer(int numServers) : currentTime(0) {
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(new WebServer());
    }
    srand(time(0));
}

/**
 * @brief Destructor cleans up all dynamically allocated WebServer instances.
 */
LoadBalancer::~LoadBalancer() {
    for (auto* server : servers) delete server;
}

/**
 * @brief Adds a new request to the queue for processing.
 * @param req The Request object to enqueue.
 */
void LoadBalancer::addRequest(const Request& req) {
    requestQueue.push(req);
}

/**
 * @brief Assigns queued requests to idle servers if available.
 * 
 * Iterates over all servers, and if a server is idle and there is a request in the queue,
 * assigns the request to that server and removes it from the queue.
 */
void LoadBalancer::distributeRequests() {
    for (auto* server : servers) {
        if (server->isIdle() && !requestQueue.empty()) {
            server->assignRequest(requestQueue.front());
            requestQueue.pop();
        }
    }
}

/**
 * @brief Advances the simulation by one clock cycle.
 * 
 * Increments the internal clock, calls tick() on all servers,
 * probabilistically adds new requests with a 70% chance, 
 * and distributes any queued requests to available servers.
 */
void LoadBalancer::tick() {
    ++currentTime;
    for (auto* server : servers) server->tick();

    if (rand() % 10 < 7) { // 70% chance to generate a new request
        // Generate random IP addresses for source and destination
        std::string ip1 = std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256);
        std::string ip2 = std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256);

        // Add request with processing time between 10 and 20 clock cycles
        addRequest(Request(ip1, ip2, 10 + rand() % 11));
    }

    // Assign requests from the queue to any idle servers
    distributeRequests();
}

/**
 * @brief Runs the load balancer simulation for a given number of clock cycles.
 * 
 * Calls tick() repeatedly, and logs the current tick number and queue size to the output stream.
 * @param totalTime Number of clock cycles to simulate.
 * @param out Output stream to write simulation logs.
 */
void LoadBalancer::simulate(int totalTime, std::ostream& out) {
    for (int i = 0; i < totalTime; ++i) {
        tick();
        out << "Tick: " << i + 1 << ", Requests in queue: " << requestQueue.size() << "\n";
    }
}
