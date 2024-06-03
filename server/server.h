#include "define.h"

#include "Windows.h"
#include <iostream>

#include "nodes/node.h"
#include "nodes/character_node.h"

using namespace std;

class server {
public:
	server();
	bool is_started();
	void accept_connections();
private:
	bool m_is_started = false;
	
	TcpListener tcp_listener;
	vector<TcpSocket> clients;
	vector<character_node> m_characters;
};