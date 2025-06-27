#include "game.h"

//class Game
//{
//public:
//    Game();
//    void run();
//
//private:
//    void processEvents();
//    void update(sf::Time deltaTime);
//    void render();
//
//    sf::RenderWindow window;
//    sf::Texture playerTexture;
//    sf::Sprite player;
//
//    float playerSpeed = 200.f;
//};
//
//Game::Game() : window(sf::VideoMode({ 800, 600 }), "SFML Game"), playerTexture("smiley.png"), player(playerTexture)
//{
//    player.setPosition({ 100, 100 });
//}
//
//void Game::run()
//{
//    sf::Clock clock;
//
//    // run the program as long as the window is open
//    while (window.isOpen())
//    {
//        sf::Time deltaTime = clock.restart();
//
//        processEvents();
//        update(deltaTime);
//        render();
//    }
//}
//
//void Game::processEvents()
//{
//    // check all the window's events that were triggered since the last iteration of the loop
//    while (auto event = window.pollEvent())
//    {
//        // "close requested" event: we close the window
//        if (event->is<sf::Event::Closed>())
//            window.close();
//    }
//}
//
//void Game::update(sf::Time deltaTime)
//{
//    sf::Vector2f movement(0.f, 0.f);
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
//        movement.y -= playerSpeed;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
//        movement.y += playerSpeed;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//        movement.x -= playerSpeed;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
//        movement.x += playerSpeed;
//
//    player.move(movement * deltaTime.asSeconds());
//}
//
//void Game::render()
//{
//    window.clear();
//    window.draw(player);
//    window.display();
//}

int main()
{
    Game game;
    game.run();

    return 0;
}
