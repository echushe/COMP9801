#include <iostream>
#include <vector>
#include <limits>
#include <assert.h>

typedef long long int lint;

struct cut_cache
{
    lint cost;
    lint cut_pos;

    cut_cache(lint co, lint c)
        : cost{ co }, cut_pos{ c }
    {}

    cut_cache()
        : cost{ 0 }, cut_pos{ 0 }
    {}
};

void min_cost_cut(lint len, std::vector<cut_cache> & cache)
{
    lint current_cost = len;

    lint min = std::numeric_limits<lint>::max();
    lint half = len / 2;

    lint cut_pos;

    for (lint i = 1; i <= half; ++i)
    {
        lint cost_sum = cache[i - 1].cost + cache[len - i - 1].cost;

        if (cost_sum < min)
        {
            min = cost_sum;
            cut_pos = i;
        }
    }

    cache.push_back(cut_cache{ min + len, cut_pos });

}


std::vector<cut_cache> generate_cut_cost_cache(lint len)
{
    std::vector<cut_cache> cache{ 1 };

    for (lint i = 2; i <= len; ++i)
    {
        min_cost_cut(i, cache);
    }

    return cache;
}


void optimal_solution(const std::vector<cut_cache> & cache, lint len, lint start, std::vector<lint> & out)
{
    if (1 == len)
    {
        return;
    }

    lint index = len - 1;
    lint left_len = cache[index].cut_pos;
    lint right_len = len - cache[index].cut_pos;

    out.push_back(start + cache[index].cut_pos);

    optimal_solution(cache, left_len, start, out);
    optimal_solution(cache, right_len, start + cache[index].cut_pos, out);
}



std::vector<lint> generate_middle_cut_cache(lint len)
{
    std::vector<lint> cache;

    for (lint i = 1; i <= len; ++i)
    {
        if (1 == i)
        {
            cache.push_back(0);
        }
        else
        {
            cache.push_back(i + cache[i / 2 - 1] + cache[i - i / 2 - 1]);
        }
    }

    return cache;
}



int main()
{
    for (lint n = 2; n <= 25; ++n)
    {
        std::vector<cut_cache> cache1 = generate_cut_cost_cache(n);
        std::vector<lint> cache2 = generate_middle_cut_cache(n);

        std::vector<lint> out;
        optimal_solution(cache1, n, 0, out);

        std::cout << "\t";
        for (lint i : out)
        {
            std::cout << "\t" << i;
        }

        assert(cache1[n - 1].cost == cache2[n - 1]);

        std::cout << '\n' << cache1[n - 1].cost << '\t' << cache2[n - 1] << '\n';
    }
}