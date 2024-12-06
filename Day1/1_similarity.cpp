#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    // Open the text file
    ifstream f("1_location_ids.txt");

    // Check if the file is successfully opened
    if (!f.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    int num1, num2;
    vector<int> list1, list2;

    // Read pairs directly into the vectors
    while (f >> num1 >> num2)
    {
        list1.push_back(num1);
        list2.push_back(num2);
    }

    f.close();

    // Sort both lists independently
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    // Ensure both lists have the same size
    if (list1.size() != list2.size())
    {
        cerr << "Lists do not have the same size!" << endl;
        return 1;
    }

    // Calculate a total similarity score by adding up each number in the 
    // left list after multiplying it by the number of times that number 
    // appears in the right list.
    int similarity = 0;
    for (size_t i = 0; i < list1.size(); ++i)
    {
        similarity += std::count(list2.begin(), list2.end(), list1[i]) * list1[i];
    }


    // // Calculate the total difference in a single pass
    // int total_dif = 0;
    // for (size_t i = 0; i < list1.size(); ++i)
    // {
    //     total_dif += abs(list1[i] - list2[i]);
    // }

    // Output the result
    cout << similarity << endl;
    return 0;
}