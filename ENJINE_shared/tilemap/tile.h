#pragma once

#include "define.h"

class tile {
public:
	tile(int texture_id, v2f position, v2f size);

	void set_texture_id(int id);
	void set_pos(v2f position);	
	void set_tile_size(v2f size);
	void is_centered(bool val);

	int get_texture_id();
	v2f get_pos();
	v2f get_tile_size();
	bool is_centered();
private:
	bool m_is_centered = true;
	int m_texture_id;
	v2f m_position;
	v2f m_size;
};
