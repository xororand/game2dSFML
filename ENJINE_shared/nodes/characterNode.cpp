#include "characterNode.h"

characterNode::characterNode(v2f position) {
	m_tile = new tile(0, get_pos(), v2f(STANDART_TILE_SIZE));
	m_velocity = new v2f(0.0, 0.0);
	wasd = new BYTE[3];

	set_pos(position);
}

void characterNode::is_main(bool val) {
	m_is_main = val;
}
bool characterNode::is_main() {
	return m_is_main;
}
void characterNode::is_in_space(bool val) {
	m_is_in_space = val;
}
bool characterNode::is_in_space() {
	return m_is_in_space;
}

void characterNode::set_pos(v2f pos) {
	node::set_pos(pos);
	m_tile->set_pos(pos);
}
void characterNode::set_wasd(BYTE* bytes)	{ wasd = bytes;	} // будет ли утечка посмотреть

tile* characterNode::get_tile()				{ return m_tile; }
v2f* characterNode::get_vel()				{ return m_velocity; }
BYTE* characterNode::get_wasd()				{ return wasd; }