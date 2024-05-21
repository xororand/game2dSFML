#include "main.h"
#include <chrono>
#include "intrin.h"

class gameloops {
public:
	gameloops();
	void render(float deltatime);
	void setMainWindow(RenderWindow* window);
	void setImguiIO(ImGuiIO* io);
	void setStandartFont(ImFont* font);
	ImFont* getStandartFont();
	int getScreenWidth();
	int getScreenHeight();
	ImGuiIO* io;
private:
	RenderWindow* window;
	
	Clock clock_start;
	ImFont* standart_font;
	string to_utf8(const wstring& str);
	string getCpu();
	wstring getGpu();
	void getRAM(DWORD& max, DWORD& used);
	void getDesktopResolution();
	int screen_weight, screen_height;
	int fps_point = 0;
	float fps_samples[500];
};