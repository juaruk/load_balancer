#include "webserver.h"
#include "request.h"

WebServer::WebServer() : timeRemaining(0), busy(false) {}

//webserver is in charge of handling its assigned requests and seeing if it is idle
void WebServer::assignRequest(const Request& req) {
    currentRequest = req;
    timeRemaining = req.time;
    busy = true;
}

//making sure request gets done within set time
void WebServer::tick() {
    if (busy) {
        --timeRemaining;
        if (timeRemaining <= 0) busy = false;
    }
}

bool WebServer::isIdle() const {
    return !busy;
}
