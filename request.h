#ifndef REQUEST_H
#define REQUEST_H

#include <string>
struct Request {
    std::string ip_in;
    std::string ip_out;
    int time;

    Request(std::string in, std::string out, int t);
    Request();
};

#endif // REQUEST_H
