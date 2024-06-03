#include "character_node.h"

character_node::character_node(v2f position) {
	m_tile = new tile(0, get_pos(), v2f(STANDART_TILE_SIZE));
	m_velocity = new v2f(0.0, 0.0);
	set_pos(position);
}
void character_node::set_pos(v2f pos) {
	node::set_pos(pos);
	m_tile->set_pos(pos);
}
tile* character_node::get_tile() {
	return m_tile;
}
void character_node::is_main(bool val) {
	m_is_main = val;
}
bool character_node::is_main() {
	return m_is_main;
}
void character_node::is_in_space(bool val) {
	m_is_in_space = val;
}
bool character_node::is_in_space() {
	return m_is_in_space;
}
v2f* character_node::get_vel() {
	return m_velocity;
}