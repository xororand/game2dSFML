#pragma once

// ======== хцпнбше детюимш ======== //

#define STANDART_TILE_SIZE 64.0f, 64.0f
#define ONE 1.0f
#define MAX_VELOCITY 1.0f
#define ANTI_VELOCITY 0.99f

// ======== яепбепмн-йкхемряйхе детюимш ======== //

#define VERSION_STAGE "DEV"
#define CLIENT_VERSION "0.1"
#define SERVER_VERSION "0.1"

#define DEFAULT_TCP_SERVER_PORT 7878
#define DEFAULT_UDP_SERVER_PORT 7879

#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

#include <filesystem>

using namespace sf;
using namespace std;
using namespace std::filesystem;

typedef Vector2f v2f;
typedef Vector2u v2u;