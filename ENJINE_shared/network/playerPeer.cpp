#include "playerPeer.h"

playerPeer::playerPeer() {}

void playerPeer::set_tcp_socket(TcpSocket* tcp_) {
	tcp = tcp_;
}
void playerPeer::set_public_hash(string hash) { public_hash = hash; }
void playerPeer::set_private_hash(string hash) { private_hash = hash; }
void playerPeer::set_timestamp(int i) { timestamp = i; }

string playerPeer::get_public_hash() { return public_hash; }
string playerPeer::get_private_hash() { return private_hash; }
int playerPeer::get_timestamp() { return timestamp; }