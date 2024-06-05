#include "Peer.h"

TcpSocket* Peer::get_tcp_sock() { return tcp; }
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