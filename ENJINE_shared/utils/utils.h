#pragma once

#include "json.hpp"
#include "sha256.h"

#include "Windows.h"
#include <string>
#include "intrin.h"
#include <codecvt>

using namespace std;

class utils {
public:
	struct encoding {
        static string to_utf8(const wstring& str);
        static wstring to_wide(const string& str);
	};
	
    struct hashing {
        static string sha256(string text);
    };

    struct strings {
        static string get_rand_string(int c_count);
    };

	struct computer {
        static string getCpu();
        static wstring getGpu();
        static void getRAM(DWORD& max, DWORD& used);
        static void getDesktopResolution(int& screen_weight, int& screen_height);
	};

};