#pragma once

#include "define.h"

#include "Peer.h"
#include "nodes/characterNode.h"

class playerPeer : public Peer {
private:
	characterNode* player_node;

	string p_name;

	string public_hash;
	string private_hash;

	int timestamp = 0.0f;
public:
	
	playerPeer();

	void set_character_node(characterNode* node);
	void set_player_name(string name);
	void set_public_hash(string hash);
	void set_private_hash(string hash);
	void set_timestamp(int i);

	characterNode* get_character_node();
	string get_player_name();
	string get_public_hash();
	string get_private_hash();
	int get_timestamp();
};