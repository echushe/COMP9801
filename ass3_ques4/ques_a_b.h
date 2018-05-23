#pragma once

#include <vector>
#include <string>
#include <algorithm>

typedef long long int lint;

struct cell
{
    // Default accumulated value of the cell is zero
    int acc_val;
    char move_from;

    cell() : acc_val{0}, move_from{'R'} {}
};

// Time complexity of this algorithm is O(m * n)
// Space compleixty of this algorithm is O(m * n)
int route_of_maximum_gain(const std::vector<std::vector<int>> & grid, std::string & route)
{
    std::vector<std::vector<cell>> cache;
    std::vector<char> re_route;

    lint rows = grid.size();
    lint cols = grid[0].size();


    // Add the zero row
    cache.push_back(std::vector<cell>{ static_cast<size_t>(cols) + 1 });

    // Traverse the grid from top-left to bottom right.
    // Time complexity: O(m * n)
    for (lint i = 0; i < rows; ++i)
    {
        // Add a new row to the cache
        cache.push_back(std::vector<cell>{ static_cast<size_t>(cols) + 1 });

        for (lint j = 0; j < cols; ++j)
        {
            // Compare the accumulated value of the left neighbor and the upper neighbor.
            // Pick up the larger value, add the value to accumulated value of current cell.
            // By the way, determine the direction of movement, the direction of move is always 
            // from the cell whose accumulated value is larger.
            if (cache[i][j + 1].acc_val > cache[i + 1][j].acc_val)
            {
                cache[i + 1][j + 1].acc_val = cache[i][j + 1].acc_val + grid[i][j];
                cache[i + 1][j + 1].move_from = 'D';
            }
            else
            {
                cache[i + 1][j + 1].acc_val = cache[i + 1][j].acc_val + grid[i][j];
                cache[i + 1][j + 1].move_from = 'R';
            }
        }
    }

    lint i = rows;
    lint j = cols;

    // Find out the optimal route.
    // Time complexity is O(m + n)
    while (i > 1 || j > 1)
    {
        re_route.push_back(cache[i][j].move_from);

        if (cache[i][j].move_from == 'D')
        {
            --i;
        }
        else
        {
            --j;
        }
    }

    // Reverse the sequence of the route
    // Time complexity: O(m + n)
    route.clear();
    for (auto itr = re_route.rbegin(); itr != re_route.rend(); ++itr)
    {
        route.push_back(*itr);
    }

    // Return the total gain
    return cache[rows][cols].acc_val;
}




