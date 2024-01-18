#pragma once
#include "grid.hpp"
#include <queue>
#include <vector>

class BFS : public Grid {
public:
    //BFS(Grid& sharedGrid);
    BFS();
    bool checkStartEnd();
    bool isValid(int x, int y);
    std::vector<std::pair<int, int>> shortestPath();
    void markPath();
};