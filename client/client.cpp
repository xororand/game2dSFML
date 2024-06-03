#include "client.h"
#include "game/game.h"

int main() {
    setlocale(LC_ALL, "RUS");
    IMGUI_CHECKVERSION();

    Clock deltaclock;
    gameloops loops;

    RenderWindow window(sf::VideoMode(loops.getScreenWidth(), loops.getScreenHeight()), "2D GAME", Style::Fullscreen);
    window.setFramerateLimit(144);
    //window.setVerticalSyncEnabled(true);

    ImGui::SFML::Init(window);
    loops.setMainWindow(&window);
    loops.setImguiIO(&ImGui::GetIO());

    ImGui::GetIO().Fonts->Clear();

    ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((current_path().string() + "/data/fonts/arialbd.ttf").c_str(), 15.f, NULL,
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

    loops.setStandartFont(font);

    ImGui::SFML::UpdateFontTexture();

    Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                loops.setScreenHeight(event.size.height);
                loops.setScreenWidth(event.size.width);
            }
        }

        float deltaTime = deltaclock.restart().asSeconds();

        ImGui::SFML::Update(window, deltaClock.restart());

        window.clear(Color(10.0, 10.0, 10.0));

        loops.render(deltaTime);
        loops.keyboard(deltaTime);

        ImGui::SFML::UpdateFontTexture();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

