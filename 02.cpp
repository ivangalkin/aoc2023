#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <tuple>
#include <numeric>
#include <algorithm>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>
#include <sstream>

#define ASSERT_EQ(a, b) \
   do { __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     if (_a != _b)       \
     {                 \
       std::cout << _a << " != " << _b << std::endl; \
       assert(0);                  \
     }                  \
     }while(0)

#define myprint(arg) do { std::cout << "" #arg << " = " << arg << std::endl; } while(0)

using ll = int64_t;

namespace {

    std::map<ll, std::vector<std::vector<std::string>>> input_real{
            {1,   {{"8 green",  "4 red",    "4 blue"},   {"1 green",  "6 red",    "4 blue"},   {"7 red",    "4 green",  "1 blue"},   {"2 blue",   "8 red",    "8 green"}}},
            {2,   {{"11 green", "7 blue",   "15 red"},   {"13 red",   "6 green",  "2 blue"},   {"7 green",  "9 red",    "10 blue"},  {"5 blue",   "1 red",    "11 green"}, {"4 blue",   "18 green"},            {"4 red",    "8 blue",   "18 green"}}},
            {3, {{"7 red", "10 green", "4 blue"}, {"2 blue", "3 green", "5 red"}, {"9 red", "7 green", "3 blue"}, {"3 blue", "6 green", "18 red"}}},
            {4, {{"1 blue", "2 green", "5 red"}, {"10 red", "1 blue", "3 green"}, {"14 red"}}},
            {5, {{"16 red", "4 green", "19 blue"}, {"13 blue", "9 red"}, {"7 green", "14 red", "2 blue"}, {"5 green", "18 blue", "4 red"}, {"7 red", "2 blue",                                      "3 green"}, {"8 blue", "12 green"}}},
            {6, {{"3 blue", "8 green"}, {"4 red", "5 green"}, {"5 red", "8 blue", "5 green"}, {"8 blue", "4 green"}, {"3 red", "7 green", "2 blue"}}},
            {7,   {{"7 red",    "2 blue"},               {"5 red",    "6 green"},              {"10 red"},                           {"2 blue",   "12 red",   "2 green"},  {"4 red",    "1 blue",   "1 green"}, {"9 green",  "2 blue",   "10 red"}}},
            {8,   {{"3 red",    "7 green",  "3 blue"},   {"2 green",  "3 blue",   "3 red"},    {"3 blue",   "4 green",  "1 red"},    {"3 blue",   "3 red"},                {"2 blue",   "6 green"},             {"2 red",    "7 green",  "1 blue"}}},
            {9,   {{"5 red",    "6 green"},              {"6 red"},                            {"2 blue",   "3 green",  "9 red"},    {"6 green",  "2 blue"}}},
            {10,  {{"5 red",    "8 blue",   "5 green"},  {"15 red",   "6 green",  "7 blue"},   {"8 blue",   "6 red",    "5 green"},  {"5 green",  "2 blue"},               {"12 red",   "6 blue"},              {"6 green",  "16 red",   "6 blue"}}},
            {11,  {{"3 red",    "7 blue"},               {"2 red",    "3 blue",   "6 green"},  {"4 red",    "5 green",  "2 blue"}}},
            {12,  {{"15 green", "6 red",    "2 blue"},   {"3 red",    "8 green",  "9 blue"},   {"8 blue",   "2 red",    "7 green"},  {"5 red",    "11 green", "6 blue"}}},
            {13,  {{"1 blue"},                           {"1 green",  "6 red"},                {"8 red",    "3 blue"},               {"5 blue",   "8 red",    "2 green"}}},
            {14,  {{"4 green",  "1 blue"},               {"8 blue",   "5 green",  "1 red"},    {"2 green",  "8 blue",   "3 red"}}},
            {15,  {{"7 blue",   "9 red",    "8 green"},  {"9 green",  "12 blue",  "5 red"},    {"8 green",  "10 blue",  "2 red"}}},
            {16,  {{"1 blue",   "1 red",    "14 green"}, {"6 green",  "4 blue",   "1 red"},    {"16 blue",  "14 green"},             {"6 green",  "2 red",    "9 blue"},   {"1 red",    "1 blue"},              {"2 red",    "13 green", "7 blue"}}},
            {17,  {{"1 red",    "9 green"},              {"9 red",    "5 blue",   "2 green"},  {"2 red",    "8 green",  "5 blue"},   {"5 blue",   "1 green",  "3 red"},    {"3 green",  "5 blue"},              {"3 red",    "5 blue",   "9 green"}}},
            {18,  {{"3 blue",   "5 red",    "3 green"},  {"8 blue",   "14 green"},             {"3 blue",   "11 red"},               {"2 blue",   "10 red",   "9 green"}}},
            {19,  {{"7 green",  "8 blue",   "10 red"},   {"1 green",  "10 red",   "2 blue"},   {"6 blue",   "4 red",    "11 green"}, {"7 red",    "4 green"},              {"6 blue",   "4 red"},               {"4 green",  "2 red",    "3 blue"}}},
            {20,  {{"5 red"},                            {"16 blue",  "4 green",  "7 red"},    {"1 red",    "1 green",  "4 blue"},   {"3 blue",   "4 green",  "7 red"},    {"5 blue",   "2 red",    "3 green"}, {"17 blue",  "5 red"}}},
            {21,  {{"11 red",   "4 green",  "4 blue"},   {"11 red",   "5 blue",   "2 green"},  {"11 red",   "13 green", "2 blue"},   {"13 green", "6 red",    "5 blue"},   {"7 green",  "4 blue",   "8 red"},   {"6 red",    "8 blue",   "14 green"}}},
            {22,  {{"2 green",  "1 red",    "6 blue"},   {"3 blue",   "2 green"},              {"7 green",  "10 red"},               {"10 red",   "7 blue",   "5 green"}}},
            {23,  {{"14 green", "8 blue"},               {"2 red",    "5 green"},              {"8 red",    "16 green", "10 blue"},  {"1 green",  "7 red",    "8 blue"},   {"15 green", "5 red"},               {"15 green", "2 red",    "5 blue"}}},
            {24,  {{"4 blue",   "1 green",  "1 red"},    {"1 blue",   "8 green",  "3 red"},    {"4 red",    "9 blue",   "4 green"}}},
            {25,  {{"2 blue",   "1 green",  "3 red"},    {"2 green",  "4 red"},                {"2 green",  "1 blue"}}},
            {26,  {{"3 red",    "5 green",  "4 blue"},   {"5 green",  "8 blue"},               {"1 blue",   "3 green",  "3 red"},    {"7 blue",   "2 red"}}},
            {27,  {{"13 red",   "9 green",  "6 blue"},   {"19 blue",  "9 red",    "4 green"},  {"14 red",   "4 green",  "11 blue"},  {"5 green",  "12 blue",  "7 red"}}},
            {28,  {{"9 green",  "4 blue",   "15 red"},   {"18 blue",  "14 red",   "12 green"}, {"14 red",   "12 blue",  "3 green"},  {"6 blue",   "7 green",  "15 red"},   {"17 blue",  "6 green",  "9 red"},   {"7 red",    "12 green"}}},
            {29,  {{"17 red",   "2 blue",   "9 green"},  {"5 blue",   "15 red",   "11 green"}, {"13 red",   "3 green",  "5 blue"},   {"4 green",  "11 red",   "1 blue"},   {"5 green",  "1 blue"}}},
            {30,  {{"3 green",  "12 blue"},              {"15 red",   "2 blue",   "6 green"},  {"12 red",   "11 blue",  "10 green"}, {"9 blue",   "7 green",  "14 red"},   {"1 green",  "7 red",    "5 blue"}}},
            {31,  {{"6 green",  "7 red",    "18 blue"},  {"2 green",  "3 blue",   "10 red"},   {"9 blue",   "8 red"},                {"18 blue",  "10 green", "4 red"},    {"14 blue",  "11 red",   "10 green"}}},
            {32,  {{"7 green",  "1 red",    "5 blue"},   {"5 green",  "3 blue"},               {"6 blue",   "5 green"},              {"5 red",    "11 green", "6 blue"}}},
            {33,  {{"9 blue",   "5 red"},                {"2 blue"},                           {"6 red",    "8 blue"},               {"10 blue",  "4 green",  "6 red"},    {"2 red",    "4 green"},             {"1 red",    "6 blue",   "2 green"}}},
            {34,  {{"1 red",    "6 green"},              {"3 green",  "6 red",    "2 blue"},   {"2 red",    "2 blue",   "1 green"},  {"5 green",  "1 red",    "2 blue"}}},
            {35,  {{"7 red",    "2 green",  "4 blue"},   {"4 red",    "2 green",  "3 blue"},   {"14 green", "2 blue",   "5 red"},    {"14 green", "2 red",    "3 blue"},   {"5 green",  "2 red",    "1 blue"},  {"2 green",  "8 red",    "3 blue"}}},
            {36,  {{"7 green",  "1 red",    "1 blue"},   {"3 blue",   "6 green",  "9 red"},    {"2 blue",   "17 red"},               {"18 red",   "2 green"}}},
            {37,  {{"6 red",    "14 blue"},              {"3 green",  "2 blue"},               {"18 blue",  "6 red"},                {"3 red",    "18 blue",  "3 green"}}},
            {38,  {{"6 blue",   "8 red"},                {"9 blue",   "1 green",  "1 red"},    {"2 green",  "10 blue",  "1 red"}}},
            {39,  {{"9 red",    "2 green"},              {"7 red",    "2 blue",   "2 green"},  {"2 blue",   "1 red",    "8 green"}}},
            {40,  {{"15 green", "1 blue",   "1 red"},    {"3 blue",   "1 red",    "6 green"},  {"2 blue",   "11 green"},             {"2 blue",   "11 green"},             {"3 green",  "4 blue",   "1 red"},   {"2 blue",   "6 green"}}},
            {41,  {{"4 blue",   "9 green"},              {"11 green", "1 blue",   "7 red"},    {"1 red",    "3 blue",   "17 green"}, {"17 green", "2 red"},                {"2 blue",   "16 green", "8 red"},   {"1 blue",   "8 green",  "3 red"}}},
            {42,  {{"7 green",  "15 blue",  "2 red"},    {"1 green",  "5 blue",   "5 red"},    {"4 green",  "6 red"},                {"4 red",    "4 blue",   "1 green"},  {"1 blue",   "4 red"}}},
            {43,  {{"10 green", "6 blue",   "8 red"},    {"9 green",  "9 red",    "4 blue"},   {"6 blue",   "3 green",  "6 red"},    {"8 blue",   "16 green", "7 red"}}},
            {44,  {{"14 red",   "14 blue"},              {"11 red",   "1 blue"},               {"1 green",  "9 red",    "15 blue"},  {"1 green",  "10 red"}}},
            {45,  {{"10 blue",  "5 red"},                {"1 green",  "2 red",    "11 blue"},  {"2 blue",   "10 red",   "1 green"}}},
            {46,  {{"10 red",   "9 green",  "5 blue"},   {"9 green",  "2 red",    "5 blue"},   {"3 blue",   "14 red",   "4 green"},  {"2 red",    "1 green",  "6 blue"},   {"2 red",    "9 blue",   "4 green"}, {"5 green",  "2 blue",   "11 red"}}},
            {47,  {{"9 red",    "5 green",  "1 blue"},   {"3 red",    "1 green"},              {"8 red",    "2 blue",   "10 green"}, {"9 green",  "9 red",    "2 blue"},   {"13 green", "3 blue",   "6 red"}}},
            {48,  {{"15 blue",  "3 red",    "8 green"},  {"2 blue"},                           {"12 green", "7 blue",   "1 red"}}},
            {49,  {{"9 blue",   "3 red",    "2 green"},  {"12 green", "17 blue",  "2 red"},    {"3 green",  "1 red",    "8 blue"},   {"16 blue",  "3 green",  "3 red"}}},
            {50,  {{"17 blue",  "2 red",    "14 green"}, {"18 blue",  "12 green"},             {"13 blue",  "6 red",    "8 green"},  {"4 blue",   "6 red",    "4 green"}}},
            {51,  {{"3 blue",   "8 green",  "4 red"},    {"5 blue",   "5 green",  "4 red"},    {"2 red",    "8 blue",   "2 green"},  {"8 green",  "3 blue"},               {"9 green",  "5 blue",   "1 red"}}},
            {52,  {{"9 red",    "5 green",  "6 blue"},   {"3 red",    "8 green"},              {"2 red",    "3 blue",   "6 green"},  {"8 red",    "4 blue",   "2 green"}}},
            {53,  {{"6 green",  "13 blue"},              {"4 red",    "7 green"},              {"2 green",  "7 red"},                {"11 red",   "2 blue"},               {"12 blue",  "9 green",  "8 red"}}},
            {54,  {{"3 red",    "3 blue",   "3 green"},  {"3 green",  "2 red",    "1 blue"},   {"13 blue",  "3 green"},              {"5 red",    "4 green",  "13 blue"},  {"4 green",  "7 blue",   "9 red"}}},
            {55,  {{"15 blue",  "3 green",  "2 red"},    {"1 red",    "8 green"},              {"19 blue",  "7 green"},              {"4 green",  "19 blue"},              {"9 blue",   "7 green",  "2 red"}}},
            {56,  {{"1 blue",   "9 green",  "11 red"},   {"3 blue",   "12 green", "2 red"},    {"1 blue",   "12 green", "4 red"},    {"16 green", "3 blue",   "3 red"},    {"18 red",   "9 green"}}},
            {57,  {{"7 blue",   "6 red",    "3 green"},  {"11 red",   "5 blue",   "4 green"},  {"9 blue",   "1 green",  "5 red"}}},
            {58,  {{"17 green", "17 red",   "6 blue"},   {"10 red",   "13 blue",  "1 green"},  {"7 red",    "14 green"},             {"6 red",    "2 blue",   "8 green"},  {"13 red",   "13 blue",  "4 green"}}},
            {59,  {{"1 green",  "4 red",    "1 blue"},   {"1 red",    "1 green"},              {"1 red"},                            {"4 blue"},                           {"6 red",    "6 blue",   "1 green"}}},
            {60,  {{"7 blue",   "17 red",   "8 green"},  {"12 green", "6 red",    "8 blue"},   {"1 red",    "9 blue",   "12 green"}}},
            {61,  {{"2 green",  "15 blue",  "2 red"},    {"1 green",  "9 blue",   "12 red"},   {"12 red",   "3 green",  "19 blue"}}},
            {62,  {{"17 red",   "1 blue"},               {"5 green",  "16 blue",  "14 red"},   {"3 red",    "7 blue"},               {"8 blue",   "3 red",    "1 green"}}},
            {63,  {{"9 red",    "9 blue"},               {"10 blue",  "6 red",    "9 green"},  {"11 green", "1 blue",   "13 red"},   {"6 green",  "13 blue",  "9 red"}}},
            {64,  {{"16 blue",  "2 red"},                {"9 blue"},                           {"10 red",   "1 blue",   "4 green"}}},
            {65,  {{"1 blue",   "18 green"},             {"19 green", "1 red"},                {"10 green", "1 blue",   "1 red"}}},
            {66,  {{"12 blue",  "5 green",  "13 red"},   {"3 green",  "3 blue"},               {"1 green",  "1 blue",   "11 red"}}},
            {67,  {{"5 red",    "2 green"},              {"7 red",    "3 blue"},               {"1 green",  "8 red",    "6 blue"},   {"2 red",    "5 blue"},               {"8 red",    "6 blue"}}},
            {68,  {{"8 green",  "6 red",    "18 blue"},  {"8 green",  "6 red",    "3 blue"},   {"4 red",    "14 blue",  "11 green"}}},
            {69,  {{"6 blue",   "3 red",    "1 green"},  {"4 green",  "6 red",    "6 blue"},   {"2 green",  "13 red"},               {"9 red",    "5 blue",   "6 green"},  {"2 green",  "11 red"},              {"6 green",  "2 red",    "1 blue"}}},
            {70,  {{"7 blue",   "18 green", "12 red"},   {"17 green", "2 red",    "8 blue"},   {"17 red",   "13 green", "2 blue"},   {"1 red",    "2 green",  "7 blue"}}},
            {71,  {{"3 blue",   "1 red",    "15 green"}, {"13 green", "2 red",    "8 blue"},   {"7 green",  "12 blue"},              {"7 blue",   "12 green"},             {"7 blue",   "5 green"}}},
            {72,  {{"6 blue",   "18 red"},               {"1 blue",   "4 green",  "3 red"},    {"11 red",   "3 green"},              {"6 blue",   "5 red",    "13 green"}, {"11 green", "16 red",   "5 blue"},  {"3 green",  "5 blue"}}},
            {73,  {{"18 red",   "1 blue",   "3 green"},  {"4 blue",   "4 red",    "4 green"},  {"1 blue",   "3 red"},                {"2 red",    "1 green"}}},
            {74,  {{"5 red"},                            {"12 red",   "4 green"},              {"4 green",  "5 red"},                {"2 red",    "1 blue",   "4 green"}}},
            {75,  {{"2 red",    "2 blue",   "6 green"},  {"2 blue",   "6 green"},              {"3 green",  "1 red"}}},
            {76,  {{"6 green",  "1 blue",   "12 red"},   {"2 green",  "2 red",    "3 blue"},   {"3 green",  "10 red",   "3 blue"},   {"3 blue",   "16 red",   "11 green"}, {"15 red",   "5 blue",   "7 green"}, {"4 green",  "4 red",    "3 blue"}}},
            {77,  {{"14 green", "4 blue",   "11 red"},   {"12 blue",  "9 red",    "19 green"}, {"10 green", "4 blue"}}},
            {78,  {{"1 blue",   "11 red"},               {"1 blue",   "14 green", "4 red"},    {"7 green",  "3 blue",   "5 red"}}},
            {79,  {{"3 red",    "13 blue"},              {"14 blue",  "5 red",    "5 green"},  {"1 green",  "7 blue",   "2 red"},    {"5 green",  "13 blue",  "3 red"},    {"7 blue",   "5 red",    "2 green"}}},
            {80,  {{"2 green",  "11 blue"},              {"2 red",    "12 blue",  "1 green"},  {"11 blue",  "11 green"},             {"2 green",  "12 blue",  "1 red"}}},
            {81,  {{"8 blue",   "5 green",  "1 red"},    {"1 red",    "6 blue",   "4 green"},  {"6 green",  "10 blue"},              {"2 red",    "9 blue",   "2 green"},  {"6 blue",   "2 green"},             {"6 green",  "9 blue",   "2 red"}}},
            {82,  {{"13 red",   "12 green", "3 blue"},   {"4 blue",   "4 red",    "1 green"},  {"4 green",  "8 red",    "2 blue"},   {"7 red",    "13 green"}}},
            {83,  {{"2 green",  "8 red",    "1 blue"},   {"2 blue",   "6 red",    "8 green"},  {"5 green",  "1 blue"}}},
            {84,  {{"6 red",    "18 blue",  "5 green"},  {"3 green",  "15 blue",  "2 red"},    {"6 red",    "6 blue",   "8 green"},  {"1 red",    "4 blue",   "2 green"},  {"2 blue",   "5 green"}}},
            {85,  {{"3 red",    "11 green", "2 blue"},   {"3 blue",   "6 green"},              {"2 red",    "4 green",  "4 blue"},   {"1 blue",   "3 red",    "10 green"}, {"4 blue",   "7 green",  "4 red"}}},
            {86,  {{"7 green",  "16 blue"},              {"4 blue",   "1 green",  "7 red"},    {"6 red",    "15 green", "9 blue"},   {"7 green",  "9 red",    "2 blue"},   {"14 green", "2 blue"}}},
            {87,  {{"8 red",    "3 blue",   "8 green"},  {"3 red",    "1 blue",   "8 green"},  {"6 red",    "5 green"},              {"2 red",    "6 green",  "2 blue"},   {"6 green",  "2 red"}}},
            {88,  {{"1 blue",   "4 red",    "12 green"}, {"4 red",    "1 blue",   "14 green"}, {"1 blue",   "10 green", "4 red"},    {"1 blue",   "10 red",   "9 green"}}},
            {89,  {{"7 green",  "6 red",    "10 blue"},  {"4 red",    "5 green"},              {"2 green",  "13 blue",  "2 red"}}},
            {90,  {{"16 blue",  "2 green",  "10 red"},   {"4 green",  "7 red",    "14 blue"},  {"4 blue",   "11 green", "3 red"},    {"3 red",    "10 blue",  "3 green"}}},
            {91,  {{"7 green",  "7 red",    "4 blue"},   {"14 red",   "11 blue"},              {"16 red",   "8 green",  "15 blue"}}},
            {92,  {{"5 blue",   "12 red",   "3 green"},  {"2 blue",   "8 green",  "5 red"},    {"5 blue",   "10 green"},             {"11 green", "6 red",    "4 blue"},   {"5 red",    "4 green",  "4 blue"}}},
            {93,  {{"4 blue",   "3 green",  "5 red"},    {"7 red",    "17 blue"},              {"8 blue",   "7 green"},              {"17 blue",  "1 green"},              {"2 red",    "6 blue",   "2 green"}, {"15 blue",  "3 red",    "4 green"}}},
            {94,  {{"9 green",  "3 red",    "2 blue"},   {"3 green",  "6 red"},                {"13 green", "4 red",    "2 blue"},   {"7 green"},                          {"4 green",  "7 red"},               {"2 red",    "9 green",  "2 blue"}}},
            {95,  {{"3 green",  "11 red",   "5 blue"},   {"6 blue",   "8 green"},              {"9 green",  "6 blue"},               {"6 red",    "1 green"}}},
            {96,  {{"3 blue",   "3 green",  "10 red"},   {"2 blue",   "12 red"},               {"4 red",    "3 blue"},               {"2 green",  "3 red",    "1 blue"},   {"2 green",  "6 blue"}}},
            {97,  {{"5 blue",   "3 green",  "2 red"},    {"2 blue",   "3 green",  "5 red"},    {"12 red",   "3 blue"}}},
            {98,  {{"2 blue",   "2 red",    "9 green"},  {"4 green",  "5 blue",   "1 red"},    {"15 green", "3 red",    "9 blue"}}},
            {99,  {{"15 red",   "7 green",  "11 blue"},  {"2 blue",   "12 green", "17 red"},   {"6 red",    "3 blue",   "11 green"}, {"14 red",   "13 green", "5 blue"}}},
            {100, {{"5 green",  "17 blue",  "5 red"},    {"15 blue"},                          {"13 green", "8 red",    "3 blue"},   {"16 blue",  "15 green", "8 red"},    {"16 green", "2 blue",   "3 red"}}},
    };

