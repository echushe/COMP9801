#include "header.h"
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std::chrono;

void initialize_customers(customer_map& men, customer_map& women, int pairs)
{
    std::string name;
    pairs *= 2;

    for (int i = 0; i < pairs; ++i)
    {
        int name_len = 20; // 3 + rand() % 10;
        for (int j = 0; j < name_len; ++j)
        {
            char c = 65 + rand() % 26;
            name.push_back(c);
        }

        if (i % 2)
        {
            men.insert({ name, customer{true, name} });
        }
        else
        {
            women.insert({ name, customer{false, name} });
        }

        name = "";
    }
}


void initialize_rankings(customer_map& men, customer_map& women)
{
    std::vector<std::string> l_men;
    std::vector<std::string> l_women;

    for (auto& m_pair : men)
    {
        l_men.push_back(m_pair.first);
    }

    for (auto& w_pair : women)
    {
        l_women.push_back(w_pair.first);
    }

    int ranking = 0;
    for (auto& m_pair : men)
    {
        // Generate rankings of all women of this man
        for (auto& w : l_women)
        {
            m_pair.second.rankings.insert({ w, ranking++ });
        }

        /*
        std::sort(
            m_pair.second.rankings.begin(),
            m_pair.second.rankings.end(),
            less);
            */

        std::random_shuffle(l_women.begin(), l_women.end());
    }

    ranking = 0;
    for (auto& w_pair : women)
    {
        // generate rankings of all men of this woman
        for (auto& m : l_men)
        {
            w_pair.second.rankings.insert({ m, ranking++ });
        }

        /*
        std::sort(
            w_pair.second.rankings.begin(),
            w_pair.second.rankings.end(),
            less);
            */

        std::random_shuffle(l_men.begin(), l_men.end());
    }
}


couple_map match(const customer_map& men, const customer_map& women)
{
    customer_map free_men;
    std::vector<std::string> men_names;
    couple_map couples;

    for (auto& k_v_pair : men)
    {
        free_men.insert(k_v_pair);
        men_names.push_back(k_v_pair.first);
    }

    size_t size = free_men.size();

    auto time1 = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
        ).count();

    while (!free_men.empty())
    {
        auto free_man_itr = free_men.begin();
        customer& free_man = (*free_man_itr).second;
        
        //std::cout << "Name of thie free man: " << free_man.name << "\n";

        customer top_woman = (*(women.find((*(free_man.rankings.begin())).first))).second;

        auto couple_itr = couples.find(top_woman.name);

        if (couple_itr == couples.end())
        {
            couples.insert({ top_woman.name, couple{ free_man.name, top_woman.name } });
            free_men.erase(free_man.name);
        }
        else
        {
            customer ex_boy_friend = (*(men.find((*couple_itr).second.man))).second;
            int boy_friend_ranking = (*(top_woman.rankings.find(ex_boy_friend.name))).second;
            int free_man_ranking = (*(top_woman.rankings.find(free_man.name))).second;

            if (free_man_ranking < boy_friend_ranking)
            {
                couples.erase(top_woman.name);
                couples.insert({ top_woman.name, couple{ free_man.name, top_woman.name } });

                free_men.insert({ ex_boy_friend.name, ex_boy_friend });
                free_men.erase(free_man.name);
            }
            else
            {
                free_man.rankings.erase(top_woman.name);
            }
        }
    }

    auto time2 = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
        ).count();

    std::cout << "milliseconds to run: " << time2 - time1 << "\n";

    return couples;
}


int main()
{
    customer_map men;
    customer_map women;  

    for (int i = 1; i <= 10; ++i)
    {
        initialize_customers(men, women, i * 100);
        initialize_rankings(men, women);
        /*
        men = {
            { "A", customer{ true, "A" } },
            { "B", customer{ true, "B" } },
            { "C", customer{ true, "C" } } };

        women = {
            { "D", customer{ true, "D" } },
            { "E", customer{ true, "E" } },
            { "F", customer{ true, "F" } } };

        for (auto& kv : men)
        {
            std::cout << kv.first << "\n";
            kv.second.rankings = {
                { "D", 0 },
                { "E", 1 },
                { "F", 2 }
            };
        }

        for (auto& kv : women)
        {
            std::cout << kv.first << "\n";
            kv.second.rankings = {
                { "A", 0 },
                { "B", 1 },
                { "C", 2 }
            };
        }
        */
        auto couples = match(men, women);

        std::cout << men.size() << "\n";
        std::cout << women.size() << "\n";
        std::cout << couples.size() << "\n";

        for (const auto& k_v_pair : couples)
        {
            // std::cout << k_v_pair.second.man << " -- " << k_v_pair.second.woman << "\n";
        }

        men.clear();
        women.clear();
    }

    return 0;
}