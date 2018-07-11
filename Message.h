#pragma once
#include <string>
#include "SimpleRpc/json.hpp"
#include <mutex>
#include <condition_variable>

using json = nlohmann::json;


class Message
{
public:
	Message(std::string name, json params);
	Message(const Message &);
	~Message();

	std::mutex mutex;
	std::unique_lock<std::mutex> lock{ mutex };
	std::condition_variable cond;

	std::string m_name;
	json m_params;
	json m_result;
};
