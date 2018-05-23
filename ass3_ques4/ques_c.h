#pragma once

#include <vector>
#include <string>
#include <algorithm>

// This integer version sqrt is adopted from
// WIKIPEDIA (Integer Square Root)
lint int_sqrt(lint n)
{
    if (n < 2)
    {
        return n;
    }
    else
    {
        lint small = int_sqrt(n >> 2) << 1;
        lint large = small + 1;
        if (large * large > n)
        {
            return small;
        }
        else
        {
            return large;
        }
    }
}

// Time complexity of this algorithm is O(m * n)
// Space compleixty of this algorithm is O(n * sqrt(m))
int route_of_maximum_gain_c(const std::vector<std::vector<int>> & grid, std::string & route)
{
    lint rows = grid.size();
    lint cols = grid[0].size();

    lint block_size = int_sqrt(rows);

    // This cache stores first row of each scanning block, there are
    // sqrt(m) scanning blocks, which means there are sqrt(m) block beginners.
    // Size of this cache is O(n * sqrt(m))
    std::vector<std::vector<cell>> block_beginners;

    // This cache stores accumulative values of one scanning block.
    // Each scanning block has sqrt(m) rows.
    // Size of this cache is O(n * sqrt(m))
    std::vector<std::vector<cell>> block_cache;
    
    // Cache of the optimal route, its size is O(m + n)
    std::vector<char> re_route;

    // There are 2 rows of scanners.
    // Scanner A represents the previous row.
    // Scanner B represents the current row.
    // We will swap A and B when finishing scanning each row.
    std::vector<cell> scanner_A{ static_cast<size_t>(cols) + 1 };
    std::vector<cell> scanner_B{ static_cast<size_t>(cols) + 1 };

    // Traverse the grid from top-left to bottom right.
    // Time complexity: O(m * n)
    for (lint i = 0; i < rows; ++i)
    {
        for (lint j = 0; j < cols; ++j)
        {
            // Compare the accumulated value of the left neighbor and the upper neighbor.
            // Pick up the larger value, add the value to accumulated value of current cell.
            // By the way, determine the direction of movement, the direction of move is always 
            // from the cell whose accumulated value is larger.
            if (scanner_A[j + 1].acc_val > scanner_B[j].acc_val)
            {
                scanner_B[j + 1].acc_val = scanner_A[j + 1].acc_val + grid[i][j];
                scanner_B[j + 1].move_from = 'D';
            }
            else
            {
                scanner_B[j + 1].acc_val = scanner_B[j].acc_val + grid[i][j];
                scanner_B[j + 1].move_from = 'R';
            }
        }

        // Save first row of each scanning block.
        if (0 == i % block_size)
        {
            block_beginners.push_back(scanner_B);
        }

        // Swap scanner_A and scanner_B when finish scanning a block
        std::swap(scanner_A, scanner_B);
    }

    // Initialize the block cache whose size is sqrt(n)
    for (lint i = 0; i < block_size; ++i)
    {
        block_cache.push_back(std::vector<cell>{ static_cast<size_t>(cols) + 1 });
    }

    lint route_j_backup = cols;
    int max_gain = 0;

    // Scan each block from the last block to the first block figure out the
    // entire optimal route.
    // Time complexity of this part is O(m * n)
    for (lint i = block_beginners.size() - 1; i >= 0; --i)
    {
        block_cache[0] = block_beginners[i];
        
        // We should scan each block from the first row to the last row.
        // Time complexity of this part is O(n * sqrt(m))
        lint ii = 1;
        for (; ii < block_size; ++ii)
        {
            // We should be careful that rows of the last block may be fewer than sqrt(m),
            // which means we may exceed range of the original grid.
            // Check current position in the 
            lint grid_row = i * block_size + ii;
            if (grid_row >= rows)
            {
                break;
            }

            // Compare the accumulated value of the left neighbor and the upper neighbor.
            // Pick up the larger value, add the value to accumulated value of current cell.
            // By the way, determine the direction of movement, the direction of move is always 
            // from the cell whose accumulated value is larger.
            for (lint j = 0; j < cols; ++j)
            {
                if (block_cache[ii - 1][j + 1].acc_val > block_cache[ii][j].acc_val)
                {
                    block_cache[ii][j + 1].acc_val = block_cache[ii - 1][j + 1].acc_val + grid[grid_row][j];
                    block_cache[ii][j + 1].move_from = 'D';
                }
                else
                {
                    block_cache[ii][j + 1].acc_val = block_cache[ii][j].acc_val + grid[grid_row][j];
                    block_cache[ii][j + 1].move_from = 'R';
                }
            }
        }

        // Do not forget to extract the final gain
        if (i == block_beginners.size() - 1)
        {
            max_gain = block_cache[ii - 1][cols].acc_val;
        }

        lint route_i = ii - 1;
        lint route_j = route_j_backup;

        // Find out part of the entire optimal route in this cached block.
        // Append the newly found route to the end of previously found route.
        while (route_i >= 0 && route_j > 0)
        {
            re_route.push_back(block_cache[route_i][route_j].move_from);

            if (block_cache[route_i][route_j].move_from == 'D')
            {
                --route_i;
            }
            else
            {
                --route_j;
            }
        }

        route_j_backup = route_j;
    }

    // Remove the first cell from the route
    re_route.pop_back();

    // Reverse the route
    route.clear();
    for (auto itr = re_route.rbegin(); itr != re_route.rend(); ++itr)
    {
        route.push_back(*itr);
    }

    return max_gain;
}


