#include "loadbalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

/**
 * @brief Converts IPv4 string to a 32-bit unsigned int for easy comparison.
 *
 * Parses the IPv4 string (e.g., "192.168.1.1") into its four octets, then
 * shifts and combines them into a single 32-bit integer.
 *
 * @param ip IPv4 address as string.
 * @return uint32_t Numeric representation of IP.
 */
uint32_t LoadBalancer::ipToUint(const std::string& ip) {
    std::istringstream ss(ip);
    uint32_t a, b, c, d;
    char dot;
    ss >> a >> dot >> b >> dot >> c >> dot >> d;
    return (a << 24) | (b << 16) | (c << 8) | d;
}

/**
 * @brief List of blocked IP ranges (start and end inclusive).
 *
 * This static array holds pairs of start and end IPs represented as
 * 32-bit unsigned integers, defining IP address ranges to block.
 */
const std::pair<uint32_t, uint32_t> LoadBalancer::blockedRanges[] = {
    std::make_pair((192u << 24) | (168u << 16) | (0u << 8) | 0u,
                   (192u << 24) | (168u << 16) | (255u << 8) | 255u)
};

/** 
 * @brief Number of blocked IP ranges.
 */
const size_t LoadBalancer::blockedRangesCount = sizeof(LoadBalancer::blockedRanges) / sizeof(LoadBalancer::blockedRanges[0]);

/**
 * @brief Checks if the IP address is in any blocked range.
 *
 * Converts the given IP string to its numeric form and checks
 * if it lies within any blocked range.
 *
 * @param ip IP address as string.
 * @return true If the IP is blocked.
 * @return false Otherwise.
 */
bool LoadBalancer::isBlockedIP(const std::string& ip) {
    uint32_t ipNum = ipToUint(ip);
    for (size_t i = 0; i < blockedRangesCount; ++i) {
        if (ipNum >= blockedRanges[i].first && ipNum <= blockedRanges[i].second)
            return true;
    }
    return false;
}

/**
 * @brief Constructor initializes the LoadBalancer with specified servers.
 *
 * @param numServers Number of web servers to create.
 */
LoadBalancer::LoadBalancer(int numServers) : currentTime(0) {
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(new WebServer());
    }
    srand(time(0));
}

/**
 * @brief Destructor cleans up dynamically allocated servers.
 */
LoadBalancer::~LoadBalancer() {
    for (auto* server : servers) delete server;
}

/**
 * @brief Adds a new request to the queue if its source IP is not blocked.
 *
 * @param req Request to be added.
 */
void LoadBalancer::addRequest(const Request& req) {
    if (!isBlockedIP(req.ip_in)) {
        requestQueue.push(req);
    }
}

/**
 * @brief Assigns queued requests to any idle servers.
 *
 * Checks all servers and assigns requests from the queue to those
 * which are idle, popping the assigned requests from the queue.
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
 * @brief Advances simulation time by one tick.
 *
 * Increments the internal clock, updates all servers, and
 * potentially adds new requests with a 70% probability.
 */
void LoadBalancer::tick() {
    ++currentTime;
    for (auto* server : servers) server->tick();

    if (rand() % 10 < 7) { // 70% chance of new request
        std::string ip1 = std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256);
        std::string ip2 = std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256);
        addRequest(Request(ip1, ip2, 10 + rand() % 11));
    }

    distributeRequests();
}

/**
 * @brief Runs the simulation for a given number of clock cycles.
 *
 * @param totalTime Number of clock cycles to simulate.
 * @param out Output stream to write the simulation log.
 */
void LoadBalancer::simulate(int totalTime, std::ostream& out) {
    out << "Simulation started: Task time range = 10 to 20 clock cycles\n";
    for (int i = 0; i < totalTime; ++i) {
        tick();
        out << "Tick: " << i + 1 << ", Requests in queue: " << requestQueue.size() << "\n";
    }
}
