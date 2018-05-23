#include "ques_a_b.h"
#include "ques_c.h"
#include <iostream>

int main()
{

    std::vector<std::vector<int>> grid;
    grid.push_back(std::vector<int>{2, 3, 9, 0, 1});
    grid.push_back(std::vector<int>{1, 5, 8, 5, 4});
    grid.push_back(std::vector<int>{4, 7, 6, 3, 3});
    grid.push_back(std::vector<int>{3, 10, 4, 7, 8});
    grid.push_back(std::vector<int>{11, 2, 6, 9, 2});

    std::string route;
    std::cout << route_of_maximum_gain_c(grid, route) << '\t' << route << '\n';
}