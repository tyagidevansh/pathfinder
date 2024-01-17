#pragma once
#include "grid.hpp"
#include <queue>
#include <vector>

class BFS : public Grid {
public:
    BFS(Grid& sharedGrid);
    bool checkStartEnd();
    bool isValid(int x, int y);
    std::vector<std::pair<int, int>> shortestPath(std::pair<int, int> starting, std::pair<int, int> ending);
    void markPath();
};