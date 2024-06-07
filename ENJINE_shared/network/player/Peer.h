#pragma once

#include "define.h"

class Peer {
private:
	IpAddress		udp_sender_ip;
	unsigned short	udp_remote_port;

	TcpSocket* tcp;
public:
	TcpSocket* get_tcp_sock();
	IpAddress get_udp_sender_ip();
	unsigned short get_remote_port();

	void set_tcp_socket(TcpSocket* sock);
	void set_udp_sender_ip(IpAddress ip);
	void set_udp_remote_port(unsigned short port);

	// Возвращает False если при отправке пакета возникла ошибка
	bool send_data(Packet* p);
};