#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include "managers/GameManager.h"
#include "Resources.h"

int main() {

    sf::VideoMode aWindowVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::RenderWindow window(aWindowVideoMode, "Simple snake");

    //Calculate game view position and size
    sf::Vector2f aGameCenter(0.f, 0);
    sf::Vector2f aGameSize(aWindowVideoMode.width, aWindowVideoMode.height);
    sf::FloatRect aGameRect(aGameCenter, aGameSize);

    convez::games::managers::GameManager aGameManager(aGameRect, "Player 1");
    aGameManager.initNewGame();

    while (window.isOpen())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(GAME_TICK_MILLISECONDS));
        sf::Event event{};
        // Process inputs
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        aGameManager.processInput();
        aGameManager.tick();

        window.clear();
        aGameManager.drawGameView(window);
        window.display();
    }
}
