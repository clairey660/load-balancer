#include <iostream>
#include "Request.h"
#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H
class RequestQueue
{
private:
    std::vector<Request> queue;
    int _size;

public:
    RequestQueue();
    void push_back(Request request);
    Request pop();
    bool isEmpty();
    int size();
};
#endif