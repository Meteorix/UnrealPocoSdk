#include "Message.h"

Message::Message(std::string name, json params)
{
	m_name = name;
	m_params = params;
}

Message::Message(const Message &)
{
}

Message::~Message()
{
}
