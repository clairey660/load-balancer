#ifndef WEBSERVER_H
#define WEBSERVER_H
class Webserver
{
public:
    Webserver();
    void createRequest(Request &r);
    bool isBusy();
    void incrementTime();
}
#endif