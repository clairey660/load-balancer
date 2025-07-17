#include "RequestQueue.h"

RequestQueue::RequestQueue()
{
}

void RequestQueue::push_back(Request request)
{
    queue.push(request);
}

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

bool RequestQueue::isEmpty()
{
    return queue.empty();
}

int RequestQueue::size()
{
    return static_cast<int>(queue.size());
}