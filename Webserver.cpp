#include "Webserver.h"

Webserver::Webserver() : busy(false), clockRemaining(0)
{
}
void Webserver::createRequest(Request &r)
{
    currentRequest = r;
    clockRemaining = r.time_required;
    busy = true;
}
bool Webserver::isBusy()
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

void Webserver::incrementTime()
{
    return busy;
}
