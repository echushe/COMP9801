#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <strstream>
#include <memory>

typedef long long int lint;

struct dp_cache
{
    char op;
    lint op_pos;
    lint cost;

    dp_cache(char o, lint pos, lint c)
        : op{ o }, op_pos{ pos }, cost{ c }
    {}

    dp_cache() : op{ 0 }, op_pos{ 0 }, cost{ 0 } {}
};


void generate_max_and_min_cache(
    lint head,
    lint tail,
    const std::vector<lint> & number_array,
    std::vector<std::vector<dp_cache>> & max_cache,
    std::vector<std::vector<dp_cache>> & min_cache)
{
    if (head == tail)
    {
        max_cache[head][tail].cost = number_array[head];
        max_cache[head][tail].op_pos = head;
        max_cache[head][tail].op = 0;
        return;
    }

    lint max = std::numeric_limits<lint>::min();
    lint min = std::numeric_limits<lint>::max();


    for (lint k = head; k < tail; ++k)
    {
        lint max_sum = max_cache[head][k].cost + max_cache[k + 1][tail].cost;
        lint min_sum = min_cache[head][k].cost + min_cache[k + 1][tail].cost;

        lint max_sub = max_cache[head][k].cost - min_cache[k + 1][tail].cost;
        lint min_sub = min_cache[head][k].cost - max_cache[k + 1][tail].cost;

        lint max_mul = std::max(
            max_cache[head][k].cost * max_cache[k + 1][tail].cost,
            min_cache[head][k].cost * min_cache[k + 1][tail].cost);

        lint min_mul = std::min(
            max_cache[head][k].cost * max_cache[k + 1][tail].cost,
            min_cache[head][k].cost * min_cache[k + 1][tail].cost);

        if (max_sum > max)
        {
            max = max_sum;
            max_cache[head][tail].cost = max;
            max_cache[head][tail].op = '+';
            max_cache[head][tail].op_pos = k;
        }

        if (max_sub > max)
        {
            max = max_sub;
            max_cache[head][tail].cost = max;
            max_cache[head][tail].op = '-';
            max_cache[head][tail].op_pos = k;
        }

        if (max_mul > max)
        {
            max = max_mul;
            max_cache[head][tail].cost = max;
            max_cache[head][tail].op = '*';
            max_cache[head][tail].op_pos = k;
        }

        if (min_sum < min)
        {
            min = min_sum;
            min_cache[head][tail].cost = min;
            min_cache[head][tail].op = '+';
            min_cache[head][tail].op_pos = k;
        }

        if (min_sub < min)
        {
            min = min_sub;
            min_cache[head][tail].cost = min;
            min_cache[head][tail].op = '-';
            min_cache[head][tail].op_pos = k;
        }

        if (min_mul < min)
        {
            min = min_mul;
            min_cache[head][tail].cost = min;
            min_cache[head][tail].op = '*';
            min_cache[head][tail].op_pos = k;
        }
    }
}


struct tree_node
{
    char op;
    lint number;
    std::shared_ptr<tree_node> left_child;
    std::shared_ptr<tree_node> right_child;

    tree_node(char o, lint n):
        op{ o }, number{ n }, left_child{ nullptr }, right_child{ nullptr }
    {}
};


std::ostream & operator << (std::ostream & out, const std::shared_ptr<tree_node> & node)
{
    if (node == nullptr)
    {
        return out;
    }

    if (node->op != 0)
    {
        out << "(";
        out << node->left_child;
        out << node->op;
        out << node->right_child;
        out << ")";
    }
    else
    {
        if (node->number < 0)
        {
            out << "(";
        }

        out << node->number;

        if (node->number < 0)
        {
            out << ")";
        }
    }

    return out;
}


void find_solution(
    lint head, lint tail,
    const std::vector<std::vector<dp_cache>> & cache,
    const std::vector<lint> & number_array,
    std::shared_ptr<tree_node> & current)
{
    if (0 == cache[head][tail].op)
    {
        current = std::make_shared<tree_node>(0, number_array[head]);
        return;
    }
    else
    {
        current = std::make_shared<tree_node>(cache[head][tail].op, 0);
    }

    find_solution(head, cache[head][tail].op_pos, cache, number_array, current->left_child);

    find_solution(cache[head][tail].op_pos + 1, tail, cache, number_array, current->right_child);
}


std::shared_ptr<tree_node> operator_max(const std::vector<lint> & number_array)
{
    std::vector<std::vector<dp_cache>> max_cache;
    std::vector<std::vector<dp_cache>> min_cache;

    for (lint i = 0; i < number_array.size(); ++i)
    {
        max_cache.push_back(std::vector<dp_cache>{ number_array.size() });
        min_cache.push_back(std::vector<dp_cache>{ number_array.size() });
    }

    for (lint size = 0; size < number_array.size(); ++size)
    {
        for (lint head = 0, tail = size; head < number_array.size() && tail < number_array.size(); ++head, ++tail)
        {
            generate_max_and_min_cache(head, tail, number_array, max_cache, min_cache);
        }
    }

    std::shared_ptr<tree_node> solution_root;
    find_solution(0, number_array.size() - 1, max_cache, number_array, solution_root);

    return solution_root;
}

int main()
{
    const std::vector<lint> number_array = { -9, -8, 7, 6, 5, 4, -3, 2, 1, 0 };

    std::cout << operator_max(number_array) << "\n";
}