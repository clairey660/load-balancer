#include "RequestQueue.h"

/**
 * @brief Constructor initializes an empty queue.
 */
RequestQueue::RequestQueue()
{
}

/**
 * @brief Adds a Request to the back of the queue.
 * @param request The request to be added.
 */
void RequestQueue::push_back(Request request)
{
    queue.push(request);
}

/**
 * @brief Removes and returns the front Request in the queue.
 * @return The front Request.
 */
Request RequestQueue::pop()
{
    if (queue.empty())
    {
        throw std::runtime_error("Attempted to pop from an empty RequestQueue.");
    }

    Request front = queue.front();
    queue.pop();
    return front;
}

/**
 * @brief Checks whether the queue is empty.
 * @return true if the queue is empty, false otherwise.
 */
bool RequestQueue::isEmpty()
{
    return queue.empty();
}

/**
 * @brief Returns the current number of Requests in the queue.
 * @return The number of requests.
 */
int RequestQueue::size() const
{
    return static_cast<int>(queue.size());
}