#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"

/**
 * @class WebServer
 * @brief Represents a server that processes requests over discrete clock cycles.
 */
class WebServer {
private:
    Request currentRequest;  /**< The request currently being processed */
    int timeRemaining;       /**< Remaining time (in clock cycles) to complete the current request */
    bool busy;               /**< Server busy status: true if processing a request, false otherwise */

public:
    /**
     * @brief Constructs a WebServer object with no active requests.
     */
    WebServer();

    /**
     * @brief Assigns a request to this server and starts processing it.
     * @param req The request to be processed.
     */
    void assignRequest(const Request& req);

    /**
     * @brief Simulates a clock tick, decreasing the remaining processing time.
     * Once the time remaining reaches zero, the server becomes idle.
     */
    void tick();

    /**
     * @brief Checks if the server is currently idle (not busy processing).
     * @return True if the server is idle, false otherwise.
     */
    bool isIdle() const;
};

#endif // WEBSERVER_H
