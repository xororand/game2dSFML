#pragma once

// ======== »√–Œ¬€≈ ƒ≈‘¿…Õ€ ======== //

#define UI_FLAG_CLEAR ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration
#define FIXED_DELTA (1.0f / 60.0f)
#define STANDART_TILE_SIZE 64.0f, 64.0f
#define ONE 1.0f
#define MAX_VELOCITY 1.0f
#define ANTI_VELOCITY 0.99f

// ======== —≈–¬≈–ÕŒ- À»≈Õ“— »≈ ƒ≈‘¿…Õ€ ======== //

#include "network/netcommands.h"

#define VERSION_STAGE "DEV"
#define CLIENT_VERSION "0.1"
#define SERVER_VERSION "0.1"

#define DEFAULT_TCP_SERVER_PORT 7888
#define DEFAULT_UDP_SERVER_PORT 7999
#define CPU_THREADS_MAX_COUNT std::thread::hardware_concurrency()


#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

#include "utils/utils.h"

#include <deque>
#include <format>
#include <filesystem>

using namespace sf;
using namespace std;
using namespace std::filesystem;

typedef Vector2f v2f;
typedef Vector2u v2u;