#include "Peer.h"

TcpSocket* Peer::get_tcp_sock() { return tcp; }
IpAddress Peer::get_udp_sender_ip() { return udp_sender_ip; }
unsigned short Peer::get_remote_port() { return udp_remote_port;  }

bool Peer::send_data(Packet* p) {
	while (1) {
		Socket::Status status = tcp->send(*p);
		if (status == Socket::Done)
			break;
		if (status == Socket::Partial)
			continue;
		if (status == Socket::Error)
			delete p;
			return false;
	}

	delete p;
	return true;
}
void Peer::set_tcp_socket(TcpSocket* tcp_) {
	tcp = tcp_;
}
void Peer::set_udp_sender_ip(IpAddress ip) { udp_sender_ip = ip; }
void Peer::set_udp_remote_port(unsigned short port) { udp_remote_port = port; }
