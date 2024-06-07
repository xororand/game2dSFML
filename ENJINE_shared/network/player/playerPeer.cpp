#include "playerPeer.h"

playerPeer::playerPeer() {}

void playerPeer::set_character_node(characterNode* node) { player_node = node;  }
void playerPeer::set_player_name(string name) {
	p_name = name;
}
void playerPeer::set_public_hash(string hash)	{ public_hash = hash;	}
void playerPeer::set_private_hash(string hash)	{ private_hash = hash;	}
void playerPeer::set_timestamp(int i)			{ timestamp = i;		}

characterNode* playerPeer::get_character_node()	{ return player_node;	}
string playerPeer::get_player_name()			{ return p_name;		}
string playerPeer::get_public_hash()			{ return public_hash;	}
string playerPeer::get_private_hash()			{ return private_hash;	}
int playerPeer::get_timestamp()					{ return timestamp;		}