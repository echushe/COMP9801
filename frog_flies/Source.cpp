#include <iostream>
#include <vector>
#include <deque>

typedef long long int lint;

struct max
{
    int flies;
    lint prev_index;

    max(int fs, lint p_i) : flies{ fs }, prev_index{ p_i } {}
    max() : flies{ 0 }, prev_index{ -1 } {}
};


int max_flies(const std::vector<int> pads)
{
    std::vector<max> max_cache;
    for (lint i = 0; i < pads.size(); ++i)
    {
        max_cache.push_back(max{});

        if (i == 0)
        {
            max_cache[i].flies = pads[i];
            max_cache[i].prev_index = -1;
        }
        else
        {
            int max_i_3 = -1;
            int max_i_5 = -1;
            
            if (i - 3 >= 0)
            {
                max_i_3 = max_cache[i - 3].flies;
            }

            if (i - 5 >= 0)
            {
                max_i_5 = max_cache[i - 5].flies;
            }

            if (max_i_3 > max_i_5)
            {
                max_cache[i].flies = max_i_3 + pads[i];
                max_cache[i].prev_index = i - 3;
            }
            else if (max_i_5 >= 0)
            {
                max_cache[i].flies = max_i_5 + pads[i];
                max_cache[i].prev_index = i - 5;
            }
        }
    }

    int all_flies = -1;
    std::deque<lint> jumps;
    lint index = -1;
    for (lint i = max_cache.size() - 1; i >=0; --i)
    {
        if (max_cache[i].flies > all_flies)
        {
            index = i;
            all_flies = max_cache[i].flies;
        }
    }

    while (index >= 0)
    {
        jumps.push_front(index);
        index = max_cache[index].prev_index;
    }

    int sum = 0;
    for (lint index : jumps)
    {
        std::cout << '\t' << index << ":" << pads[index];
    }

    std::cout << '\n';

    return all_flies;
}


int main()
{
    std::vector<int> pads = { 1, 3, 1, 3, 6, 7, 9, 2, 1, 4, 5, 8, 3, 9, 7, 6, 2, 11 };

    std::cout << max_flies(pads) << '\n';

    pads = { 7, 6, 5 };

    std::cout << max_flies(pads) << '\n';

    pads = { 7, 7, 7, 7, 7, 7, 7, 7, 1000, 7 };

    std::cout << max_flies(pads) << '\n';

    return 0;
}