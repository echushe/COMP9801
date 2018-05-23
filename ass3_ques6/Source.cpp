#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

typedef long long int lint;

// Definition of a cell in dynamic programming cache
struct cell
{
    // Accumulative number of different rides
    int rides;
    // Flag showing of this cell is valid or not
    bool valid;
    // Showing id of previous ride
    // If previous ride is smaller than current ride, ++rides
    // If previous ride is equal to current ride, rides stays what it is
    int prev_ride_id;

    // Validity of this Cell is invalid by default
    // Prev_ride_id is -1 by default
    cell() : rides{ 0 }, valid{ false }, prev_ride_id{ -1 } {}

    cell(int r, bool v) : rides{ r }, valid{ v }, prev_ride_id{ -1 } {}
};

// A turple of <cost, deposit>
struct c_d
{
    int cost;
    int deposit;

    c_d() : cost{ 0 }, deposit{ 0 } {}

    c_d(int c, int d) : cost{ c }, deposit{ d } {}
};

// Compare two items via amounts of deposits
bool diff_more(const c_d & item1, const c_d & item2)
{
    if (item1.deposit > item2.deposit)
    {
        return true;
    }

    return false;
}

// Main entrance of this algorithm
// Time complexity of this algorithm is O(n * log(n) + n * T)
int max_different_rides(int T, const std::vector<int> & costs, const std::vector<int> & deposits)
{
    // Cache in 2D table (T * n) mode for dynamic programming
    std::vector<std::vector<cell>> DP;
    // List of <cost, deposit> turples
    std::vector<c_d> cd_list;
    // Number of all available rides
    lint all_rides = costs.size();

    // Initialization of <cost, deposit> turples
    for (lint i = 0; i < all_rides; ++i)
    {
        cd_list.push_back(c_d{ costs[i], deposits[i] });
    }

    // Sort <cost, deposit> turples in non-increase order of deposit
    // Time complexity: O(n * log(n))
    std::sort(cd_list.begin(), cd_list.end(), diff_more);

    // Initialization of 2D cache (T * n)
    for (lint j = 0; j <= T; ++j)
    {
        DP.push_back(std::vector<cell>{costs.size()});
    }

    int max_ride = 0;

    // Begins with the top-left corner and finish with bottom-right corner of this table.
    // Row index i of this table represents how much money you have spent on rides.
    // For example, if i == 12, it means you have spent 12 on rides and you have T - 12 money left.
    for (lint i = 0; i <= T; ++i)
    {
        for (lint j = 0; j < all_rides; ++j)
        {
            bool cell_valid = false;
            if (i == 0)
                // First row of this table are all of zero rides
            {
                DP[i][j].prev_ride_id = -1;
                DP[i][j].valid = true;
                cell_valid = true;
            }
            else if (DP[i][j].valid)
            {
                if (j > 0 && DP[i][j - 1].valid)
                    // If this cell is already valid, check whether the left neighbor is
                    // equal to or larger than the current one
                {
                    if (DP[i][j - 1].rides >= DP[i][j].rides)
                        // If the left one is larger, copy rides and prev_ride_id to 
                        // current cell
                    {
                        DP[i][j].rides = DP[i][j - 1].rides;
                        DP[i][j].prev_ride_id = DP[i][j - 1].prev_ride_id;
                    }
                }

                cell_valid = true;
            }
            else if (j > 0 && DP[i][j - 1].valid)
                // If current cell is invaid but the left neighbor is valid
                // copy rides and prev_ride_id to current cell, and make current
                // cell valid.
            {
                DP[i][j].rides = DP[i][j - 1].rides;
                DP[i][j].prev_ride_id = DP[i][j - 1].prev_ride_id;
                DP[i][j].valid = true;

                cell_valid = true;
            }

            if (cell_valid)
            {
                if (DP[i][j].rides > max_ride)
                    // Always keep an eye on the max_ride
                {
                    max_ride = DP[i][j].rides;
                }

                if (i + cd_list[j].cost + cd_list[j].deposit <= T)
                    // (T - i - cost - deposit) shoule be >= 0.
                    // i is money you have spent.
                    // cd_list[j].cost is cost of the j-th ride.
                    // cd_list[j].deposit is deposit of the j-th ride.
                {
                    if (j > DP[i][j].prev_ride_id)
                        // Plus number of rides only when current ride is different
                        // from the previous ride.
                    {
                        DP[i + cd_list[j].cost][j].rides = DP[i][j].rides + 1;
                    }
                    else // Number of rides stays the same because we only count
                        // number of different rides.
                    {
                        DP[i + cd_list[j].cost][j].rides = DP[i][j].rides;
                    }

                    DP[i + cd_list[j].cost][j].prev_ride_id = j;
                    DP[i + cd_list[j].cost][j].valid = true;
                }
            }
        }
    }

    std::cout << "costs:\t";
    for (int cost : costs)
    {
        std::cout << cost << "\t";
    }
    std::cout << "\ndpsts:\t";
    for (int deposit : deposits)
    {
        std::cout << deposit << "\t";
    }
    std::cout << "\n";

    for (lint i = 0; i <= T; ++i)
    {
        for (lint j = -1; j < all_rides; ++j)
        {
            if (j == -1)
            {
                std::cout << i << "\t";
            }
            else if (DP[i][j].valid)
            {
                std::cout << DP[i][j].rides << "\t";
            }
            else
            {
                std::cout << "--\t";
            }
        }
        std::cout << "\n";
    }

    return max_ride;
}

int main(int argc, char* argv[])
{
    std::vector<int> costs{ 9, 3, 2, 1, 2, 4, 6, 7 };
    std::vector<int> deposits{ 8, 7, 6, 5, 4, 3, 2, 1 };
    std::cout << "Max different rides: " << max_different_rides(std::stoi(argv[1]), costs, deposits) << "\n";
    return 0;
}