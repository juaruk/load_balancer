#include "loadbalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//Load balancer contains a  list that contains multiple server, and a queue of requests
LoadBalancer::LoadBalancer(int numServers) : currentTime(0) {
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(new WebServer());
    }
    srand(time(0));
}

LoadBalancer::~LoadBalancer() {
    for (auto* server : servers) delete server;
}

// requests from the servers get added in the queue
void LoadBalancer::addRequest(const Request& req) {
    requestQueue.push(req);
}

void LoadBalancer::distributeRequests() {
    //this is assigning requests to the servers if they're not doing anything and there are requests
    for (auto* server : servers) {
        if (server->isIdle() && !requestQueue.empty()) {
            server->assignRequest(requestQueue.front());
            requestQueue.pop();
        }
    }
}

void LoadBalancer::tick() {
    // currenttime acts as the clock cycle
    ++currentTime;
    for (auto* server : servers) server->tick();
    if (rand() % 10 < 7) { // generates number from 1-10, 70% chance to add new requests to prevent queue from growing too fast
        //if request is made, random ip address
        std::string ip1 = std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256);
        std::string ip2 = std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256) + "." +
                          std::to_string(rand() % 256);

        //requests will be added to the queue with a random clock cycle time(between 10-20)
        addRequest(Request(ip1, ip2, 10 + rand() % 11)
);
    }
    //once we add the request, we need to see if any servers are available to handle it
    distributeRequests();
}

//this is how load balancer increments time
void LoadBalancer::simulate(int totalTime, std::ostream& out) {
    for (int i = 0; i < totalTime; ++i) {
        tick();
        out << "Tick: " << i + 1 << ", Requests in queue: " << requestQueue.size() << "\n";
    }
}
