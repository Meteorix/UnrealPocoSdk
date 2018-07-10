#ifndef RPCSERVER_H
#define RPCSERVER_H

#include "iostream"
#include <string>
#include "Tcp/PassiveSocket.h"
#include "WinSock2.h"
#include "protocol.h"
#include "json.hpp"
#include <list>
#include <map>
#include <thread>
#include <functional>


using std::string;
using std::cout;
using std::endl;
using json = nlohmann::json;

#define MAX_PACKET 4096 


class RpcServer
{
public:
	RpcServer();
	~RpcServer();
	void start();
	void close();
	void client_task(CActiveSocket *pClient, Protocol proto);
	void client_task2(SOCKET *ClientSocket, Protocol proto);
	string handle_rpc_request(string request);
	void register_rpc_method(string method_name, std::function<json(json)> method_ptr);
private:
	bool running = false;
	CPassiveSocket m_socket;
	SOCKET ListenSocket = INVALID_SOCKET;
	Protocol proto = Protocol();
	std::list<std::thread*> client_thread_list = {};
	std::map<string, std::function<json(json)>> rpc_method_map = {};
};

#endif // RPCSERVER_H
