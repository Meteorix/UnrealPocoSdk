#include "rpcserver.h"
#include "CoreMinimal.h"


json Dump(json params);


RpcServer::RpcServer()
{
	//register_rpc_method("Dump", Dump);
}


void RpcServer::start()
{
	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		UE_LOG(LogTemp, Warning, TEXT("WSAStartup failed: %d\n"), iResult);
		return ;
	}

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, "5007", &hints, &result);
	if (iResult != 0) {
		UE_LOG(LogTemp, Warning, TEXT("getaddrinfo failed: %d\n"), iResult);
		WSACleanup();
		return ;
	}

	//SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		UE_LOG(LogTemp, Warning, TEXT("Error at socket(): %ld\n"), WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Start listening"));
	}

	running = true;

	while (true) {
		//printf("wait for connection...\n");
		UE_LOG(LogTemp, Warning, TEXT("============wait for connection==========="));

		SOCKET *ClientSocket = new SOCKET();
		*ClientSocket = INVALID_SOCKET;

		// Accept a client socket
		*ClientSocket = accept(ListenSocket, NULL, NULL);
		if (*ClientSocket == INVALID_SOCKET) {
			UE_LOG(LogTemp, Warning, TEXT("accept failed: %d\n"), WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Got one ClientSocket"));
		std::thread *client_thread = new std::thread(&RpcServer::client_task2, this, ClientSocket, proto);
		client_thread_list.push_back(client_thread);
	}



	/*
	if (!m_socket.Initialize()) {
		UE_LOG(LogTemp, Warning, TEXT("============socket init error==========="));
		int err_no = m_socket.GetSocketError();
		UE_LOG(LogTemp, Warning, TEXT("%d"), err_no);
		return;
	}

	if (!m_socket.Listen("0.0.0.0", 5006)) {
		UE_LOG(LogTemp, Warning, TEXT("============socket listen error==========="));
		return;
	}
	
	running = true;

	while (true) {
		//printf("wait for connection...\n");
		UE_LOG(LogTemp, Warning, TEXT("============wait for connection==========="));
		CActiveSocket *pClient = NULL;
		if ((pClient = m_socket.Accept()) != NULL)
		{
			//printf("accepted one connection\n");
			UE_LOG(LogTemp, Warning, TEXT("============accepted one connection==========="));
			std::thread *client_thread = new std::thread(&RpcServer::client_task, this, pClient, proto);
			client_thread_list.push_back(client_thread);
		}
	}

	m_socket.Close();
	*/
}


void RpcServer::close()
{
	if (!running) {
		return;
	}
	closesocket(ListenSocket);
	WSACleanup();
	//m_socket.Close();

	for (auto item : client_thread_list) {
		delete item;
	}

}


RpcServer::~RpcServer()
{
	close();
}



void RpcServer::client_task2(SOCKET *ClientSocket, Protocol proto)
{
#define DEFAULT_BUFLEN 512

	char recvbuf[DEFAULT_BUFLEN];
	int iRecvResult, iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;

	UE_LOG(LogTemp, Warning, TEXT("Start to handle ClientSocket"));

	// Receive until the peer shuts down the connection
	while (true){
		iRecvResult = recv(*ClientSocket, recvbuf, recvbuflen, 0);
		if (iRecvResult > 0) {
			UE_LOG(LogTemp, Warning, TEXT("Bytes received: %d\n"), iRecvResult);
			
			proto.parse(string(recvbuf, iRecvResult));

			while (proto.messageCount() > 0) {
				string request = proto.nextMessage();
				string response = handle_rpc_request(request);
				string response_proto = proto.pack(response);
				cout << response_proto << endl;
				const char* response_trunk = response_proto.c_str();
				iSendResult = send(*ClientSocket, response_trunk, response_proto.size(), 0);
				//iSendResult = send(*ClientSocket, recvbuf, iRecvResult, 0);
				if (iSendResult == SOCKET_ERROR) {
					UE_LOG(LogTemp, Warning, TEXT("send failed: %d\n"), WSAGetLastError());
					closesocket(*ClientSocket);
					WSACleanup();
					break;
				}
				UE_LOG(LogTemp, Warning, TEXT("Bytes sent: %d\n"), iSendResult);
			}
		}
		else if (iRecvResult == 0) {
			UE_LOG(LogTemp, Warning, TEXT("ClientSocket connection closing"));
			break;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("recv failed: %d\n"), WSAGetLastError());
			closesocket(*ClientSocket);
			WSACleanup();
			break;
		}
	}
}


void RpcServer::client_task(CActiveSocket *pClient, Protocol proto)
{

	/*
	while (pClient->Receive(MAX_PACKET) > 0)
	{
		char* trunk = (char *)pClient->GetData();
		int trunk_size = pClient->GetBytesReceived();
		printf("got trunk size: %d\n", trunk_size);

		proto.parse(string(trunk, trunk_size));

		while (proto.messageCount() > 0)
		{
			string request = proto.nextMessage();
			string response = handle_rpc_request(request);
			string response_proto = proto.pack(response);
			cout << response_proto << endl;
			const char* response_trunk = response_proto.c_str();
			pClient->Send((const uint8*)(response_trunk), response_proto.size());
		}
	}
	pClient->Close();
	delete pClient;
	*/
}


string RpcServer::handle_rpc_request(string request)
{
	// parse json-rpc 2.0
	auto j = json::parse(request);
	int rpc_id = j["id"];
	string rpc_method = j["method"];
	json rpc_params = j["params"];
	cout << rpc_id << ":" << rpc_method << endl;
	if (rpc_params.is_array())
	{
		// iterate the array
		for (json::iterator it = rpc_params.begin(); it != rpc_params.end(); ++it) {
			cout << *it << endl;
		}
	}
	else if (rpc_params.is_object())
	{
		std::cerr << "keyword params is not allowed" << endl;
		return NULL;
	}
	json res;
	bool err = false;
	string err_message;
	// dispatch rpc method

	auto search = rpc_method_map.find(rpc_method);
	if (search != rpc_method_map.end())
	{
		std::function<json(json)> method_ptr = rpc_method_map[rpc_method];
		try
		{
			res = method_ptr(rpc_params);
		}
		catch (const std::exception& e)
		{
			err = true;
			err_message = string(e.what());
		}
	}
	else 
	{
		// TODO: error code
		err = true;
		err_message = string("Method not found");
	}

	// form response
	json response = {
		{ "jsonrpc", "2.0" },
		{ "id", rpc_id },
	};
	if (err) {
		json err_object = {
			{ "code", -32603 },
			{ "message", err_message },
		};
		response["error"] = err_object;
	}
	else {
		response["result"] = res;
	}
	string response_str = response.dump();
	return response_str;
}


void RpcServer::register_rpc_method(string method_name, std::function<json(json)> method_ptr)
{
	rpc_method_map[method_name] = method_ptr;
}


json Dump(json params)
{
	bool flag = params[0];
	json result = {
		{ "name", "root" },
		{ "payload",{
			{ "name", "root" },
			{ "size",{ 0, 0 } },
			{ "pos",{ 0, 0 } },
			{ "zOrders",{ { "local", 0 },{ "global", 0 } } },
			{ "anchorPoint",{ 0.5, 0.5 } },
			{ "visible", true },
		} },
		{ "children", json::array() }
	};
	return result;
}
