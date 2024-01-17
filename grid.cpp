#include "headers/grid.hpp"
#include <SFML\Graphics.hpp>

Grid::Grid() {
        for (size_t i = 0; i < COLS; i++) {
            for (size_t j = 0; j < ROWS; j++) {
                map[i][j] = Cell::empty;
            }
        }
    }

void Grid::render(sf::RenderWindow& window){
        for (size_t i = 0; i < COLS; i++) {
            for (size_t j = 0; j < ROWS; j++) {
                sf::RectangleShape cell(sf::Vector2f(SQUARE, SQUARE));
                cell.setPosition(i * SQUARE, j * SQUARE);
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(2);
                if (map[i][j] == Cell::empty) {
                    cell.setFillColor(sf::Color(40, 40, 125));
                } else if (map[i][j] == Cell::wall) {
                    cell.setFillColor(sf::Color::White);
                } else if (map[i][j] == Cell::start) {
                    cell.setFillColor(sf::Color::Green);
                } else if (map[i][j] == Cell::end) {
                    cell.setFillColor(sf::Color::Red);
                } else if (map[i][j] == Cell::visited) {
                    cell.setFillColor(sf::Color::Yellow);
                }
                window.draw(cell);
            }
        }
    }

void Grid::handleInput(sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Event mouseEvent;
                while (window.pollEvent(mouseEvent)) {
                    if (mouseEvent.type == sf::Event::MouseButtonReleased && mouseEvent.mouseButton.button == sf::Mouse::Left) {
                        break;
                    }
                }

                int i = sf::Mouse::getPosition(window).x / SQUARE;
                int j = sf::Mouse::getPosition(window).y / SQUARE;
                map[i][j] = Cell::wall;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            if (starting.first != -1 && starting.second != -1) {
                map[starting.first][starting.second] = Cell::empty;
            }     
            int i = sf::Mouse::getPosition(window).x / SQUARE;
            int j = sf::Mouse::getPosition(window).y / SQUARE;
            map[i][j] = Cell::start;
            starting = {i,j};
            printf("%d, %d ", starting.first, starting.second);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
            if (ending.first != -1 && ending.second != -1){
                map[ending.first][ending.second] = Cell::empty;
            }
            int i = sf::Mouse::getPosition(window).x / SQUARE;
            int j = sf::Mouse::getPosition(window).y / SQUARE;
            map[i][j] = Cell::end;
            ending = {i,j};
        }
    }