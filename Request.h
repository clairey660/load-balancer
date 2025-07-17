#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a single web request to be processed by a web server.
 *
 * Each request has:
 * - an input IP address (source),
 * - an output IP address (destination),
 * - and a time requirement indicating how many clock cycles are needed to process it.
 */
struct Request
{
    /**
     * @brief The source IP address of the request.
     */
    std::string ip_in;

    /**
     * @brief The destination IP address of the request.
     */
    std::string ip_out;

    /**
     * @brief The number of clock cycles needed to complete the request.
     */
    int time_required;
};

#endif // REQUEST_H
