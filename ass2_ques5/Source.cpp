
// "The shortest leader's height should be no less than T" is exactly
// the same as "all leaders height should be no less than T".
#include <iostream>
#include <vector>
#include <algorithm>

// Find leaders from array of giants using greedy method.
// Time complexity of this function is O(N)
std::vector<size_t> find_leaders(const std::vector<int> & giants, int K, int T)
{
    // Container of leaders
    std::vector<size_t> leaders;

    size_t i = 0;

    while (i < giants.size())
    {
        // Iterate each giant in the array
        // Stop the iteration if there is a giant whose height is not less than T
        for (; i < giants.size() && giants[i] < T; ++i);

        // If the index exceeds range of the array, stop the while loop
        if (i >= giants.size())
        {
            break;
        }

        // Push the giant whose height is not less than T into the container of leaders
        leaders.push_back(i);
        // Jump the index so that there are at least K giants between 2 leaders
        i += K + 1;
    }

    for (auto index : leaders)
    {
        std::cout << index << ": " << giants[index] << "\t";
    }
    
    return leaders;
}

// This function simply judge if we can find at least L leaders whose height are at least T
// Slightly modify the function
// At an reference argument "ret" to this function so that we can get all the selected leaders
bool can_find_leaders(const std::vector<int> & giants, int L, int K, int T, std::vector<size_t> & ret)
{
    ret = find_leaders(giants, K, T);

    std::cout << "\n";

    // If we can find at least L leaders from the array of giants
    if (ret.size() >= L)
    {
        return true;
    }

    // If we cannot find at least L leaders from the array of giants
    return false;
}


// Use the method "Divide and Conquer" to solve the optimisation version of this problem
// Time complexity: O(N * log(N))
std::vector<size_t> find_leaders_shortest_max(const std::vector<int> & giants, int L, int K)
{
    std::vector<size_t> ret;

    // Copy the array of giants and sort them in non-decrease order of their heights
    // Time complexity of sort is N * log(N)
    std::vector<int> giants_copy = giants;
    std::sort(giants_copy.begin(), giants_copy.end());

    // tail is initialized as index of the last giant
    size_t tail = giants_copy.size() - 1;

    // head is index of the first giant
    size_t head = 0;
    
    // Figure out the answer using divide and conquer
    // Time complexity of this loop is N * log(N)
    while (tail - head > 1)
    {
        std::cout << head << "\t" << tail << "\n";

        size_t mid = (head + tail) / 2;

        // Time complexity of the search is O(N)
        if (!can_find_leaders(giants, L, K, giants_copy[mid], ret))
        {
            tail = mid;
        }
        else
        {
            head = mid;
        }
    }

    std::cout << head << "\t" << tail << "\n";

    // Check if the larger T is the answer.
    if (can_find_leaders(giants, L, K, giants_copy[tail], ret))
    {
        std::cout << tail << "\n";
        return ret;
    }
    else // If the larger T is too large, it is certain that
        // The answer is the smaller T
    {
        std::cout << head << "\n";
        return find_leaders(giants, K, giants_copy[head]);
    }
}


int main()
{
    std::vector<int> giants;
    for (int i = 0; i < 20; ++i)
    {
        giants.push_back(100 + rand() % 100);
    }

    for (int i = 0; i < giants.size(); ++i)
    {
        std::cout << i << ": " << giants[i] << "\t";
    }

    std::cout << "\n";

    auto ret = find_leaders_shortest_max(giants, 3, 4);
}