    decltype(input_real) input_test;
//    auto &input = input_test;
    auto &input = input_real;

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> result;
        std::istringstream ss(s);
        std::string item;

        while (getline(ss, item, delim)) {
            result.push_back(item);
        }

        return result;
    }
}

int main02() {
    int64_t result0 = 0;
    int64_t result1 = 0;

    for (const auto &[game_id, game_sets]: input) {
        bool possible = true;
        for (const auto &game_set: game_sets) {
            for (const auto &cubes: game_set) {
                auto cube = split(cubes, ' ');
                auto number = strtol(cube.at(0).c_str(), nullptr, 10);
                if (cube.at(1) == "red") {
                    if (number > 12) {
                        possible = false;
                        break;
                    }
                } else if (cube.at(1) == "green") {
                    if (number > 13) {
                        possible = false;
                        break;
                    }
                } else if (cube.at(1) == "blue") {
                    if (number > 14) {
                        possible = false;
                        break;
                    }
                }
            }
            if (!possible) {
                break;
            }
        }
        if (possible) {
            result0 += game_id;
        }
    }

    for (const auto &[game_id, game_sets]: input) {
        bool possible = true;
        ll max_red = -1;
        ll max_green = -1;
        ll max_blue = -1;
        for (const auto &game_set: game_sets) {
            for (const auto &cubes: game_set) {
                auto cube = split(cubes, ' ');
                auto number = strtol(cube.at(0).c_str(), nullptr, 10);
                if (cube.at(1) == "red") {
                    max_red = std::max<ll>(max_red, number);
                } else if (cube.at(1) == "green") {
                    max_green = std::max<ll>(max_green, number);
                } else if (cube.at(1) == "blue") {
                    max_blue = std::max<ll>(max_blue, number);
                }
            }
        }

        ll power = max_red * max_blue * max_green;
        result1 += power;
    }


    myprint(result0);
    myprint(result1);
    return 0;
}
