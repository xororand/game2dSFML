#include "game.h"

VertexArray mypoints(Points, 4000);

string gameloops::to_utf8(const wstring& str)
{
    static std::wstring_convert<codecvt_utf8<wchar_t>> u8;
    return u8.to_bytes(str);
}
string gameloops::getCpu() {
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
wstring gameloops::getGpu() {
    DISPLAY_DEVICE dd = { sizeof(dd), 0 };
    BOOL f = EnumDisplayDevicesW(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
    return dd.DeviceString;
}
void gameloops::getRAM(DWORD &max, DWORD &used) {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    max = memoryStatus.ullTotalPhys / 1024 / 1024;
    used = memoryStatus.dwMemoryLoad; // загруженность ОП
}
void gameloops::getDesktopResolution() {
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    screen_weight = desktop.right;
    screen_height = desktop.bottom;
}

void gameloops::setMainWindow(RenderWindow* window_) {
    window = window_;
}
void gameloops::setImguiIO(ImGuiIO* io_) {
    io = io_;
}
void gameloops::setStandartFont(ImFont* font) {
    standart_font = font;
}
int gameloops::getScreenWidth() {
    return screen_weight;
}

int gameloops::getScreenHeight() {
    return screen_height;
}
ImFont* gameloops::getStandartFont() {
    return standart_font;
}
gameloops::gameloops() {
    srand(time(NULL));
    getDesktopResolution();

    for (int i = 0; i < 4000; i++) {
        mypoints[i].position = Vector2f(rand() % screen_weight * 2, rand() % screen_height * 2);
    }
    for (int i = 0; i < 100; i++){
        fps_samples[i] = 0.0f;
    }

}

void gameloops::render(float deltatime) {
    ImGui::PushFont(getStandartFont());

    ImGui::Begin(u8"Дебаг ИНФО");

    static float f = 0.0f;
    ImGui::SliderFloat("MAX FPS", &f, 0.0f, 144.0f);
    float ms = 1000.0f / io->Framerate;
    float fps = io->Framerate;
    ImGui::Text("CPU:\t%s", getCpu().c_str());
    ImGui::Text("GPU:\t%s", to_utf8(getGpu()).c_str());
    DWORD max, used;
    getRAM(max, used);
    ImGui::Text(u8"RAM:\ta%i MB / %i%s загружено", max, used, "%");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", ms, fps);
    window->setFramerateLimit((int)f);
    if (fps > 144.0)
        fps = 144.0;

    if (fps_point == 500)
        fps_point = 0;

    fps_samples[fps_point] = fps;
    fps_point++;
    
    ImGui::PlotLines("FPS", fps_samples, 500, 0, NULL, 0.0, 144.0, ImVec2(0.0, 70.0));

    ImGui::End();
    ImGui::PopFont();

    for (int i = 0; i < 4000; i++) {
        float scale_delta_y = sinf(i * 0.2f + ImGui::GetTime() * 0.25f);
        float scale_delta_x = cosf(i * 0.2f + ImGui::GetTime() * 0.25f);

        float rad_delta = i / 4000;

        double angle = (.0015 * (rad_delta - 1.0 + 0.5)) * (1.0 / fps) * 100.0f;

        Vector2f to_center = (Vector2f(screen_weight, screen_height) - mypoints[i].position);
        to_center.x += (20.0f * scale_delta_x);
        to_center.y += (20.0f * scale_delta_y);


        mypoints[i].position = Vector2f(to_center.x * cos(angle) - to_center.y * sin(angle),
                                        to_center.x * sin(angle) + to_center.y * cos(angle));

        
    }
    window->draw(mypoints);
    /*ImGui::Text("Hello, world!");
    static float f = 0.0f;
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS) %.3f", 1000.0f / io->Framerate, io->Framerate, f);
    float samples[100];
    for (int n = 0; n < 100; n++)
        samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
    ImGui::PlotLines("Samples", samples, 100);
    ImGui::PopFont();*/
    //Text fps_text;
    //fps_text.setFont(standart_font);
    //fps_text.setCharacterSize(14);
    //fps_text.setFillColor(sf::Color::White);
    //fps_text.setStyle(sf::Text::Bold);
    //fps_text.setPosition(Vector2f(10.0, 10.0));
    //char strfps[10];

    //sprintf(strfps, "Application average %.3f ms/frame\n%.1f FPS", 1000.0f / io.Framerate, io.Framerate);

    //fps_text.setString(strfps);

    //window->draw(fps_text);

}
