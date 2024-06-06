#include "game.h"

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
void gameloops::setScreenWidth(float w) {
    screen_weight = w;
}
int gameloops::getScreenHeight() {
    return screen_height;
}
void gameloops::setScreenHeight(float h) {
    screen_height = h;
}

void gameloops::write2draw_all_characters() {
    for (auto c : peers) {
        characterNode* cd = c->get_character_node();
        if (cd->is_main()) {
            sf::View view = window->getDefaultView();
            view.setCenter(cd->get_pos());

            window->setView(view);
        }
        // запись на отрисовку персонажа
        render_system::tiles.push_back(*cd->get_tile());
    }
}
void gameloops::clean_all_tiles() {
    render_system::tiles.clear();
    render_system::_tilemap.clean();
}

ImFont* gameloops::getStandartFont() {
    return standart_font;
}

gameloops::gameloops() {
    srand(time(NULL));
    utils::computer::getDesktopResolution(screen_weight, screen_height);

    render_system::atlas1.loadFromFile(current_path().string() + "\\data\\atlases\\first_altlas.png");

    render_system::_tilemap = tilemap(&render_system::atlas1, Vector2u(64, 64));

    // запись главного персонажа
    //main_player = new playerPeer(v2f(0.0, 0.0));
    //main_player->is_main(true);
    //main_player->set_pos(v2f(screen_weight / 2.0, screen_height / 2.0));
    //main_player->get_tile()->set_texture_id(1);

    //characterNode* player = new characterNode(v2f(0.0, 0.0));
    //player->set_pos(v2f(screen_weight / 2.0, screen_height / 2.0));
    //player->get_tile()->set_texture_id(1);

    //characters.push_back(main_player);
    //characters.push_back(player);


    m_settings::space_points = VertexArray(Points, m_settings::space_points_count);
    toview_center = Vector2f(screen_weight / 2, screen_height / 2);
    view_center = toview_center;

    for (int i = 0; i < m_settings::space_points_count; i++) {
        m_settings::space_points[i].position = Vector2f(rand() % screen_weight, rand() % screen_height);
    }

    for (int i = 0; i < 100; i++) {
        debug_stats::fps_samples[i] = 0.0f;
    }
}

