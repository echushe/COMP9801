#include "Integer.h"
#include <assert.h>
#include <random>
#include <chrono>

void basic_test_cases()
{
    std::cout << "===================== basic_test_cases ==================\n";
    Integer in1{ 54321, 10 };
    Integer in2{ -302, 10 };
    Integer in3{ in1 };

    std::cout << in1.to_raw_int() << "\n";
    std::cout << in2.to_raw_int() << "\n";
    std::cout << in3.to_raw_int() << "\n";

    in1 <<= 6;
    in3 >>= 3;

    std::cout << in1.to_raw_int() << "\n";
    std::cout << in3.to_raw_int() << "\n";

    Integer in4{ 1, 2 };

    for (lint i = 0; i < 25; ++i)
    {
        std::cout << in4.to_raw_int() << "\n";
        in4 <<= 1;
    }

    Integer in5{ -32768, 2 };
    for (lint i = 0; i < 25; ++i)
    {
        std::cout << in5.to_raw_int() << "\n";
        in5 >>= 1;
    }
}


void constructor_assignment_test_cases()
{
    std::cout << "===================== constructor_assignment_test_cases ==================\n";

    std::cout << "------------ test copies -------------\n";
    Integer in1{ 1983, 120 };
    Integer in2{ -1983, 12 };
    Integer in3{ in1 };
    Integer in22;
    in22 = in2;

    std::cout << in1.to_raw_int() << "\n";
    std::cout << in2.to_raw_int() << "\n";
    std::cout << in3.to_raw_int() << "\n";
    std::cout << in22.to_raw_int() << "\n";

    std::cout << "------------ test moves -------------\n";
    Integer in4{ std::move(in1) };
    Integer in5;
    in5 = std::move(in3);

    std::cout << in1.to_raw_int() << "\n";
    std::cout << in3.to_raw_int() << "\n";
    std::cout << in4.to_raw_int() << "\n";
    std::cout << in5.to_raw_int() << "\n";
}


void shift_test_cases()
{
    std::default_random_engine label_rand{ 120 };
    std::uniform_int_distribution<unsigned int> uniform_distribution{ 0,  std::numeric_limits<unsigned int>::max() };

    for (lint i = 0; i < 1000; ++i)
    {
        lint sign = rand() % 2;
        lint shift = rand() % 100;

        if (sign)
        {
            shift *= -1;
        }

        unsigned int input = uniform_distribution(label_rand);
        std::cout << "input: " << input << " left shift: " << shift << "\n";
        Integer in{ input, 4 };
        input <<= shift;
        in <<= shift;

        std::cout << "expected: " << input << " ouput: " << in.to_raw_int() << "\n";
        assert(input == in.to_raw_int());
    }

    for (lint i = 0; i < 1000; ++i)
    {
        lint sign = rand() % 2;
        lint shift = rand() % 100;

        if (sign)
        {
            shift *= -1;
        }

        unsigned int input = uniform_distribution(label_rand);
        std::cout << "input: " << input << " right shift: " << shift << "\n";
        Integer in{ input, 4 };
        input >>= shift;
        in >>= shift;

        std::cout << "expected: " << input << " ouput: " << in.to_raw_int() << "\n";
        assert(input == in.to_raw_int());
    }
}


void sum_sub_test_cases()
{
    std::default_random_engine label_rand{ 120 };
    std::uniform_int_distribution<int> uniform_distribution{ std::numeric_limits<int>::min(),  std::numeric_limits<int>::max() };

    for (lint i = 0; i < 1000; ++i)
    {
        lint left = uniform_distribution(label_rand);
        lint right = uniform_distribution(label_rand);

        std::cout << "left: " << left << " right: " << right << "\n";
        Integer out = Integer{ left, 4 } + Integer{ right, 4 };
        lint expect = left + right;

        std::cout << "expected sum: " << expect << " ouput: " << out.to_raw_int() << " " << out << "\n";
        assert(expect == out.to_raw_int());
    }

    for (lint i = 0; i < 1000; ++i)
    {
        lint left = uniform_distribution(label_rand);
        lint right = uniform_distribution(label_rand);

        std::cout << "left: " << left << " right: " << right << "\n";
        Integer out = Integer{ left, 4 } - Integer{ right, 4 };
        lint expect = left - right;

        std::cout << "expected sub: " << expect << " ouput: " << out.to_raw_int() << " " << out << "\n";
        assert(expect == out.to_raw_int());
    }

    for (lint i = 0; i < 1000; ++i)
    {
        lint left = uniform_distribution(label_rand);
        lint right = uniform_distribution(label_rand);

        std::cout << "left: " << left << " right: " << right << "\n";
        Integer out{ left, 4 };
        out += Integer{ right, 4 };
        
        lint expect = left + right;

        std::cout << "expected sum: " << expect << " ouput: " << out.to_raw_int() << " " << out << "\n";
        assert(expect == out.to_raw_int());
    }

    for (lint i = 0; i < 1000; ++i)
    {
        lint left = uniform_distribution(label_rand);
        lint right = uniform_distribution(label_rand);

        std::cout << "left: " << left << " right: " << right << "\n";
        Integer out{ left, 4 };
        out -= Integer{ right, 4 };
        
        lint expect = left - right;

        std::cout << "expected sub: " << expect << " ouput: " << out.to_raw_int() << " " << out << "\n";
        assert(expect == out.to_raw_int());
    }

    for (lint i = 0; i < 1000; ++i)
    {
        lint left = uniform_distribution(label_rand);
        lint right = uniform_distribution(label_rand);

        std::cout << "left: " << left << " right: " << right << "\n";
        Integer out{ left, 4 };
        out += right;

        lint expect = left + right;

        std::cout << "expected sum: " << expect << " ouput: " << out.to_raw_int() << " " << out << "\n";
        assert(expect == out.to_raw_int());
    }

    for (lint i = 0; i < 1000; ++i)
    {
        lint left = uniform_distribution(label_rand);
        lint right = uniform_distribution(label_rand);

        std::cout << "left: " << left << " right: " << right << "\n";
        Integer out{ left, 4 };
        out -= right;

        lint expect = left - right;

        std::cout << "expected sub: " << expect << " ouput: " << out.to_raw_int() << " " << out << "\n";
        assert(expect == out.to_raw_int());
    }
}



