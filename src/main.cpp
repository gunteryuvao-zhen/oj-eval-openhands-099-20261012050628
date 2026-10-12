#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Function to perform BFS and return the sum of fish in the connected component
int bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int startRow, int startCol) {
    int m = grid.size();
    int n = grid[0].size();
    int fishCount = 0;
    
    // Directions for adjacent cells (up, down, left, right)
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    queue<pair<int, int>> q;
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;
    fishCount += grid[startRow][startCol];
    
    while (!q.empty()) {
        pair<int, int> current = q.front();
        int row = current.first;
        int col = current.second;
        q.pop();
        
        // Check all four adjacent cells
        for (auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;
            
            // Check if the new position is within bounds and is a water cell not yet visited
            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && 
                grid[newRow][newCol] > 0 && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                fishCount += grid[newRow][newCol];
                q.push({newRow, newCol});
            }
        }
    }
    
    return fishCount;
}

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    // Create a visited array to keep track of visited cells
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    int maxFish = 0;
    
    // Iterate through all cells in the grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // If the cell is water and not visited, perform BFS
            if (grid[i][j] > 0 && !visited[i][j]) {
                int fishInComponent = bfs(grid, visited, i, j);
                maxFish = max(maxFish, fishInComponent);
            }
        }
    }
    
    cout << maxFish << endl;
    
    return 0;
}