void gameloops::drawMainMenu(float& deltatime) {
    drawBackgroundSpaceCircleEffect(deltatime);

    ImGui::PushFont(getStandartFont());

    ImGui::SetNextWindowSize(ImVec2(screen_weight / 3.84f, screen_height / 2.16f));
    ImGui::SetNextWindowPos(ImVec2(screen_weight / 2 - (screen_weight / 3.84f) / 2, screen_height / 2 - (screen_height / 2.16f) / 5));
    ImGui::Begin("mMain", NULL, UI_FLAG_CLEAR);//s

    ImGui::SetCursorPosX(screen_weight / 3.84f / 2 - 125);
    if (ImGui::Button(utils::encoding::to_utf8(L"Вход").c_str(), ImVec2(250, 50))) {
        current_scene = SCENE::connection_process_game_server;
    }
    ImGui::SetCursorPosX(screen_weight / 3.84f / 2 - 125);
    if (ImGui::Button(utils::encoding::to_utf8(L"Настройки").c_str(), ImVec2(250, 50))) {
        current_scene = SCENE::main_menu_settings;
    }
    ImGui::SetCursorPosX(screen_weight / 3.84f / 2 - 125);
    if (ImGui::Button(utils::encoding::to_utf8(L"Выход").c_str(), ImVec2(250, 50))) {
        exit(0);
    }

    ImGui::End();
    ImGui::PopFont();
    
}
void gameloops::drawMainSettings(float& deltatime) {
    drawBackgroundSpaceCircleEffect(deltatime);

    ImGui::PushFont(getStandartFont());

    ImGui::SetNextWindowSize(ImVec2(screen_weight / 3.84f, screen_height / 2.16f));
    ImGui::SetNextWindowPos(ImVec2(screen_weight / 2 - (screen_weight / 3.84f) / 2, screen_height / 2 - (screen_height / 2.16f) / 2));
    ImGui::Begin("settings", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

    ImGui::SetCursorPosX(screen_weight / 3.84f / 2 - (ImGui::CalcTextSize(utils::encoding::to_utf8(L"Настройки").c_str()).x) / 2);
    ImGui::Text(utils::encoding::to_utf8(L"Настройки").c_str());
    ImGui::Separator();

    ImGui::SetCursorPos(ImVec2(screen_weight / 3.84f - 108, screen_height / 2.16f - 40));
    if (ImGui::Button(utils::encoding::to_utf8(L"Назад").c_str(), ImVec2(100, 30))) {
        current_scene = SCENE::main_menu;
    }

    ImGui::End();
    ImGui::PopFont();
}
void gameloops::drawConnectionProcessGameServer(float& deltatime) {
    drawBackgroundSpaceFlyEffect(deltatime);

    wstring connect_text = L"ИДЕТ ПОДКЛЮЧЕНИЕ";

    if(m_network::failed_count > 0)
        connect_text += format(L" ({}) ", m_network::failed_count);

    float text_size = ImGui::CalcTextSize(utils::encoding::to_utf8(connect_text).c_str()).x / 2;
    float coef_point = clamp(abs(cosf(ImGui::GetTime())), 0.0f, 1.0f);

    if (coef_point >= 0.7 && coef_point <= 1.0) {
        connect_text += L"...";
    }
    else if (coef_point > 0.3 && coef_point < 0.7) {
        connect_text += L"..";
    }
    else if (coef_point >= 0.0 && coef_point <= 0.3) {
        connect_text += L".";
    }

    ImGui::Begin("connection_progress", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(screen_weight / 2 - text_size, screen_height / 2));
    ImGui::Text(utils::encoding::to_utf8(connect_text).c_str());
    ImGui::End();

}
void gameloops::drawGameWorld(float& deltatime) {
    drawRandomComets(deltatime);

    // пишем что отрисовать
    write2draw_all_characters();

    // записываем массив в класс для отрисовки
    render_system::_tilemap.update(render_system::tiles);
    
    // отрисовка тайлов
    window->draw(render_system::_tilemap);

    // очистка того что надо было отрисовать
    clean_all_tiles();

}

void gameloops::drawDebug() {
    ImGui::PushFont(getStandartFont());

    ImGui::Begin(utils::encoding::to_utf8(L"Дебаг ИНФО").c_str(), NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(0.0, 0.0));
    //static float f = 0.0f;
    //ImGui::SliderFloat("MAX FPS", &f, 0.0f, 144.0f);
    //window->setFramerateLimit((int)f);


    ImGui::Text("CPU:\t%s", utils::computer::getCpu().c_str());
    ImGui::Text("GPU:\t%s", utils::encoding::to_utf8(utils::computer::getGpu()).c_str());
    DWORD max, used;
    utils::computer::getRAM(max, used);
    ImGui::Text("RAM:\t%i MB / %i%s %s", max, used, "%", utils::encoding::to_utf8(L"заружено").c_str());
    ImVec2 m_vec = io->MousePos;


    float ms = 1000.0f / io->Framerate;
    float fps = io->Framerate;

    ImGui::Text("PLAYER POS:\t(\t%.1f,\t%.1f\t)", m_peer->get_character_node()->get_pos().x, m_peer->get_character_node()->get_pos().y);
    ImGui::Text("MOUSE POS:\t(%.1f,%.1f)", m_vec.x, m_vec.y);
    ImGui::Text("TIME:\t%.1fsec; FRAME:\t%if", ImGui::GetTime(), ImGui::GetFrameCount());
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", ms, fps);


    if (debug_stats::fps_point == 500)
        debug_stats::fps_point = 0;

    debug_stats::fps_samples[debug_stats::fps_point] = fps;
    debug_stats::fps_point++;

    // вычисляем самый большой фпс из нашего списка
    float max_fps = 0.0f;
    for (auto sample : debug_stats::fps_samples)
        if (sample > max_fps)
            max_fps = sample;

    ImGui::PlotLines("FPS", debug_stats::fps_samples, 500, 0, NULL, 0.0, max_fps * 2.0, ImVec2(0.0, 70.0));

    //ImGui::ShowDemoWindow();

    ImGui::End();
    ImGui::PopFont();
}
void gameloops::drawRandomComets(float& deltatime) {
    // TODO: коменты пролетающие на фоне, чисто BackGround в космосе
}
void gameloops::drawBackgroundSpaceCircleEffect(float& deltatime) {
    float max = 0.0f;
    // цикл анимации для каждого пикселя
    for (int i = 0; i < m_settings::space_points_count; i++) {
        float scale_delta_y = sinf(i * 0.2f + ImGui::GetTime() * 0.25f);
        float scale_delta_x = cosf(i * 0.2f + ImGui::GetTime() * 0.25f);

        float rad_delta = i / m_settings::space_points_count;

        double angle = (.0015 * (rad_delta - 1.0 + 0.5));


        float dist_tocenter = vecmath::distance(Vector2f(screen_weight / 2, screen_height / 2), m_settings::space_points[i].position);
        if (dist_tocenter > max)
            max = dist_tocenter;


        Vector2f to_center = (Vector2f(screen_weight, screen_height) - m_settings::space_points[i].position);
        to_center.x += (20.0f * scale_delta_x);
        to_center.y += (20.0f * scale_delta_y);


        m_settings::space_points[i].position = Vector2f(to_center.x * cos(angle) - to_center.y * sin(angle),
            to_center.x * sin(angle) + to_center.y * cos(angle));
    }

    sf::View view = window->getDefaultView();
    view.zoom(0.5f - cosf(ImGui::GetTime()) * 0.02f);
    toview_center += vecmath::tovec2f(io->MouseDelta) * deltatime * 2.0f;
    view_center += (toview_center - view_center) * deltatime * 2.0f;
    view.setCenter(view_center);

    window->setView(view);
    window->draw(m_settings::space_points);
}
void gameloops::drawBackgroundSpaceFlyEffect(float& deltatime) {
    float max = 0.0f;
    // цикл анимации для каждого пикселя
    for (int i = 0; i < m_settings::space_points_count; i++) {
        if (m_settings::space_points[i].position.x <= 0) {
            m_settings::space_points[i].position.x = screen_weight;
            m_settings::space_points[i].position.x += rand() % 100;

            m_settings::space_points[i].position.y = rand() % screen_height;
        }
        m_settings::space_points[i].position.y += cosf(ImGui::GetTime()) * 0.2f;
        m_settings::space_points[i].position.x -= 100.0f * deltatime;
    }

    sf::View view = window->getDefaultView();
    view.zoom(0.5f - cosf(ImGui::GetTime()) * 0.02f);
    window->setView(view);
    window->draw(m_settings::space_points);
}
void gameloops::drawCredits() {
    ImGui::Begin("credits", NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(1, screen_height - 30));
    ImGui::Text("%s %s %s", utils::encoding::to_utf8(L"В РАЗРАБОТКЕ").c_str(),  CLIENT_VERSION, VERSION_STAGE);
    ImGui::End();
}

void gameloops::create_player(string public_hash, string private_hash, v2f pos, bool is_main) {
    playerPeer* pp = new playerPeer();

    

    characterNode* cn = new characterNode();
    cn->is_main(is_main);
    cn->set_pos(pos);
    cn->get_tile()->set_texture_id(1);

    pp->set_character_node(cn);
    pp->set_public_hash(public_hash);
    pp->set_private_hash(private_hash);
    pp->set_timestamp(time(0));

    if (is_main) m_peer = pp; // После заполения данных вносим наш пир как основной, если сделать ДО, то ты пойдешь нахуй еблан при обработке keyboard

    peers.push_back(pp);
}
void gameloops::connect_to_server() {
    if (connect_timer.getElapsedTime().asSeconds() < m_network::connect_every_sec)
        return;

    connect_timer.restart();

    if (tcp.connect(IpAddress("localhost"), DEFAULT_TCP_SERVER_PORT) != Socket::Done) {
        m_network::failed_count++;
        if (m_network::failed_count >= m_network::failed_max_count) {
            m_network::failed_count = 0;
            current_scene = SCENE::main_menu;
        }
        return;
    }
    
    tcp_status = Socket::Done;
    current_scene = SCENE::game_world;
    cout << "connected to server" << endl;
}
// Вернет True если всё гуд
bool gameloops::check_connection() {
    // TODO: проверка на дисконнект и тд
    if (current_scene != SCENE::game_world) return false;

    switch (tcp_status) {
        case Socket::Done:
            break;
        case Socket::Disconnected:
            current_scene = SCENE::main_menu;
            return false;
            break;
    }
    return true;
}
void gameloops::receive_packets() {
    Packet p;
    tcp_status = tcp.receive(p);
    
    if (p.getDataSize() <= 0) return; // проверка на говеный пакет

    std::string json_string(static_cast<const char*>(p.getData()), p.getDataSize());
    
    wcout << L"packet: " << utils::encoding::to_wide(json_string) << endl;

    //TODO: Обработка запросов от сервера в виде JSON (ПОДКЛЮЧИ ЛИБУ ЕБЛАН ТУПОЙ)
    try {
        json json_parsed = json::parse(utils::encoding::to_wide(json_string));
        
        switch ((int)json_parsed["c"]) {
        case (int)command::CREATE_PLAYER:
            create_player(
                json_parsed["public_hash"], 
                json_parsed["private_hash"], 
                v2f(json_parsed["pos"][0], 
                    json_parsed["pos"][1]),
                json_parsed["scc"]
            );
            break;
        case (int)command::SEND_CHAT_MSG:
            break;
        }
    }
    catch (...) {
        wcout << L"ERROR JSON PARSING: " << utils::encoding::to_wide(json_string) << endl;
    }
}

// ОСНОВНАЯ ФУНЦИЯ ГДЕ ПРОИСХОДИТ ОТРИСОВКА ВСЕЙ ГРАФИКИ
void gameloops::render(float& deltatime) {
    if (m_settings::is_debug)
        drawDebug();

    switch (current_scene) {
    case SCENE::main_menu:
        drawMainMenu(deltatime);
        break;
    case SCENE::main_menu_settings:
        drawMainSettings(deltatime);
        break;
    case SCENE::connection_process_game_server:
        drawConnectionProcessGameServer(deltatime);
        //connect_to_server(); // каждые 5 сек идет попытка подключения
        break;
    case SCENE::game_world:
        drawGameWorld(deltatime);
        break;
    }

    drawCredits(); 
}

// ОБРАБОТКА СЕТИ В ОТДЕЛЬНОМ ПОТОКЕ
void gameloops::network() {
    while (window->isOpen()) {
        // ПОПЫТКА ПОДКЛЮЧЕНИЯ
        if (current_scene == SCENE::connection_process_game_server && tcp_status != Socket::Done) {
            connect_to_server();
            continue;
        }

        //if (!check_connection()) {
        //    Sleep(100);
        //    continue;
        //}
        receive_packets();
        Sleep(100);
    }
}

// ОСНОВНАЯ ФУНКЦИЯ ДЛЯ ОБРАБОТКИ ВСЕХ КЛАВИШ
void gameloops::keyboard(float& deltatime) {
    if (ImGui::IsKeyReleased(ImGuiKey_F1))
        m_settings::is_debug = !m_settings::is_debug;

    if (current_scene == SCENE::game_world && tcp_status == Socket::Done && m_peer != NULL) {
        characterNode* p_node = m_peer->get_character_node();

        p_node->get_vel()->x *= ANTI_VELOCITY;
        p_node->get_vel()->y *= ANTI_VELOCITY;

        if (ImGui::IsKeyDown(ImGuiKey_W)) {
            p_node->get_vel()->y += -0.01;
            p_node->get_tile()->set_texture_id(4);
        }
        if (ImGui::IsKeyDown(ImGuiKey_S)) {
            p_node->get_vel()->y += 0.01;
            p_node->get_tile()->set_texture_id(1);
        }
        if (ImGui::IsKeyDown(ImGuiKey_D)) {
            p_node->get_vel()->x += 0.01;
            p_node->get_tile()->set_texture_id(2);
        }
        if (ImGui::IsKeyDown(ImGuiKey_A)) {
            p_node->get_vel()->x += -0.01;
            p_node->get_tile()->set_texture_id(3);
        }

        p_node->get_vel()->x = clamp(p_node->get_vel()->x, -MAX_VELOCITY, MAX_VELOCITY);
        p_node->get_vel()->y = clamp(p_node->get_vel()->y, -MAX_VELOCITY, MAX_VELOCITY);

        v2f delta_pos = p_node->get_pos() + *p_node->get_vel();

        p_node->set_pos(delta_pos);
    }
}