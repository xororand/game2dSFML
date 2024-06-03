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
    for (character_node* c : characters) {
        if (c->is_main()) {
            sf::View view = window->getDefaultView();
            view.setCenter(c->get_pos());

            window->setView(view);
        }
        // запись на отрисовку персонажа
        render_system::tiles.push_back(*c->get_tile());
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
    main_player = new character_node(v2f(0.0, 0.0));
    main_player->is_main(true);
    main_player->set_pos(v2f(screen_weight / 2.0, screen_height / 2.0));
    main_player->get_tile()->set_texture_id(1);

    character_node* player = new character_node(v2f(0.0, 0.0));
    player->set_pos(v2f(screen_weight / 2.0, screen_height / 2.0));
    player->get_tile()->set_texture_id(1);

    characters.push_back(main_player);
    characters.push_back(player);


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

void gameloops::drawDebug() {
    ImGui::PushFont(getStandartFont());

    ImGui::Begin(u8"Дебаг ИНФО", NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(0.0, 0.0));
    //static float f = 0.0f;
    //ImGui::SliderFloat("MAX FPS", &f, 0.0f, 144.0f);
    //window->setFramerateLimit((int)f);


    ImGui::Text("CPU:\t%s", utils::computer::getCpu().c_str());
    ImGui::Text("GPU:\t%s", utils::encoding::to_utf8(utils::computer::getGpu()).c_str());
    DWORD max, used;
    utils::computer::getRAM(max, used);
    ImGui::Text(u8"RAM:\t%i MB / %i%s загружено", max, used, "%");
    ImVec2 m_vec = io->MousePos;


    float ms = 1000.0f / io->Framerate;
    float fps = io->Framerate;
    ImGui::Text(u8"MOUSE POS:\t(%.1f,%.1f)", m_vec.x, m_vec.y);
    ImGui::Text(u8"TIME:\t%.1fsec; FRAME:\t%if", ImGui::GetTime(), ImGui::GetFrameCount());
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
void gameloops::drawMainMenu(float& deltatime) {
    drawBackgroundSpace(deltatime);

    ImGui::PushFont(getStandartFont());

    ImGui::SetNextWindowSize(ImVec2(screen_weight / 3.84f, screen_height / 2.16f));
    ImGui::SetNextWindowPos(ImVec2(screen_weight / 2 - (screen_weight / 3.84f) / 2, screen_height / 2 - (screen_height / 2.16f) / 2));
    ImGui::Begin(u8"mMain", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);//

    ImGui::Button(u8"Вход", ImVec2(250, 50));
    if (ImGui::Button(u8"Настройки", ImVec2(250, 50))) {
        current_ui = UI::main_settings;
    }
    if (ImGui::Button(u8"Выход", ImVec2(250, 50))) {
        exit(0);
    }

    ImGui::End();
    ImGui::PopFont();
    
}
void gameloops::drawMainSettings(float& deltatime) {
    drawBackgroundSpace(deltatime);

    ImGui::PushFont(getStandartFont());

    ImGui::SetNextWindowSize(ImVec2(screen_weight / 3.84f, screen_height / 2.16f));
    ImGui::SetNextWindowPos(ImVec2(screen_weight / 2 - (screen_weight / 3.84f) / 2, screen_height / 2 - (screen_height / 2.16f) / 2));
    ImGui::Begin("settings", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

    ImGui::Text(u8"Настройки");
    ImGui::Separator();
    //if (ImGui::Checkbox("VSYNC", &m_settings::vsync)) {
    //    window->setVerticalSyncEnabled(m_settings::vsync);
    //}

    ImGui::End();
    ImGui::PopFont();
}
void gameloops::drawGameServer(float& deltatime) {
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
void gameloops::drawRandomComets(float& deltatime) {
    // TODO: коменты пролетающие на фоне, чисто BackGround в космосе
}
void gameloops::drawBackgroundSpace(float& deltatime) {
    float max = 0.0f;
    // цикл анимации для каждого пикселя
    for (int i = 0; i < m_settings::space_points_count; i++) {
        float scale_delta_y = sinf(i * 0.2f + ImGui::GetTime() * 0.25f);
        float scale_delta_x = cosf(i * 0.2f + ImGui::GetTime() * 0.25f);

        float rad_delta = i / m_settings::space_points_count;

        double angle = (.0015 * (rad_delta - 1.0 + 0.5)) * (1.0f / io->Framerate) * 100.0f;


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
void gameloops::drawMenu(float& deltatime) {
    switch (current_ui) {
        case UI::main_menu:
            drawMainMenu(deltatime);
            break;
        case UI::main_settings:
            drawMainSettings(deltatime);
            break;
        case UI::game_server:
            drawGameServer(deltatime);
            break;
    }
    
}
void gameloops::drawCredits() {
    ImGui::Begin(u8"credits", NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(1, screen_height - 30));
    ImGui::Text(u8"В РАЗРАБОТКЕ");

    ImGui::End();
}


// ОСНОВНАЯ ФУНЦИЯ ГДЕ ПРОИСХОДИТ ОТРИСОВКА ВСЕЙ ГРАФИКИ
void gameloops::render(float& deltatime) {
    if (m_settings::is_debug)
        drawDebug();

    drawMenu(deltatime);
    drawCredits();
    
}

// ОСНОВНАЯ ФУНКЦИЯ ДЛЯ ОБРАБОТКИ ВСЕХ КЛАВИШ
void gameloops::keyboard(float& deltatime) {
    if (ImGui::IsKeyReleased(Keyboard::F1))
        m_settings::is_debug = !m_settings::is_debug;

    main_player->get_vel()->x *= ANTI_VELOCITY;
    main_player->get_vel()->y *= ANTI_VELOCITY;

    if (ImGui::IsKeyDown(Keyboard::W)) {
        main_player->get_vel()->y += -0.01;
        main_player->get_tile()->set_texture_id(4);
    } 
    if (ImGui::IsKeyDown(Keyboard::S)) {
        main_player->get_vel()->y += 0.01;
        main_player->get_tile()->set_texture_id(1);
    } 
    if (ImGui::IsKeyDown(Keyboard::D)) {
        main_player->get_vel()->x += 0.01;    
        main_player->get_tile()->set_texture_id(2);
    } 
    if (ImGui::IsKeyDown(Keyboard::A)) {
        main_player->get_vel()->x += -0.01;
        main_player->get_tile()->set_texture_id(3);
    }

    main_player->get_vel()->x = clamp(main_player->get_vel()->x, -MAX_VELOCITY, MAX_VELOCITY);
    main_player->get_vel()->y = clamp(main_player->get_vel()->y, -MAX_VELOCITY, MAX_VELOCITY);

    //cout << main_player->get_vel()->x << " " << main_player->get_vel()->y << endl;
    //delta_pos = v2f(clamp(delta_pos.x, -ONE, ONE), clamp(delta_pos.y, -ONE, ONE));

    v2f delta_pos = main_player->get_pos() + *main_player->get_vel();

    main_player->set_pos(delta_pos);
}