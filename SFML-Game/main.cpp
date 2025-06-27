#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    sf::RenderWindow window;
    sf::CircleShape player;

    // Example movement speed
    float playerSpeed = 100.f;
};

Game::Game() : window(sf::VideoMode({ 800, 600 }), "SFML Game"), player(40.f) {
    player.setFillColor(sf::Color::Green);
    player.setPosition({ 100, 100 });
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        processEvents();
        update(deltaTime);  // <-- update method
        render();
    }
}

void Game::processEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
    }
}

void Game::update(sf::Time deltaTime) {
    // Example: Move player to the right constantly
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= playerSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += playerSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= playerSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += playerSpeed;

    player.move(movement * deltaTime.asSeconds());
}

void Game::render() {
    window.clear();
    window.draw(player);
    window.display();
}

int main() {
    Game game;
    game.run();
    return 0;
}
