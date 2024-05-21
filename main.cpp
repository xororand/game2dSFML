#include "main.h"
#include "game.h"

int main() {
    setlocale(LC_ALL, "ru");
    IMGUI_CHECKVERSION();

    Clock deltaclock;
    gameloops loops;

    RenderWindow window(sf::VideoMode(loops.getScreenWidth(), loops.getScreenHeight()), "2D GAME", Style::Fullscreen);
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);
    loops.setMainWindow(&window);
    loops.setImguiIO(&ImGui::GetIO());

    ImGui::GetIO().Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)
    // IO.Fonts->AddFontDefault(); // this will load default font as well
    ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF("fonts/arial.ttf", 15.f, NULL,
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    loops.setStandartFont(font);

    ImGui::SFML::UpdateFontTexture(); // important call: updates font texture

    Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
           ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = deltaclock.restart().asSeconds();

        ImGui::SFML::Update(window, deltaClock.restart());

        //ImGui::ShowDemoWindow();

        window.clear();
        loops.render(deltaTime);
        ImGui::SFML::UpdateFontTexture();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

