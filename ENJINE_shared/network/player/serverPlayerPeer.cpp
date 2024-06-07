#include "serverPlayerPeer.h"

bool serverPlayerPeer::create_player_node(string public_hash, string private_hash, v2f pos, bool is_main) {
	Packet* p = new Packet();

	string command = format(R"({{"c":{0},"public_hash":"{1}","private_hash":"{2}","pos":[{3},{4}],"scc":true}})",
		(int)command::CREATE_PLAYER,
		public_hash,
		private_hash,
		pos.x, pos.y
	);

	p->append(command.c_str(), command.size());

	return send_data(p);
}

bool serverPlayerPeer::send_chat_msg(string text) {
	Packet* p = new Packet();
	string command = format(R"({{"c":{0},"msg":"{1}"}})",
		(int)command::SEND_CHAT_MSG,
		text
	);

	p->append(command.c_str(), command.size());

	return send_data(p);
}