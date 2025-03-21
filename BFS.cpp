#include <chrono>
#include <thread>
#include "headers\BFS.hpp"
#include <algorithm>

BFS::BFS() : Grid() {}

bool BFS::checkStartEnd()
{
    return (starting.first != -1 && starting.second != -1 && ending.first != -1 && ending.second != -1);
}

bool BFS::isValid(int x, int y)
{
    return x >= 0 && x < COLS && y >= 0 && y < ROWS && map[x][y] != Cell::wall;
}

std::vector<std::pair<int, int>> BFS::shortestPath(sf::RenderWindow &window)
{
    std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
    std::vector<std::vector<std::pair<int, int>>> parent(ROWS, std::vector<std::pair<int, int>>(COLS, {-1, -1}));
    std::queue<std::pair<int, int>> queue;

    int startX = starting.first;
    int startY = starting.second;
    int endX = ending.first;
    int endY = ending.second;

    queue.push({startX, startY});
    visited[startY][startX] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!queue.empty())
    {
        auto current = queue.front();
        queue.pop();
        int x = current.first;
        int y = current.second;

        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY) && !visited[newY][newX])
            {
                visited[newY][newX] = true;
                map[newX][newY] = Cell::visited;
                parent[newY][newX] = {x, y};
                queue.push({newX, newY});

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                render(window); 
                // std::this_thread::sleep_for(std::chrono::milliseconds(1));

                if (newX == endX && newY == endY)
                {
                    std::vector<std::pair<int, int>> path;
                    int curX = endX;
                    int curY = endY;

                    while (curX != -1 && curY != -1)
                    {
                        path.push_back({curX, curY});
                        auto &p = parent[curY][curX];
                        curX = p.first;
                        curY = p.second;
                    }

                    std::reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    return std::vector<std::pair<int, int>>();
}

void BFS::markPath(sf::RenderWindow &window)
{
    std::vector<std::pair<int, int>> path = shortestPath(window);
    for (const auto &p : path)
    {
        map[p.first][p.second] = Cell::path;
    }
}