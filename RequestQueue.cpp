#include "RequestQueue.h"

RequestQueue::RequestQueue()
{
}

void RequestQueue::push_back(Request request)
{
    ++_size;
}

Request RequestQueue::pop()
{
    --_size;
}

bool RequestQueue::isEmpty()
{
    return _size == 0;
}

int RequestQueue::size()
{
    return _size;
}