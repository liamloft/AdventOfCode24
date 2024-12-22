#include <algorithm> // For std::sort
#include <cmath>     // For std::abs
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility> // For std::pair
#include <vector>
#include <unordered_set>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    // Open the text file
    ifstream f("guard_path.txt");

    // Check if the file is successfully opened
    if (!f.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    vector<vector<char>> grid;
    std::string line;
    string letter;

    // Read file directly into the vectors
    while (std::getline(f, line))
    {
        std::vector<char> row(line.begin(), line.end());

        grid.push_back(row);
    }

    f.close();

    int total_rows = grid.size();
    int total_cols = grid[0].size();
    pair<int, int> starting_pos;

    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_cols; j++)
        {
            if (grid[i][j] == '^')
            {
                starting_pos.first = i;
                starting_pos.second = j;
            }
            cout << grid[i][j];
        }
        cout << endl;
    }

    cout << "Guard start at grid row: " << starting_pos.first << " col: " << starting_pos.second << endl;

    // Directions: up, right, down, left (clockwise)
    const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // (row change, column change)

    int rows = grid.size();
    int cols = grid[0].size();

    // Current position of the guard
    int row = starting_pos.first, col = starting_pos.second;
    int dir = 0; // Initially facing up (0 corresponds to up direction)

    unordered_set<string> visited;
    visited.insert(to_string(row) + "," + to_string(col)); // Mark starting position as visited

    while (true)
    {
        // If there's an obstacle, turn right (90 degrees)
        if (grid[row][col] == '#')
        {
            if (dir == 0 || 2)
            {
                row -= directions[dir].first;
            }
            if (dir == 1 || 3)
            {
                col -= directions[dir].second;
            }
            cout << "Turning right" << endl;
            dir = (dir + 1) % 4; // Turn right (clockwise)
        }

        // Move forward in the current direction
        row += directions[dir].first;
        col += directions[dir].second;

        cout << "movign to row: " << row << "col: " << col << endl;

        // Check if the guard goes out of bounds
        if (row < 0 || row >= rows || col < 0 || col >= cols)
        {
            cout << "The guard has left the area" << endl;
            break; // The guard has left the area
        }

        // Mark the new position as visited
        visited.insert(to_string(row) + "," + to_string(col));

        // // If the guard encounters an obstacle, turn right (90 degrees)
        // if (grid[row][col] == '#')
        // {
        //     dir = (dir + 1) % 4; // Turn right (clockwise)
        // }
        cout << "while loop" << endl;
        // Sleep for 0.5 seconds
        // std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 500 ms = 0.5 seconds
    }

    // Mark all visited positions with 'X'
    for (const string &pos : visited)
    {
        size_t commaPos = pos.find(',');
        int r = stoi(pos.substr(0, commaPos));
        int c = stoi(pos.substr(commaPos + 1));

        // Mark the cell in the grid with 'X'
        if (grid[r][c] == '.' || grid[r][c] == '^' || grid[r][c] == '>' || grid[r][c] == 'v' || grid[r][c] == '<')
        {
            grid[r][c] = 'X';
        }
    }

    int count{0};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << grid[i][j];
            if (grid[i][j] == 'X') {count++;}
        }
        cout << endl;
    }
    cout << "Total Xs: " << count << endl;
}