#include <iostream>
#include <vector>
#include <memory>

// This algorithm costs O(n) time
int get_max_sum_non_adjacent(const std::vector<int> & input)
{
    // Initialize the inclusive sum.
    // "Inclusive sum" means it is the "sum" of elements that
    // includes the left neighbour of current element.
    int incl_sum = input[0];

    // Intialize the exclusive sum.
    // "Exclusive sum" means it is the "sum" of elements that
    // does not include the left neighbour of current element.
    int excl_sum = 0;

    // Go through each element of this array.
    // We should start with the second element of this array.
    // Index of the second element is 1 (The first is 0).
    for (int i = 1; i < input.size(); ++i)
    {
        // Back up the inclusive sum
        int old_incl_sum = incl_sum;

        // The new inclusive sum is equal to exclusive sum plus current element
        incl_sum = excl_sum + input[i];

        // Compare the old inclusive sum with the exclusive sum and pick up
        // the large one as the new exclusive sum
        if (old_incl_sum > excl_sum)
        {
            excl_sum = old_incl_sum;
        }
    }

    // Return the larger one of incl_sum and excl_sum
    if (incl_sum > excl_sum)
    {
        return incl_sum;
    }
    else
    {
        return excl_sum;
    }
}


int main()
{
    std::vector<int> input{ 5, 1, 15, 2, 4, 7, 9, -1, 0, 19, 6 };
    std::vector<int> input2{ 80, 0, 90, 1, 78, 2, 3, 77 };

    int out = get_max_sum_non_adjacent(input2);
    std::cout << out;
}