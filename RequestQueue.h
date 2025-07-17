#include <iostream>
#include "Request.h"
#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H
class RequestQueue
{
private:
    std::vector<Request> queue;

public:
    RequestQueue();
};
#endif