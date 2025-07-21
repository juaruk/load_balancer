#include "webserver.h"
#include "request.h"

/**
 * @brief Constructs a WebServer instance with no active request.
 */
WebServer::WebServer() : timeRemaining(0), busy(false) {}

/**
 * @brief Assigns a request to this server and starts processing.
 * @param req The request to be processed by the server.
 */
void WebServer::assignRequest(const Request& req) {
    currentRequest = req;
    timeRemaining = req.time;
    busy = true;
}

/**
 * @brief Simulates a clock tick; decreases remaining time for current request.
 * If the request is finished, the server becomes idle.
 */
void WebServer::tick() {
    if (busy) {
        --timeRemaining;
        if (timeRemaining <= 0) busy = false;
    }
}

/**
 * @brief Checks if the server is currently idle (not processing any request).
 * @return true if the server is idle, false otherwise.
 */
bool WebServer::isIdle() const {
    return !busy;
}

