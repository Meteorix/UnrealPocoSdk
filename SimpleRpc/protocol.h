#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "iostream"
#include <string>
#include <list>
//#include <dlfcn.h>

using std::string;
using std::list;
using std::cout;
using std::endl;


class Protocol
{
public:
    Protocol();
    void parse(std::string data);
    int messageCount();
    std::string nextMessage();
    std::string pack(std::string message);
private:
    string m_buf;
    list<string> m_messages;
};

#endif // PROTOCOL_H
