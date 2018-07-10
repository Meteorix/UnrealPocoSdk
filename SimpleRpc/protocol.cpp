#include "protocol.h"


#define HEADER_SIZE 4


Protocol::Protocol()
{
}


void Protocol::parse(string data)
{
    m_buf.append(data);

    while (m_buf.length() > HEADER_SIZE)
    {
        string header_data = m_buf.substr(0, HEADER_SIZE);
        int32_t body_size = (int32_t)*header_data.data();

        printf("%d\n", body_size);
        
        if (m_buf.length() >= (body_size + HEADER_SIZE))
        {
            string body_data = m_buf.substr(HEADER_SIZE, body_size);
            m_buf = m_buf.substr(HEADER_SIZE + body_size, string::npos);
            m_messages.push_back(body_data);
        }
        else
        {
            break;
        }
    }
        
}

string Protocol::pack(string message)
{
    string data;
    int32_t body_size = message.length();
    char bytes[4];
    bytes[3] = (body_size >> 24) & 0xFF;
    bytes[2] = (body_size >> 16) & 0xFF;
    bytes[1] = (body_size >> 8) & 0xFF;
    bytes[0] = body_size & 0xFF;
    data.append(string(bytes, 4));
    data.append(message);
    return data;
}


int Protocol::messageCount()
{
    return m_messages.size();
}


string Protocol::nextMessage()
{
    string message = m_messages.front();
    m_messages.pop_front();
    return message;
}
