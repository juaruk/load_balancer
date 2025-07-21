#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a network request with source IP, destination IP, and execution time.
 */
struct Request {
    std::string ip_in;  /**< Source IP address */
    std::string ip_out; /**< Destination IP address */
    int time;           /**< Execution time or clock cycles needed to process the request */

    /**
     * @brief Constructs a Request with given input IP, output IP, and processing time.
     * @param in Source IP address
     * @param out Destination IP address
     * @param t Execution time in clock cycles
     */
    Request(std::string in, std::string out, int t);

    /**
     * @brief Default constructor. Initializes IPs to "0.0.0.0" and time to 0.
     */
    Request();
};

#endif // REQUEST_H

