#include "..\client.h"
#include "utils/utils.h"
#include "utils/vecmath.h"
#include "tilemap/tile.h"
#include "tilemap/tilemap.h"
#include "nodes/node.h"
#include "nodes/characterNode.h"
#include "network/player/playerPeer.h"

class gameloops {
public:
	gameloops();
	void render(float& deltatime);
	void network();
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
	bool is_console_debug = true;
	enum class SCENE {
		main_menu,
		main_menu_settings,
		connection_process_game_server,
		game_world,
	};

	SCENE current_scene = SCENE::main_menu;
	struct m_settings {
		static inline int space_points_count = 4000;
		static inline int space_comets_count = 4000;
		static inline bool vsync = true;
		static inline VertexArray space_points;
		static inline VertexArray space_comets;
		static inline bool is_debug = false;
	};

	IpAddress server_ip = "localhost";

	Clock connect_timer;
	//Clock udp_timer;
	TcpSocket tcp;
	UdpSocket udp;
	Socket::Status tcp_status = Socket::Disconnected;
	Socket::Status udp_status = Socket::Disconnected;

	static struct m_network {
		static inline float udp_max_time_to_connect = 10.0f;
		static inline float connect_every_sec = 5.0f;
		static inline int tcp_failed_max_count = 5;
		static inline int tcp_failed_count = 0;

	};

	struct debug_stats {
		static inline int fps_point = 0;
		static inline float fps_samples[500];
	};
	
	vecmath vmath;
	RenderWindow* window;
	Clock clock_space;
	ImFont* standart_font;
	Vector2f view_center = Vector2f(0.0f, 0.0f);
	Vector2f toview_center = Vector2f(0.0f, 0.0f);
	int screen_weight, screen_height;

	playerPeer* m_peer;
	deque<playerPeer*> peers;

	struct render_system {
		static inline Texture atlas1;
		static inline deque<tile> tiles;
		static inline tilemap _tilemap = tilemap(&atlas1, Vector2u(64, 64));;
	};

	void write2draw_all_characters();
	void clean_all_tiles();
	
	void drawMainMenu(float& deltatime);
	void drawMainSettings(float& deltatime);
	void drawConnectionProcessGameServer(float& deltatime);
	void drawGameWorld(float& deltatime);

	void drawDebug();
	void drawRandomComets(float& deltatime);
	void drawBackgroundSpaceCircleEffect(float& deltatime);
	void drawBackgroundSpaceFlyEffect(float& deltatime);
	void drawCredits();

	void create_player(string public_hash, string private_hash, v2f pos, bool is_main);
	void connect_to_server();
	bool check_connection();
	void receive_tcp_packets();
	void receive_udp_packets();
	json receive_udp(IpAddress& sender_ip, unsigned short& port);
	void udp_send(string data);
	
};