void plus_plus_sub_sub_cases()
{
    Integer to_plus{ -10000, 2 };
    for (lint i = 0; i < 80000; ++i)
    {
        ++to_plus;
        std::cout << "to_plus: " << to_plus.to_raw_int() << "\n";
    }

    Integer to_sub{ 10000, 2 };
    for (lint i = 80000; i >= 0; --i)
    {
        --to_sub;
        std::cout << "to_sub: " << to_sub.to_raw_int() << "\n";
    }
}



void comparison_cases()
{
    std::default_random_engine label_rand{ 120 };
    std::normal_distribution<double> normal_distribution(0, 10);

    for (lint i = 0; i < 5000; ++i)
    {
        lint left = static_cast<lint>(normal_distribution(label_rand));
        lint right = static_cast<lint>(normal_distribution(label_rand));

        std::cout << "left: " << left << " right: " << right << "\n";
        bool out = (Integer{ left } == Integer{ right });
        bool expect = (left == right);

        std::cout << "expected equals: " << expect << " ouput: " << out << "\n";
        assert(expect == out);
    }

    for (lint i = 0; i < 5000; ++i)
    {
        lint left = static_cast<lint>(normal_distribution(label_rand));
        lint right = static_cast<lint>(normal_distribution(label_rand));

        std::cout << "left: " << left << " right: " << right << "\n";
        bool out = (Integer{ left } < Integer{ right });
        bool expect = (left < right);

        std::cout << "expected less: " << expect << " ouput: " << out << "\n";
        assert(expect == out);
    }

    for (lint i = 0; i < 5000; ++i)
    {
        lint left = static_cast<lint>(normal_distribution(label_rand));
        lint right = static_cast<lint>(normal_distribution(label_rand));

        std::cout << "left: " << left << " right: " << right << "\n";
        bool out = (Integer{ left } > Integer{ right });
        bool expect = (left > right);

        std::cout << "expected more: " << expect << " ouput: " << out << "\n";
        assert(expect == out);
    }
}


void test_integer_resize()
{
    Integer int1{ 60000, 2 };

    std::cout << "int1: " << int1.to_raw_int() << " binary: " << int1 << " size: " << int1.size() << "\n";
    int1 = 100000;

    std::cout << "int1: " << int1.to_raw_int() << " binary: " << int1 << " size: " << int1.size() << "\n";
    int1.resize(16);

    std::cout << "int1: " << int1.to_raw_int() << " binary: " << int1 << " size: " << int1.size() << "\n";
    int1.resize(2);

    std::cout << "int1: " << int1.to_raw_int() << " binary: " << int1 << " size: " << int1.size() << "\n";

    Integer int2{ 8000, 4 };

    try
    {
        Integer int3 = int1 + int2;
        std::cout << "int3: " << int3.to_raw_int() << " binary: " << int3 << " size: " << int3.size() << "\n";
    }
    catch (std::invalid_argument & ex)
    {
        std::cout << ex.what() << "\n";
    }

    try
    {
        Integer int3 = int1 - int2;
        std::cout << "int3: " << int3.to_raw_int() << " binary: " << int3 << " size: " << int3.size() << "\n";
    }
    catch (std::invalid_argument & ex)
    {
        std::cout << ex.what() << "\n";
    }

    Integer int3{ 200, 1 }, int4{ 200, 1 };
    Integer int5 = int3 + int4;

    std::cout << "int5: " << int5.to_raw_int() << " binary: " << int5 << " size: " << int5.size() << "\n";
}


