#pragma once

#include "define.h"

#include "nodes/characterNode.h"

class playerPeer {
public:
	playerPeer();
	void set_tcp_socket(TcpSocket* tcp);
	void set_public_hash(string hash);
	void set_private_hash(string hash);
	void set_timestamp(int i);

	string get_public_hash();
	string get_private_hash();
	int get_timestamp();
private:
	characterNode player_node;
	
	TcpSocket* tcp;
	UdpSocket* udp;

	string public_hash;
	string private_hash;

	int timestamp = 0.0f;
};