#include <SFML/Graphics.hpp>
#include <array>
#include "headers/grid.hpp"
#include "headers/BFS.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Pathfinder");

    //Grid grid;    
    BFS bfs;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            bfs.handleInput(event, window);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (bfs.checkStartEnd()) {
                bfs.markPath();
            }
        } 
        

        window.clear();
        bfs.render(window);
        window.display();
    }
    return 0;
}