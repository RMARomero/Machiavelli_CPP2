#pragma once
#include "Socket.h"
#include <memory>
#include "Sync_queue.h"
#include "ClientCommand.h"
using std::unique_ptr;
class SocketManager
{
private:
	int m_Port;
	void getServerInformation();
	SocketManager();
	SocketManager(const SocketManager&);
	SocketManager& operator=(const SocketManager&);
public:
	Sync_queue<ClientCommand> queue;
	void start();
	static SocketManager& getInstance();
	virtual ~SocketManager();
};

