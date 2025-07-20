#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include <ostream> 
#include "webserver.h"
#include "request.h"
//webserver is the class that is the server

/**
 * @class LoadBalancer
 * @brief Distributes requests to available web servers.
 */
class LoadBalancer {
private:
    std::vector<WebServer*> servers;
    std::queue<Request> requestQueue;
    int currentTime;

public:
    LoadBalancer(int numServers);
    ~LoadBalancer();
    void addRequest(const Request& req);
    void distributeRequests();
    void tick();
    void simulate(int totalTime, std::ostream& out);
};

#endif // LOADBALANCER_H
