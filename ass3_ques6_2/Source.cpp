#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>


typedef long long int lint;
// Definition of a cell in dynamic programming cache
struct cell
{
    // Accumulative amount of money needed
    int money_needed;
    // Refound which is deposit of the last ride
    int refund;

    // Default value of money_needed is infinity
    cell() : money_needed{ std::numeric_limits<int>::max() }, refund{ 0 } {}

    cell(int m, int re, int r) : money_needed{ m }, refund{ re } {}
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
bool diff_less(const c_d & item1, const c_d & item2)
{
    if (item1.deposit < item2.deposit)
    {
        return true;
    }

    return false;
}

// Main entrance of this algorithm
// Time complexity of this algorithm is O(n * n)
lint max_different_rides(int T, const std::vector<int> & costs, const std::vector<int> & deposits)
{
    // Cache in 2D table (n * n) mode for dynamic programming
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

    // Sort <cost, deposit> turples in non-decrease order of deposit
    // Time complexity: O(n * log(n))
    std::sort(cd_list.begin(), cd_list.end(), diff_less);

    // Initialization of 2D cache (n * n)
    for (lint i = 0; i <= all_rides; ++i)
    {
        DP.push_back(std::vector<cell>{costs.size()});
    }

    // Intialize the first row of 2D cache, time complexity O(n)
    // This row represents the minimum money you can spend if you can choose
    // only one ride
    for (lint j = 0; j < all_rides; ++j)
    {
        if (j == 0)
        {
            DP[0][j].money_needed = cd_list[j].cost + cd_list[j].deposit;
            DP[0][j].refund = cd_list[j].deposit;
        }
        else
        {
            int spent = cd_list[j].cost;
            int prev_spent = DP[0][j - 1].money_needed - DP[0][j - 1].refund;

            if (spent < prev_spent)
            {
                DP[0][j].money_needed = cd_list[j].cost + cd_list[j].deposit;
                DP[0][j].refund = cd_list[j].deposit;
            }
            else
            {
                DP[0][j].money_needed = DP[0][j - 1].money_needed;
                DP[0][j].refund = DP[0][j - 1].refund;
            }
        }
    }

    // Start from the second row and finish the scanning with the last row.
    // In each row we start from [row_index, row_index] to the end of each row.
    // Time complexity is O(n * n)
    for (lint i = 1; i < all_rides; ++i)
    {
        for (lint j = i; j < all_rides; ++j)
        {
            // There are two options in each step
            // Option one:
            //        Do not choose new ride, then accumulative money_needed and the
            //        last deposit will be the same as the previous step, just copy
            //        the left neighbor.
            // Option two:
            //        Choose a new ride that is current ride you can choose, combine it
            //        with all previous rides. Then calculate the value of money_needed
            //        and refund.
            //
            // Compare Option one and Option two, and choose an optimal option that:
            //        1. Costs less money
            //        2. If they cost the same amound of money, choose the one requiring
            //           less total money required (less final deposit)
            //

            int spent_if_not_choose = DP[i][j - 1].money_needed - DP[i][j - 1].refund;

            int current_ride_money_needed = cd_list[j].deposit + cd_list[j].cost;
            int current_ride_refund = cd_list[j].deposit;

            
            int spent_if_choose;
            int money_needed;
            int refund;

            if (current_ride_refund > DP[i - 1][j - 1].refund)
            {
                refund = DP[i - 1][j - 1].refund;
                money_needed = current_ride_money_needed;
                if (current_ride_refund < DP[i - 1][j - 1].money_needed)
                {
                    money_needed += DP[i - 1][j - 1].money_needed - current_ride_refund;
                }
            }
            else
            {
                refund = current_ride_refund;
                money_needed = DP[i - 1][j - 1].money_needed;
                if (DP[i - 1][j - 1].refund < current_ride_money_needed)
                {
                    money_needed += current_ride_money_needed - DP[i - 1][j - 1].refund;
                }
            }

            spent_if_choose = money_needed - refund;

            if (spent_if_choose < spent_if_not_choose)
            {
                DP[i][j].money_needed = money_needed;
                DP[i][j].refund = refund;
            }
            else if (spent_if_choose > spent_if_not_choose)
            {
                DP[i][j].money_needed = DP[i][j - 1].money_needed;
                DP[i][j].refund = DP[i][j - 1].refund;
            }
            else if (money_needed < DP[i][j - 1].money_needed)
            {
                DP[i][j].money_needed = money_needed;
                DP[i][j].refund = refund;
            }
            else
            {
                DP[i][j].money_needed = DP[i][j - 1].money_needed;
                DP[i][j].refund = DP[i][j - 1].refund;
            }
        }
    }


    std::cout << "costs:\t";
    for (auto ele : cd_list)
    {
        std::cout << ele.cost << "\t";
    }
    std::cout << "\ndpsts:\t";
    for (auto ele : cd_list)
    {
        std::cout << ele.deposit << "\t";
    }
    std::cout << "\n";

    for (lint i = 0; i < all_rides; ++i)
    {
        for (lint j = -1; j < all_rides; ++j)
        {
            if (j == -1)
            {
                std::cout << i << "\t";
            }
            else if (DP[i][j].money_needed < std::numeric_limits<int>::max())
            {
                std::cout << DP[i][j].money_needed << '/' << DP[i][j].refund << "\t";
            }
            else
            {
                std::cout << "--\t";
            }
        }
        std::cout << "\n";
    }

    // Search for the largest row where money_needed does not
    // exceed total money available in hands.
    // Time complexity: O(n * n)
    for (lint i = all_rides; i >= 0; --i)
    {
        for (lint j = all_rides - 1; j >= 0; --j)
        {
            if (DP[i][j].money_needed <= T)
            {
                return  i + 1;
            }
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    //std::vector<int> costs{ 9, 3, 2, 1, 2, 4, 6, 7 };
    //std::vector<int> deposits{ 8, 7, 6, 5, 4, 3, 2, 1 };

    std::vector<int> costs{ 3, 2, 1, 2, 4, 6 };
    std::vector<int> deposits{ 6, 5, 4, 3, 2, 1 };

    std::cout << "Max different rides: " << max_different_rides(std::stoi(argv[1]), costs, deposits) << "\n";
    return 0;
}