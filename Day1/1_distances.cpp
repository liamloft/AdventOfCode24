#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <utility>
#include <list>

using namespace std;

int main()
{
    // Open the text file
    ifstream f("1_location_ids.txt");

    // Check if succesfully opened
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    std::string line;
    int num1, num2;
    list<int> list_nums1{};
    list<int> list_nums2{};

    while (getline(f, line))
    {
        // Convert line to integers
        std::istringstream iss(line);
        iss >> num1 >> num2;
        // vec_pair.push_back({num1, num2});

        list_nums1.push_back(num1);
        list_nums2.push_back(num2);
    }

    f.close();
    // cout << list_nums1.front() << endl;
    // cout << list_nums2.front() << endl;

    list_nums1.sort();
    list_nums2.sort();

    if (list_nums1.size() != list_nums2.size())
    {
        cerr << "Lists do not have same size" << endl;
        return 1;
    }

    int total_dif{0};
    auto it1 = list_nums1.begin();
    auto it2 = list_nums2.begin();

    for (; it1 != list_nums1.end() && it2 != list_nums2.end(); ++it1, ++it2)
    {
        total_dif += abs(*it1 - *it2);
        // cout << *it1 << " - " << *it2 << endl;
    }

    std::cout << total_dif << std::endl;
    return 0;
}