#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct customer;
struct couple;
typedef std::unordered_map<std::string, customer> customer_map;
typedef std::unordered_map<std::string, couple> couple_map;
typedef std::unordered_map<std::string, int> ranking_map;

struct customer
{
    bool gender;
    std::string name;

    ranking_map rankings;

    customer(bool gd, const std::string& n)
        : gender{gd}, name{n}
    {}

    customer() {}
};

struct couple
{
    std::string man;
    std::string woman;

    couple(const std::string& m, const std::string& w)
        : man{m}, woman{w}
    {}

    couple() {}
};
