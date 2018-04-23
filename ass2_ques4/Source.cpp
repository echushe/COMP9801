#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// This struct stores:
// 1. index of the item
// 2. difference (no less than zero) of the prices between A and B
// 3. ID of the person who pays more than the other person
struct Item
{
    int index;
    int price_diff;
    char who_pays_more;

    Item() : index{ 0 }, price_diff{ 0 }, who_pays_more{ 'A' } {}

    Item(int i, int diff, char who)
        : index{ i }, price_diff{ diff }, who_pays_more{ who }
    {}
};

// Compare two items via price differences
bool diff_more(const Item & item1, const Item & item2)
{
    if (item1.price_diff > item2.price_diff)
    {
        return true;
    }

    return false;
}

// Main entrance of this algorithm.
// Time complexity is O(N * log(N))
std::map<int, char> maximize(int N, int * a, int * b, int A_limit, int B_limit)
{
    // Stores all the items including price differences and
    // which person pays more than the other person
    std::vector<Item> items;

    // Iterate all the items
    for (int i = 0; i < N; ++i)
    {
        if (a[i] >= b[i])
        {
            // Insert the item for which A pays more than B (or equals) with
            // price difference
            items.push_back(Item{ i, a[i] - b[i], 'A' });
        }
        else
        {
            // Insert the item for which B pays more than A with
            // price difference
            items.push_back(Item{ i, b[i] - a[i], 'B' });
        }
    }

    // Sort all the items in non-increase order of price difference,
    // time complexity is O(N * log (N)).
    std::sort(items.begin(), items.end(), diff_more);

    int a_items = 0;
    int b_items = 0;

    std::map<int, char> result;

    // Iterate all the items and decide whether to sell this item to A or B.
    // Time complexity of this "for" loop is O(N)
    // If you want elements in the result to be sorted, it would be O(N * log(N))
    for (Item & item : items)
    {
        if (item.who_pays_more == 'A')
        {
            if (a_items < A_limit)
            {
                // Let A buy this item
                result.insert({ item.index, 'A' });
                ++a_items;
            }
            else
            {
                // A's shopping cart is full even though A bids higher.
                // So we have to sell this item to B.
                result.insert({ item.index, 'B' });
                ++b_items;
            }
        }
        else
        {
            if (b_items < B_limit)
            {
                // Let B buy this item
                result.insert({ item.index, 'B' });
                ++b_items;
            }
            else
            {
                // B's shopping cart is full even though B bids higher.
                // So we have to sell this item to A.
                result.insert({ item.index, 'A' });
                ++a_items;
            }
        }
    }

    return result;
}


int main()
{
    int N = 6; int A = 3; int B = 4;

    int a[6] = { 5, 7, 2, 4, 8, 3 };
    int b[6] = { 3, 2, 9, 2, 2, 4 };

    auto ret = maximize(N, a, b, A, B);

    for (auto & pair : ret)
    {
        std::cout << "( " << pair.first << "\t" << pair.second << " )\n";
    }

    return 0;
}

