#pragma once

#include "define.h"

class Peer {
private:
	TcpSocket* tcp;
	UdpSocket* udp;
public:
	TcpSocket* get_tcp_sock();
	void set_tcp_socket(TcpSocket* sock);
	// ���������� False ���� ��� �������� ������ �������� ������
	bool send_data(Packet* p);
};