#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include "define.h"

#include "network/player/serverPlayerPeer.h"
#include "nodes/node.h"
#include "nodes/characterNode.h"
#include <iostream>
#include <string>
#include <thread>
#include <synchapi.h>

class server {
private:
	bool m_is_started = false;
	int tps = 30;

	static inline int thread_count = 0;
	vector<Thread*> threads;

	TcpListener tcp_listener;

	deque<serverPlayerPeer*> peers;
public:
	enum class threadtype {
		new_connections,
		process_connected
	};
	
	server();
	
	void sync_clients();

	void tcp_new_connections();
	void process_connected();

	void add_thread(threadtype type);
	void start();
	bool is_started();

	void send_msg_to_all(string text);
};