#pragma once
#include "Socket.h"
#include <memory>
#include "Sync_queue.h"
#include "ClientCommand.h"

using std::unique_ptr;

class SocketManager
{
public:
	Sync_queue<ClientCommand> queue;
	void start();
	static SocketManager& getInstance();
	virtual ~SocketManager(){}
private:
	int m_iPort;
	void getServerInformation();
	SocketManager(){}
	SocketManager(const SocketManager&);
	SocketManager& operator=(const SocketManager&);
};

