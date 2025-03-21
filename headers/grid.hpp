#pragma once
#include <array>
#include <SFML\Graphics.hpp>
class Grid {
protected:
    static const int SCREEN_HEIGHT = 800;
    static const int SCREEN_WIDTH = 1200;
    static const int SQUARE = 20;
    static const int ROWS = SCREEN_HEIGHT/SQUARE;
    static const int COLS = SCREEN_WIDTH/SQUARE;
    std::pair<int, int> starting = {-1, -1};
    std::pair<int, int> ending = {-1, -1};

    enum Cell {
        empty,
        wall,
        start,
        end,
        visited,
        path
    };
    
    //defining the map matrix
    std::array<std::array<Cell, ROWS>, COLS> map;

public:
    Grid();
    void render(sf::RenderWindow& window);
    void handleInput(sf::Event& event, sf::RenderWindow& window);

};