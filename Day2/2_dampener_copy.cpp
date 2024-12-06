#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>     // For std::abs
#include <algorithm> // For std::sort
#include <sstream>

using namespace std;

int main()
{
    // Open the text file
    ifstream f("reports.txt");

    // Check if the file is successfully opened
    if (!f.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    std::string line;
    int number{0};
    int safe{0};
    vector<vector<int>> reports;

    // Read pairs directly into the vectors
    while (getline(f, line))
    {
        std::istringstream iss(line);
        vector<int> row;
        while (iss >> number)
        {
            row.push_back(number);
        }
        reports.push_back(row);
    }

    f.close();

    // Output the matrix
    for (auto &row : reports)
    {
        bool increasing{false};
        int safe_row{0};
        bool damper{false};
        if (row[0] < row[1])
        {
            increasing = true;
        }
        auto row_size = row.size();
        cout << "this row has " << row_size << endl;
        for (auto it = row.begin() + 1; it != row.end(); ++it)
        {
            // skip over first element
            if (*(it - 1) < *it && *it <= (*(it - 1) + 3) && increasing)
            {
                cout << *(it-1) << " < " << *it;
                safe_row++;
            }
            else if (*(it - 1) > *it && *it >= (*(it - 1) + 3) && !increasing)
            {
                cout << *(it-1) << " > " << *it;
                safe_row++;
            }
            // Dampener Increasing
            else if (*(it-1) < *(it+1) && *(it+1) <= (*(it-1) + 3) && increasing)
            {
                cout << "applied dampener increasing removed " << *it << endl;;
                row.erase(it);
                damper = true;
            }
            else if (*(it-1) > *(it+1) && *(it+1) >= (*(it-1) + 3) && !increasing)
            {
                cout << "applied dampener decreasing removed " << *it << endl;
                row.erase(it);
                damper = true;
            }
            else if (it == row.end() - 1)
            {
                safe_row++;
                damper = true;
            }
            cout << "safe_row#" << safe_row << endl;
        }
        if (safe_row == row_size - 1)
        {
            cout << "Adding to Safe" << endl;
            safe++;
        }
        // else if (damper && safe_row == row_size - 2)
        // {
        //     cout << "Adding to Safe via damper" << endl;
        //     safe++;
        // }
    }

    cout << "safe: " << safe << endl;
    return 0;
}