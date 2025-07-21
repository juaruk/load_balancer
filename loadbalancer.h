#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include <ostream>
#include <string>
#include "webserver.h"
#include "request.h"

/**
 * @class LoadBalancer
 * @brief Manages a pool of web servers and distributes incoming requests to them.
 *
 * This class maintains a queue of pending requests and a vector of web servers.
 * It supports IP-based blocking of requests and simulates the processing of requests
 * over discrete clock cycles.
 */
class LoadBalancer {
private:
    std::vector<WebServer*> servers;   ///< List of servers managed by the load balancer
    std::queue<Request> requestQueue;  ///< Queue of pending requests waiting to be assigned
    int currentTime;                   ///< Current simulation clock cycle
    static const std::pair<uint32_t, uint32_t> blockedRanges[];  ///< Array of blocked IP ranges (start/end)
    static const size_t blockedRangesCount;                      ///< Number of blocked IP ranges

    /**
     * @brief Converts an IPv4 address string to a 32-bit unsigned integer.
     *
     * @param ip IPv4 address in dotted decimal notation (e.g., "192.168.1.1")
     * @return uint32_t Numeric representation for easy comparison and range checks.
     */
    static uint32_t ipToUint(const std::string& ip);

    /**
     * @brief Determines whether the given IP is within any blocked IP range.
     *
     * @param ip IPv4 address as string.
     * @return true If IP falls within a blocked range.
     * @return false Otherwise.
     */
    static bool isBlockedIP(const std::string& ip);

public:
    /**
     * @brief Constructs the LoadBalancer and initializes the specified number of web servers.
     *
     * @param numServers Number of web servers to create and manage.
     */
    LoadBalancer(int numServers);

    /**
     * @brief Destructor that releases all dynamically allocated web servers.
     */
    ~LoadBalancer();

    /**
     * @brief Adds a new request to the queue if the source IP is not blocked.
     *
     * @param req Request object containing source/destination IP and processing time.
     */
    void addRequest(const Request& req);

    /**
     * @brief Assigns queued requests to idle servers, if available.
     */
    void distributeRequests();

    /**
     * @brief Advances the simulation by one clock cycle, processing requests and
     * optionally adding new requests.
     */
    void tick();

    /**
     * @brief Runs the simulation for the specified number of clock cycles,
     * logging the status of the request queue.
     *
     * @param totalTime Number of clock cycles to simulate.
     * @param out Output stream where simulation logs will be written.
     */
    void simulate(int totalTime, std::ostream& out);
};

#endif // LOADBALANCER_H
