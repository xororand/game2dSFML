#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include "define.h"

#include "nodes/node.h"
#include "nodes/character_node.h"
#include <iostream>
#include <string>

class server {
public:
	server();
	bool is_started();
	void accept_connections();
private:
	bool m_is_started = false;
	v2f global_pos;
	TcpListener tcp_listener;
	vector<TcpSocket> clients;
	vector<character_node> m_characters;
};