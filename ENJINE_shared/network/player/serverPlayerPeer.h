#pragma once

#include "playerPeer.h"

class serverPlayerPeer : public playerPeer {
public:
	bool create_player_node(string public_hash, string private_hash, v2f pos, bool is_main = false);
	bool send_chat_msg(string text);
};