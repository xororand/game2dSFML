#include "utils.h"

// ==================== ENCODING ====================

string utils::encoding::to_utf8(const wstring& str)
{
    static std::wstring_convert<codecvt_utf8<wchar_t>> u8;
    return u8.to_bytes(str);
}
wstring utils::encoding::to_wide(const string& str)
{
    int count = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
    wstring wstr(count, 0);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}

// ==================== HASHING ====================

string utils::hashing::sha256(string text) {
    SHA256 sha;
    sha.update(text);
    std::array<uint8_t, 32> digest = sha.digest();
    return SHA256::toString(digest);
}

// ==================== STRINGS ====================

string utils::strings::get_rand_string(int c_count) {
    srand(time(0));
    string text = "";
    for (int i = 0; i < c_count; i++) {
        text += (char)rand() % 256;
    }
    return text;
}

// ==================== COMPUTER ====================

string utils::computer::getCpu() {
    try
    {
        int CPUInfo[4] = { -1 };
        __cpuid(CPUInfo, 0x80000000);
        unsigned int nExIds = CPUInfo[0];

        char CPUBrandString[0x40] = { 0 };
        for (unsigned int i = 0x80000000; i <= nExIds; ++i)
        {
            __cpuid(CPUInfo, i);
            if (i == 0x80000002)
            {
                memcpy(CPUBrandString,
                    CPUInfo,
                    sizeof(CPUInfo));
            }
            else if (i == 0x80000003)
            {
                memcpy(CPUBrandString + 16,
                    CPUInfo,
                    sizeof(CPUInfo));
            }
            else if (i == 0x80000004)
            {
                memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
            }
        }

        return CPUBrandString;
    }
    catch (...) { return "NONE"; }
}
wstring utils::computer::getGpu() {
    DISPLAY_DEVICE dd = { sizeof(dd), 0 };
    BOOL f = EnumDisplayDevicesW(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
    return dd.DeviceString;
}
void utils::computer::getRAM(DWORD& max, DWORD& used) {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    max = memoryStatus.ullTotalPhys / 1024 / 1024;
    used = memoryStatus.dwMemoryLoad; // загруженность ОП
}
void utils::computer::getDesktopResolution(int& screen_weight, int& screen_height) {
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    screen_weight = desktop.right;
    screen_height = desktop.bottom;
}
