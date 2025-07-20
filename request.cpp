#include "request.h"
#include <cstdlib>

//simple request interface, request has random home id, random out id, and random execution time
Request::Request(std::string in, std::string out, int t) : ip_in(in), ip_out(out), time(t) {}
Request::Request() : ip_in("0.0.0.0"), ip_out("0.0.0.0"), time(0) {}