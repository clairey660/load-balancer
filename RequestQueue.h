#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

/**
 * @class RequestQueue
 * @brief A wrapper class for managing a queue of Requests.
 */
class RequestQueue
{
private:
    std::queue<Request> queue;

public:
    /**
     * @brief Constructs an empty RequestQueue.
     */
    RequestQueue();

    /**
     * @brief Adds a Request to the end of the queue.
     * @param request The Request to enqueue.
     */
    void push_back(Request request);

    /**
     * @brief Removes and returns the front Request in the queue.
     * @return The front Request.
     */
    Request pop();

    /**
     * @brief Checks if the queue is empty.
     * @return true if empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Returns the number of Requests in the queue.
     * @return The size of the queue.
     */
    int size() const;
};
#endif // REQUESTQUEUE_H