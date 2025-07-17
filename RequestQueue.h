#include <iostream>
#include <queue>
#include "Request.h"
#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H
class RequestQueue
{
private:
    std::queue<Request> queue;

public:
    RequestQueue();
    void push_back(Request request);
    Request pop();
    bool isEmpty();
    int size();
};
#endif