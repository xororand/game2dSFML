#include "tile.h"

tile::tile(int texture_id, v2f position, v2f size) {
	m_texture_id = texture_id;
	m_position = position;
	m_size = size;
}

void tile::set_texture_id(int id) {
	m_texture_id = id;
}
void tile::set_pos(v2f position) {
	m_position = position;
}
void tile::set_tile_size(v2f size) {
	m_size = size;
}
void tile::is_centered(bool val) {
	m_is_centered = val;
}

int tile::get_texture_id() {
	return m_texture_id;
}
v2f tile::get_pos() {
	return v2f(m_position.x - (m_size.x/2), m_position.y - (m_size.y/2));
}
v2f tile::get_tile_size() {
	return m_size;
}
bool tile::is_centered() {
	return m_is_centered;
}