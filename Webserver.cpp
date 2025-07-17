#include "Webserver.h"
/**
 * @brief Constructor initializes the server as idle.
 */
Webserver::Webserver() : busy(false), clockRemaining(0)
{
}
/**
 * @brief Assigns a request to the web server and sets the processing time.
 *
 * This function marks the server as busy and stores the request details,
 * including the number of cycles required to process it.
 *
 * @param r The incoming Request object to be processed.
 */
void Webserver::assignRequest(Request &r)
{
    currentRequest = r;
    clockRemaining = r.time_required;
    busy = true;
}

/**
 * @brief Simulates one clock cycle of processing.
 *
 * Decrements the remaining time. If the request is finished,
 * marks the server as idle.
 */
void Webserver::incrementTime()
{
    if (busy)
    {
        --clockRemaining;
        if (clockRemaining <= 0)
        {
            busy = false;
        }
    }
}

/**
 * @brief Returns whether the server is currently processing a request.
 *
 * @return true if the server is busy; false otherwise.
 */
bool Webserver::isBusy()
{
    return busy;
}