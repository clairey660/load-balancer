#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
/**
 * @class Webserver
 * @brief Represents a single web server that can process one request at a time.
 */
class Webserver
{
private:
    Request currentRequest;
    bool busy;
    int clockRemaining;

public:
    /**
     * @brief Constructs an idle Webserver.
     */
    Webserver();

    /**
     * @brief Assigns a new request to the web server.
     * @param r The Request to assign.
     */
    void assignRequest(Request &r);

    /**
     * @brief Advances the server's processing time by one clock cycle.
     */
    void incrementTime();

    /**
     * @brief Checks if the server is currently busy processing a request.
     * @return true if busy, false otherwise.
     */
    bool isBusy();
};
#endif // WEBSERVER_H