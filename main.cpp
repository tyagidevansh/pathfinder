#include <SFML/Graphics.hpp>
#include <array>
#include <map>

class Grid {
    static const int SCREEN_HEIGHT = 800;
    static const int SCREEN_WIDTH = 1000;
    static const int SQUARE = 14;
    std::pair<int, int> starting = {-1, -1};
    std::pair<int, int> ending = {-1, -1};

    enum Cell {
        empty,
        wall,
        start,
        end
    };
    
    //defining the map matrix
    std::array<std::array<Cell, SCREEN_HEIGHT/SQUARE>, SCREEN_WIDTH/14> map;

public:
    Grid() {
        for (size_t i = 0; i < SCREEN_HEIGHT/SQUARE; i++) {
            for (size_t j = 0; j < SCREEN_HEIGHT/SQUARE; j++) {
                map[i][j] = Cell::empty;
            }
        }
    }
    void render(sf::RenderWindow& window){
        for (size_t i = 0; i < SCREEN_HEIGHT/SQUARE; i++) {
            for (size_t j = 0; j < SCREEN_HEIGHT/SQUARE; j++) {
                sf::RectangleShape cell(sf::Vector2f(SQUARE, SQUARE));
                cell.setPosition(i * SQUARE, j * SQUARE);
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(2);
                if (map[i][j] == Cell::empty) {
                    cell.setFillColor(sf::Color::Blue);
                } else if (map[i][j] == Cell::wall) {
                    cell.setFillColor(sf::Color::White);
                } else if (map[i][j] == Cell::start) {
                    cell.setFillColor(sf::Color::Green);
                } else {
                    cell.setFillColor(sf::Color::Red);
                }
                window.draw(cell);
            }
        }
    }

    void handleInput(sf::Event& event, sf::RenderWindow& window) {
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
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinder");

    Grid grid;    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed 
        || event.type == sf::Event::KeyPressed) {
            grid.handleInput(event, window);
        }
        

        window.clear();
        grid.render(window);
        window.display();
    }
    return 0;
}