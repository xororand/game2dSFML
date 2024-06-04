#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include "define.h"

#include "network/playerPeer.h"
#include "nodes/node.h"
#include "nodes/characterNode.h"
#include <iostream>
#include <string>
#include <thread>
#include <synchapi.h>

class server {
private:
	bool m_is_started = false;
	vector<Thread*> threads;

	TcpListener tcp_listener;

	vector<playerPeer*> players;
public:
	enum class threadtype {
		new_connections,
		process_connected
	};
	server();
	bool is_started();
	void accept_connections();
	void process_connected();
	void add_thread(threadtype type);
	void start();

};