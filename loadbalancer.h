#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include <ostream> 
#include "webserver.h"
#include "request.h"

/**
 * @class LoadBalancer
 * @brief Distributes incoming web requests among a pool of web servers.
 * 
 * The LoadBalancer maintains a queue of incoming requests and a vector of
 * pointers to WebServer instances. It simulates time passing by clock cycles,
 * distributes queued requests to available servers, and logs the simulation.
 */
class LoadBalancer {
private:
    /** Vector of pointers to WebServer objects managed by this load balancer */
    std::vector<WebServer*> servers;

    /** Queue holding incoming requests waiting to be processed */
    std::queue<Request> requestQueue;

    /** Current simulation time in clock cycles */
    int currentTime;

public:
    /**
     * @brief Constructs a LoadBalancer with a specified number of servers.
     * @param numServers Number of web servers to initialize.
     */
    LoadBalancer(int numServers);

    /**
     * @brief Destructor to clean up dynamically allocated WebServer objects.
     */
    ~LoadBalancer();

    /**
     * @brief Adds a new request to the request queue.
     * @param req The request to add.
     */
    void addRequest(const Request& req);

    /**
     * @brief Distributes queued requests to available servers.
     * 
     * Assigns requests from the queue to servers that are free to process them.
     */
    void distributeRequests();

    /**
     * @brief Advances the simulation by one clock cycle.
     * 
     * Increments current time, ticks each server, generates new requests
     * probabilistically, and distributes them.
     */
    void tick();

    /**
     * @brief Runs the simulation for a specified total number of clock cycles.
     * @param totalTime Total number of clock cycles to simulate.
     * @param out Output stream to log simulation information.
     */
    void simulate(int totalTime, std::ostream& out);
};

#endif // LOADBALANCER_H

