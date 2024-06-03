#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define UI_FLAG_CLEAR ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration

#include "Windows.h"
#include <filesystem>
#include <iostream>
#include <locale>
#include <math.h>

#include "SFML/Graphics.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

using namespace sf;
using namespace std;
using namespace std::filesystem;