void test_initegers_of_different_sizes()
{
    std::default_random_engine label_rand{ 120 };
    std::uniform_int_distribution<int> uniform_1{ std::numeric_limits<int>::min(),  std::numeric_limits<int>::max() };
    std::uniform_int_distribution<int> uniform_2{ 0,  4 };

    for (lint i = 0; i < 1000; ++i)
    {
        Integer left{ uniform_1(label_rand), uniform_2(label_rand) };
        Integer right{ uniform_1(label_rand), uniform_2(label_rand) };
        lint l = left.to_raw_int();
        lint r = right.to_raw_int();

        lint expected = l + r;
        Integer out = left + right;

        std::cout << "left: " << left.to_raw_int() << " binary: " << left << " size: " << left.size() << "\n";
        std::cout << "right: " << right.to_raw_int() << " binary: " << right << " size: " << right.size() << "\n";
        std::cout << "expected: " << expected << " out: " << out << "\n";

        assert(expected == out);
    }

    for (lint i = 0; i < 1000; ++i)
    {
        Integer left{ uniform_1(label_rand), uniform_2(label_rand) };
        Integer right{ uniform_1(label_rand), uniform_2(label_rand) };
        lint l = left.to_raw_int();
        lint r = right.to_raw_int();

        lint expected = l - r;
        Integer out = left - right;

        std::cout << "left: " << left.to_raw_int() << " binary: " << left << " size: " << left.size() << "\n";
        std::cout << "right: " << right.to_raw_int() << " binary: " << right << " size: " << right.size() << "\n";
        std::cout << "expected: " << expected << " out: " << out << "\n";

        assert(expected == out);
    }

    for (lint i = 0; i < 1000; ++i)
    {
        Integer left{ uniform_1(label_rand), uniform_2(label_rand) };
        Integer right{ uniform_1(label_rand), uniform_2(label_rand) };
        lint l = left.to_raw_int();
        lint r = right.to_raw_int();

        bool expected = (l > r);
        bool out = left > right;

        std::cout << "left: " << left.to_raw_int() << " binary: " << left << " size: " << left.size() << "\n";
        std::cout << "right: " << right.to_raw_int() << " binary: " << right << " size: " << right.size() << "\n";
        std::cout << "expected: " << expected << " out: " << out << "\n";

        assert(expected == out);
    }
}



void test_multiplications()
{
    Integer int1{ 100, 2 };
    Integer int2{ 100, 2 };
    Integer int3 = int1 * int2;
    std::cout << "int3: " << int3.to_raw_int() << " binary: " << int3 << " size: " << int3.size() << "\n";

    int1 = Integer{ 256, 2 };
    int2 = Integer{ 1, 2 };
    int3 = int1 * int2;
    std::cout << "int3: " << int3.to_raw_int() << " binary: " << int3 << " size: " << int3.size() << "\n";

    std::default_random_engine label_rand{ 120 };
    std::uniform_int_distribution<int> uniform_1{ std::numeric_limits<int>::min(),  std::numeric_limits<int>::max() };
    std::uniform_int_distribution<int> uniform_2{ 0,  3 };

    for (lint i = 0; i < 1000; ++i)
    {
        Integer left{ uniform_1(label_rand), uniform_2(label_rand) };
        Integer right{ uniform_1(label_rand), uniform_2(label_rand) };
        lint l = left.to_raw_int();
        lint r = right.to_raw_int();

        lint expected = l * r;
        Integer out = left * right;

        std::cout << "left: " << left.to_raw_int() << " binary: " << left << " size: " << left.size() << "\n";
        std::cout << "right: " << right.to_raw_int() << " binary: " << right << " size: " << right.size() << "\n";
        std::cout << "expected: " << expected << " out: " << out.to_raw_int() << "\n";

        assert(expected == out);
    }
}


using namespace std::chrono;

void test_multiplications_time_complexity()
{

    for (lint step = 1; step < 11; ++step)
    {

        std::vector<byte> data;
        for (lint i = 0; i < step * 100; ++i)
        {
            data.push_back(255);
        }

        Integer long_int_a{ data, 1 };
        Integer long_int_b{ data, -1 };

        Integer out = long_int_a + long_int_b;

        //std::cout << "out: " << out.to_raw_int() << " binary: " << out << " size: " << out.size() << "\n";
        auto time1 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
            ).count();

        out = long_int_a * long_int_b;
        //std::cout << "out: " << out.to_raw_int() << " binary: " << out << " size: " << out.size() << "\n";

        auto time2 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
            ).count();

        std::cout << "============== Time used: " << time2 - time1 << " ===============\n";
    }


}



int main()
{
    //basic_test_cases();
    //constructor_assignment_test_cases();
    //shift_test_cases();
    //sum_sub_test_cases();
    //plus_plus_sub_sub_cases();
    //comparison_cases();
    //test_integer_resize();

    //test_initegers_of_different_sizes();
    //test_multiplications();

    test_multiplications_time_complexity();

    return 0;
}