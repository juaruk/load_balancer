#ifndef WEBSERVER_H
#define WEBSERVER_H

class WebServer {
private:
    Request currentRequest;
    int timeRemaining;
    bool busy;

public:
    WebServer();
    void assignRequest(const Request& req);
    void tick();
    bool isIdle() const;
};

#endif // WEBSERVER_H

