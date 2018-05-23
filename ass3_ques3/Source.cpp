#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


struct table_grid
{
    int val;
    bool matched;

    int matches_from_left;

    table_grid()
        :
        val{ 0 }, matched{ false }, matches_from_left{ 0 } {}

    table_grid(int v, bool m)
        : 
        val{ v }, matched{ m }, matches_from_left{ 0 } {}

};


// We use the Dynamic Programming method to solve the match occurrence problem.
// Time complexity of this algorithm is O(m * n) where m is size of sequence A,
// n is size of sequence B.
int find_match_occurrences(const std::string & A, const std::string & B)
{ 
    // Create a 2D table to cache data of the algorithm
    // rows == A.size() + 1, cols == B.size() + 1
    // All values in this table are initialized as zero
    std::vector<std::vector<table_grid>> table;

    // Time complexity of initializtion of this table is O(m * n)
    for (int i = 0; i <= A.size(); ++i)
    {
        table.push_back(std::vector<table_grid>{});

        for (int j = 0; j <= B.size(); ++j)
        {
            table[i].push_back(table_grid{});
        }
    }

    // Traverse the table (except the first row and the first column).
    // Time complexity of this part is O(m * n)
    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = 0; j < B.size(); ++j)
        {
            if (table[i + 1][j].matched && table[i + 1][j].val == i + 1)
            {
                // Update matches_from_left if the left neighbor is somewhere
                // a letter is matched.
                // Stay cautious that value of the left neighbor should be 
                // no less than row index plus one.
                table[i + 1][j + 1].matches_from_left = 
                    table[i + 1][j].matches_from_left + 
                    std::max(1, table[i][j].matches_from_left);
            }
            else
            {
                // Just copy matches_from_left from the left neighbor
                table[i + 1][j + 1].matches_from_left = table[i + 1][j].matches_from_left;
            }

            if (A[i] == B[j])
            {
                // If a letter matches here, value of this grid is value of
                // the upper-left neighbor plus one.
                table[i + 1][j + 1].val = table[i][j].val + 1;
                // Set true flag of match
                table[i + 1][j + 1].matched = true;
            }
            else
            {
                // If there is no match here, choose the max value between
                // left neighbor and upper left neighbor
                table[i + 1][j + 1].val = std::max(table[i + 1][j].val, table[i][j + 1].val);
            }
        }
    }


    for (int i = 0; i <= A.size(); ++i)
    {
        for (int j = 0; j <= B.size(); ++j)
        {
            std::cout << table[i][j].val << ' ' << 
                table[i][j].matches_from_left << ' ' << table[i][j].matched << "    ";
        }
        std::cout << '\n';
    }


    // Sum matches_from_up_left of the last row
    // Time complexity: O(n)
    for (int j = B.size(); j > 0; --j)
    {
        if (table[A.size()][j].matched && table[A.size()][j].val == A.size())
        {
            return table[A.size()][j].matches_from_left + 
                std::max(1, table[A.size() - 1][j].matches_from_left);
        }
    }

    return 0;
}



int main(int argc, char* argv[])
{
    /*
    std::string A{ "abc" };
    std::string B{ "aaaaaaaabbbbbbbbcccccccc" };

    std::cout << find_match_occurrences(A, B) << '\n';
    
    A = "abc";
    B = "cakbjbcbmcabca";
    */

    std::cout << find_match_occurrences(argv[1], argv[2]) << '\n';

    return 0;
}