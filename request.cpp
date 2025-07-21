#include "request.h"
#include <cstdlib>

/**
 * @class Request
 * @brief Represents a network request with source and destination IPs and execution time.
 */

/**
 * @brief Constructs a Request with given input IP, output IP, and processing time.
 * @param in Source IP address (string).
 * @param out Destination IP address (string).
 * @param t Execution time or clock cycles needed to process the request.
 */
Request::Request(std::string in, std::string out, int t) : ip_in(in), ip_out(out), time(t) {}

/**
 * @brief Default constructor. Initializes IPs to "0.0.0.0" and time to 0.
 */
Request::Request() : ip_in("0.0.0.0"), ip_out("0.0.0.0"), time(0) {}
