#pragma once

#include "node.h"
#include "tilemap/tile.h"

class characterNode : public node {
public:
	characterNode(v2f position = v2f(0.0f, 0.0f));
	tile* get_tile();
	void set_pos(v2f pos);
	void is_main(bool val);
	bool is_main();
	void is_in_space(bool val);
	bool is_in_space();
	v2f* get_vel();
private:
	tile* m_tile;
	bool m_is_main = false;
	bool m_is_in_space;
	v2f* m_velocity;
};