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
    int number {0};
    int safe {0};
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
    for (const auto &row : reports)
    {
        bool increasing{false};
        int safe_row {0};
        if (row[0] < row[1])
        {
            increasing = true;
        }
        cout << "this row has " << row.size() << endl;
        for (int i = 1; i < row.size(); i++)
        {
            // skip over first element
            if (row[i - 1] < row[i] && row[i] <= (row[i - 1] + 3) && increasing)
            {
                cout << row[i - 1] << " < " << row[i];
                safe_row++;
            }
            else if (row[i - 1] > row[i] && row[i] >= (row[i - 1] - 3) && !increasing)
            {
                cout << row[i - 1] << " > " << row[i];
                safe_row++;
            }
            cout << "safe_row#" << safe_row << endl;
        }
        if (safe_row == row.size()-1)
        {
            cout << "Adding to Safe" << endl;
            safe++;
        }
    }

    cout << "safe: " << safe << endl;
    return 0;
}