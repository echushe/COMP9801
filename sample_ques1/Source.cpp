#include <iostream>
#include <vector>
#include <limits>
#include <memory>


typedef std::vector<double> sequence;


void largest_sub_seq(const sequence & seq)
{
    double global_largest_sum = std::numeric_limits<double>::max() * (-1);
    size_t global_largest_head = 0;
    size_t global_largest_tail = 0;

    double prev_largest_sum = 0;
    size_t prev_largest_head = 0;
    size_t prev_largest_tail = 0;

    for (size_t i = 0; i < seq.size(); ++i)
    {
        double prev_plus_current = prev_largest_sum + seq[i];
        double current_max;
        if (seq[i] > prev_plus_current)
        {
            current_max = seq[i];

            prev_largest_sum = seq[i];
            prev_largest_head = i;
            prev_largest_tail = i;
        }
        else
        {
            current_max = prev_plus_current;

            prev_largest_sum += seq[i];
            prev_largest_tail = i;
        }

        if (current_max > global_largest_sum)
        {
            global_largest_sum = current_max;
            global_largest_head = prev_largest_head;
            global_largest_tail = prev_largest_tail;
        }
    }

    for (size_t i = global_largest_head; i <= global_largest_tail; ++i)
    {
        std::cout << '\t' << seq[i];
    }

    std::cout << '\n';
}


int main()
{
    sequence seq = { 5, 1, -2, 3, 4, -1, 2 };

    largest_sub_seq(seq);

    seq = { 1, -3, 2, 1, -1 };

    largest_sub_seq(seq);

    seq = { -1, -2, -3, -4, -5, -6 };

    largest_sub_seq(seq);

    seq = { -6, -5, -4, -3, -2, -1 };

    largest_sub_seq(seq);

    seq = { 1, -3, 2, -5, 7, 6, -1, -4, 11, -23 };

    largest_sub_seq(seq);

    seq = { 1, 2, 11, 9, 2, 3, 7, 4 };

    largest_sub_seq(seq);

    return 0;
}