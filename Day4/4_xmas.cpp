#include <algorithm>  // For std::sort
#include <cmath>      // For std::abs
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>  // For std::pair
#include <vector>

using namespace std;

int main() {
  // Open the text file
  ifstream f("xmas.txt");

  // Check if the file is successfully opened
  if (!f.is_open()) {
    cerr << "Error opening the file!" << endl;
    return 1;
  }

  vector<vector<char>> grid;
  std::string line;
  string letter;

  // Read file directly into the vectors
  while (std::getline(f, line)) {
    std::vector<char> row(line.begin(), line.end());

    grid.push_back(row);
  }

  f.close();

  // grid [1][3] = "X";
  cout << grid[1][2] << endl;

  vector<pair<int, int>> directions = {
      {-1, 0},  // left
      {1, 0},   // right
      {0, 1},   // up
      {0, -1},  // down
      {-1, 1},  // up-left
      {1, 1},   // up-right
      {1, -1},  // down-right
      {-1, -1}  // down-left
  };

  string word = "XMAS";
  int rows = grid.size();
  int cols = grid[0].size();

  int found_xmas = 0;

  // gird[i][j] is the starting point
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (const auto& dir : directions) {
        int x = i;
        int y = j;
        string found_word = "";
        // important here it only goes to the length of the word and the specific char
        for (const auto& letter : word) {
          if (x < 0 || x >= rows || y < 0 || y >= cols) {
            break;
          }
          found_word += grid[x][y];
          if (found_word == word) {
            cout << "Found word " << word << " at (" << i << ", " << j << ")" << endl;
            cout << ++found_xmas << endl;
            break;
          }
          x += dir.first;
          y += dir.second;
        }
      }
    }
  }

  // Print the grid
  // for (const auto& row : grid) {
  //     for (const auto& str : row) {
  //         std::cout << str << " ";
  //     }
  //     std::cout << std::endl;
  // }

  return 0;
}