#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>

class GridBFS {
public:
    GridBFS(const std::vector<std::vector<char>>& grid);
    std::vector<std::pair<int, int>> findShortestPath(std::pair<int, int> start, std::pair<int, int> end);

private:
    std::vector<std::vector<char>> grid;
    int rows;
    int cols;

    bool isValid(int x, int y);
};

GridBFS::GridBFS(const std::vector<std::vector<char>>& grid) : grid(grid) {
    rows = grid.size();
    cols = (rows > 0) ? grid[0].size() : 0;
}

bool GridBFS::isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 'O'; // Assuming 'O' represents an open cell
}

std::vector<std::pair<int, int>> GridBFS::findShortestPath(std::pair<int, int> start, std::pair<int, int> end) {
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<std::pair<int, int>>> parent(rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));
    std::queue<std::pair<int, int>> queue;

    int startX = start.first;
    int startY = start.second;
    int endX = end.first;
    int endY = end.second;

    queue.push({startX, startY});
    visited[startX][startY] = true;

    // Define possible moves (up, down, left, right)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();
        int x = current.first;
        int y = current.second;

        // Check neighbors
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                parent[newX][newY] = {x, y};
                queue.push({newX, newY});

                // If the destination is reached, reconstruct the path
                if (newX == endX && newY == endY) {
                    std::vector<std::pair<int, int>> path;
                    int curX = endX;
                    int curY = endY;

                    while (curX != -1 && curY != -1) {
                        path.push_back({curX, curY});
                        auto& p = parent[curX][curY];
                        curX = p.first;
                        curY = p.second;
                    }

                    std::reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    // If no path is found, return an empty vector
    return std::vector<std::pair<int, int>>();
}

int main() {
    // Example usage:
    std::vector<std::vector<char>> grid = {
        {'O', 'O', 'O', 'O', 'O'},
        {'O', 'X', 'O', 'X', 'O'},
        {'O', 'O', 'O', 'O', 'O'},
        {'O', 'X', 'O', 'X', 'O'},
        {'O', 'O', 'O', 'O', 'O'}
    };

    GridBFS gridBFS(grid);

    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {4, 4};

    std::vector<std::pair<int, int>> shortestPath = gridBFS.findShortestPath(start, end);

    if (!shortestPath.empty()) {
        std::cout << "Shortest path from start to end:" << std::endl;
        for (const auto& point : shortestPath) {
            std::cout << "(" << point.first << ", " << point.second << ") ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path from start to end found." << std::endl;
    }

    return 0;
}
