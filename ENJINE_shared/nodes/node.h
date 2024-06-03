#pragma once

#include "define.h"

class node {
public:
	void set_pos(v2f pos);
	v2f get_pos();

private:
	v2f m_position;
};