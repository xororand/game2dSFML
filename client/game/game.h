#include "..\client.h"


#include "utils/utils.h"
#include "utils/vecmath.h"
#include "tilemap/tile.h"
#include "tilemap/tilemap.h"
#include "nodes/node.h"
#include "nodes/character_node.h"

class gameloops {
public:
	gameloops();
	void render(float& deltatime);
	void keyboard(float& deltatime);
	void setMainWindow(RenderWindow* window);
	void setImguiIO(ImGuiIO* io);
	void setStandartFont(ImFont* font);
	ImFont* getStandartFont();
	int getScreenWidth();
	void setScreenWidth(float w);
	int getScreenHeight();
	void setScreenHeight(float h);
	ImGuiIO* io;
	
private:
	enum class UI {
		main_menu,
		main_settings,
		game_server
	};

	struct m_settings {
		static inline int space_points_count = 4000;
		static inline int space_comets_count = 4000;
		static inline bool vsync = true;
		static inline VertexArray space_points;
		static inline VertexArray space_comets;
		static inline bool is_debug = false;
	};
	struct debug_stats {
		static inline int fps_point = 0;
		static inline float fps_samples[500];
	};

	UI current_ui = UI::game_server;
	vecmath vmath;
	RenderWindow* window;
	Clock clock_space;
	ImFont* standart_font;
	Vector2f view_center = Vector2f(0.0f, 0.0f);
	Vector2f toview_center = Vector2f(0.0f, 0.0f);
	int screen_weight, screen_height;

	character_node* main_player;
	vector<character_node*> characters;


	struct render_system {
		static inline Texture atlas1;
		static inline vector<tile> tiles;
		static inline tilemap _tilemap = tilemap(&atlas1, Vector2u(64, 64));;
	};

	void write2draw_all_characters();
	void clean_all_tiles();

	void drawMenu(float& deltatime);

	void drawDebug();
	void drawMainMenu(float& deltatime);
	void drawMainSettings(float& deltatime);
	void drawGameServer(float& deltatime);
	void drawRandomComets(float& deltatime);
	void drawBackgroundSpace(float& deltatime);
	void drawCredits();

	
};