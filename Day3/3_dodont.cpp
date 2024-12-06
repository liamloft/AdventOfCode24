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
    string line;
    string huge_string{""};

    // Read pairs directly into the vectors
    while (getline(f, line))
    {
        huge_string += line;
    }

    cout << huge_string << endl;
    std::regex delete_pattern(R"(don't\(\).+?do\(\))");

    // Use regex_replace to remove the matched chunk
    std::string smaller_huge_string = std::regex_replace(huge_string, delete_pattern, "");

    // Output the result
    std::cout << "Result: " << smaller_huge_string << std::endl;

    regex inner_pattern(R"(mul\((\d+),(\d+)\))");
    vector<pair<int, int>> pairs;
    int total{0};

    // Container to hold matches
    std::sregex_iterator it(smaller_huge_string.begin(), smaller_huge_string.end(), inner_pattern);
    std::sregex_iterator end;

    for (; it != end; ++it)
    {
        smatch match = *it;
        pair<int, int> pare;

        // Convert extracted strings to integers and store them in the pair
        pare.first = stoi(match[1]);
        pare.second = stoi(match[2]);
        // cout << "#1" << pare.first << "#2" << pare.second << endl;

        pairs.push_back(pare);
    }

    // Display all pairs
    std::cout << "All pairs:\n";
    for (const auto &p : pairs)
    {
        total += (p.first * p.second);
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }
    cout << total << endl;

    f.close();
}