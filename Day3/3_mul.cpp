#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <cmath>     // For std::abs
#include <algorithm> // For std::sort
#include <sstream>
#include <regex>

using namespace std;

int main()
{
    // Open the text file
    ifstream f("mul.txt");

    // Check if the file is successfully opened
    if (!f.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    // Define the regex pattern
    regex pattern(R"(mul\(\d+,\d+\))");
    regex inner_pattern(R"(mul\((\d+),(\d+)\))");
    vector<pair<int, int>> pairs;
    string line;
    int total{0};

    // Read pairs directly into the vectors
    while (getline(f, line))
    {
        // Container to hold matches
        std::sregex_iterator it(line.begin(), line.end(), inner_pattern);
        std::sregex_iterator end;

        for (; it != end; ++it)
        {
            smatch match = *it;
            pair<int, int> pare;

            // Convert extracted strings to integers and store them in the pair
            pare.first = stoi(match[1]);
            pare.second = stoi(match[2]);
            cout << "#1" << pare.first << "#2" << pare.second << endl;

            pairs.push_back(pare);
        }
    }

        // Display all pairs
    std::cout << "All pairs:\n";
    for (const auto& p : pairs) {
        total += (p.first * p.second);
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }
    cout << total <<endl;

    f.close();
}