#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <iomanip>
#include <sstream>
#include <map>
#include <tuple>
#include <numeric>
#include <algorithm>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>

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

    std::vector<std::string> input_real{
            ".#..#..O..O.....#O..O#O.O#.#.##O........#O..O...O#.O.O....##..#O..#..O.O#.O..#.O#O.#.#...#...#....O.",
            "#.O#.##..O.OO#..OO..O...O...#.O..#O...#..O...OO#....O...O#O...OO..##...O.O.O.....OO..#......O..##...",
            "..........O..O.OO...O.O....O...O..O..#O#O.O.#........O..O.O.O..O##.#O...O#...O..O....#...OO.#O..#.#.",
            "..O.O..O.O#....O...O#.....O.....##O..O#.O...O......#O#...OO...##O....O.O#OO#.....O##.....#O.OO....#O",
            "OOO...O....##...#OO.O.O.#OO.O#O.O.O..O.OO.##.O...O.........O...#.#O.......O#...O###.#...#O.#.....#..",
            "O..#..#......O...OO..#....#..O...O#.#...O#...#.##...#.#....O..O#.......O.......O..O.O......##..O....",
            ".....###..O#........OOO.#...#O.O#O..OO...O#...O..................#....O..##.#.O.O.#.#O...#.##.O...##",
            "OOOO......#O..O.#...O..O..O...#....#..O.#O..OOO.##....#.O......#.#.#O.O.O.#.O##.OOOO.O.#O.#O###..O.#",
            "#.....O#..O...O..O.O..#...O..#..#..#.....#..O.#OO...#.O.....#..O.....O.O.#O#......#.O.O#...#.O..#...",
            "O....O....O....OO.O...#......O.O.#O........O#.....#...........O.#.O.##.....O......#..#....O.....#...",
            ".........O##.###....#......#....#O.O..#...O.O.....O..OO.O...O.OO..#.O.#OO..#.#...O.##.OO..#.OO.O....",
            "......O###....O.#..O..OO#O.......#.......#O..#...O.O......O...O.....###.#O..#O.O...#O.#OO...##O..O.#",
            "....#O#.....O...O........#.##O.O..O....#.....O.O#...#.##....##.....O.O.#.O..O#.O..O#...........O.OO.",
            "#.O......#.##...OO...#.#.....#.###.OO..##O##.O.#.....O#..OOO...O.#O#..O...#..#....##......##.OO..O..",
            "OOO.##OOOO#.........O.#OOOO...O....OO#O##.O......#.........#.O..#....O..#....#..#....#..#.O....#..OO",
            ".#O......O#...........O.O....#.O....#...##..O......#.O..#..OOO.#....#...#O.....O....#OO..#.#O..O....",
            "...#.....##..O..##...##...O#OO.O..O#..O##..O.....#O#..O...O#...O..##OO...OO#..O...#.O#...##....O.O#O",
            ".......#.....O...#O..OO.O#O.....O.......O#.O...O.O#...O.#...O...O......O.O.##........#...#.##..O....",
            "#O....O.O...#.OO....O#.O........O.....#....OO..#O#..O.O#.#.O.##OO...O.#..O......O#.#..O.###.....OO..",
            "....O..OO.O..O..O#.........O..O...O.#..#....O.O.#.#O....O....O#.#......O..#.#..#.#..O.#.##.##O.O#.#O",
            "O......O#.O.....O.#....O......OO....O.#O.O....#...O#.........O..O.O.O..........O....#.....O#...O.OO#",
            "#OO...O...O...O.......##..O..##O..##......O...O...#O.O.OOO..O........#..##.OO.O.#.......O..#..O...OO",
            "...#.#.O#OO.O.#...#.OO.....OO..#.O..#.OO......OO..........OO..O#...........O.#.#O.....#.O..O#..##...",
            "..O..O..##.OO...O...O.#......O.#....#.O#..OOOO#.##.O......#.O...O.OO....OOOOO.........#.O.O....O..#.",
            ".##.#...O#...OO.#.......#.##.O.......O.O.#.#O#..O#O#...O...#.O.............O......OO...O.......OO.##",
            "...OO..#.O..O.#...O...........O##OOO...O.O##...O.#...O....#..O.O.OO....##O#.#O...#O.#...OO#.##.#.OO.",
            "#...#......#.OO..#.#.O.O.....O..O..O#..#.....O.#..#.#.O.#O.#OO......OO.....O.##OO.#...OOOO#OO.....O.",
            ".....###O##.##.......##O.##.O...#..OO....OO.O.........O#.....OOOO....#OO#...#O.OOO..O#....O.......#.",
            "........#O.O..#O#O#O..OOO....O.....O.#..#.......O.....#....O.....#.O##..O#....OO.#..O#.O........#...",
            ".#O...#..#.......#...O..O.O.#OO..#.O.#O#....O.#O..#....#..OO.#OOO.O#.O.#...O.O..O....#.#.O.......#..",
            "O.......##.O#...OO.O#O.O.O....O#.....O...O..#.....#O..O..#.#O.##....O...#O...##..O....O...#OO.#.O...",
            ".O.#..O.OO.O##..OO.##.#O#O..OO..O..........OO...O###..............O.....#.##...O.....#.OO.O#..O#O...",
            "O.#....O.#.##..#...O....#...#.OO.#.##.#...#.#O.#.##O.....##O.O....O..O..O##.......O#...O##.......OO.",
            "...#......#OO.........#..OO.O.O........#..O...O.O....O#O..OO#...#..#O..#.#OO....O.#..O.O.........O.O",
            "...O...O..O#.#O#O#O#O.#..##..##.OO##........O.O......##.O.O.#..#.....O#O#..O.O.#....OO...#.O...O#O.O",
            "##....#.....O.......#OOOOO..O....#...#........#....O.#....#.#..#.O##.##....O...#.#O...O...O..O......",
            "..OO..O...O#.O#..#....##...#........###.O.OO...##.......#..#....O..O..O.#OOO..#..#O........O..OO...O",
            "..#...#..........O..O.###..OO..O.O....#..#.OO#....#.#...O#..O..O..OO##....O.#...#.#...#..#.#......O.",
            "..OO..#.O.........O#.O.OO.O..O.O#.OOO..O..#.#.O#....O#.OO..O#..##.#..#O#..#..O.#.O#...O...O..#O....O",
            "..O#..O..O#O...#..#.OO.....#....OOOO.....O...O..OO.O.#.O...#OO.O##O..O#....##.OO#.......O.#....#.#..",
            "......O.#......#....OO.#.O...#OO.#O..#....O#.O.OOOO..OO.O....##O.#....O#..OO#.OO#O##..O.#........O..",
            ".O...........#O...O..O#..#..O.O..#O#.#..O..OO..O.O.#O...#..OOO.#...OO.....O........O...##..#...O...#",
            "......#O...O...#O.O...O..#OO....O..O.#OO..O....O#..#OO...#.#.#.##OOO.O.#OO..OO#........#.##.O..#....",
            "OOO.O..O.O....O.....O##.......#OO...#O.......O..#O....O....OO..O.#.........O.O.OO.....O#.........OO#",
            ".#.OO......O...#.#..O....O...O...............O..O...O.OO....O.#O....#........#...#.#......O......O..",
            "#.......#O.#...###....O.O....#.###.OO..#OO....#....O.....#O.OO##OO..O.O....#O..#......#..#O#...#.O..",
            "OOOO..#...##O........#....OO.....O.O##..#O..OO..O#.##O..O#...#.OOOO##...........#.#O...#.O#.O....O.O",
            "O#..O#..#.O..#.O.OO.O#O.O..#......O.#...O#O#..O..OO.#..O.OO#..OOO............O.....OOO#.O###.....##.",
            "O....##.........O.O.O.O..OOO...O..O.O....O......#..........#...#.....#..#..#.....#.###..#...O#......",
            "OOOO...#O##.O.O#...#.#..OO.O#...#O.O.....#....OOO....#..#O..##.....OO...O..OO#...O..OOO...#.O.O...OO",
            "..#O#...O......O##..OO#..#O#..#O#.O...#.###.O.O....O.....#..OO.O...O.#.......#..#.#.#.....#O..O.O...",
            "..#....O.O.......OO..O#..OOOO..#.........#OO......O..O...O..O.###.......#O#...#.O..OOO.......O#.#.#.",
            ".O.O..#........OOO.O.##..#.O...O.O.OO..#..O#O.##.OOO#.OO...#....OO#O#.......O##.....O....#OOO.O...O.",
            "#....O.......#..#OO.#.#.O....#..#.#...O..O.O..O....OOO....#.O.#OOOO.#.......#.#.OO...OOO....#..#....",
            ".OO.O.O......O#.O....#......#O..##.....O.#..##..O...O.O...OO..OO..#..O..O....#......O.O.......#O.#.O",
            "....O.#..O....O#.OOO.O..#....O..O...#.OO........O.#OO#O#.##..O..O##.O#...O......O....#O#..#...#O.#..",
            "#.....#..O#..O..OOO..O.#....#.......OO.O##.#......OO.....OO....O.O...#.#.O#...OO.......OO....#.....#",
            "....O.OO#....#O#..O..#O.....#..O...O...O.##...O....#.....#.O....O##O..O#O.....O..##...O....O.O#.....",
            "..O.#.#..OO......#..#.#.#.#.....O..#O..O.........O#...O##.#.....#O.O..O....#.##O.#O..OO...##....#..O",
            "O......#............#.....##O..O..OO.....##..O..O.......O.......#OO...#O.....O.O.O.......OOO.O.#OOO.",
            "O..OO.#....#...O..O...##..OO...O........OO....O..........#OO.....#..#O...O#.#....#O..O#..#.O......O.",
            "..O#.##O..O.#..#.......O...#...O..O.#O....#.#....#O#.O..#O...O..#OO.O#O.....O....#.....#..O.......#.",
            ".O.O..OO.O...O.#O....OOO..O.O................O..##......OO.O.......OO.O................#.O....OOO#O.",
            "......O.O.#O#...O#..#.........#O#.#O......O...#O....#.#O..O...O..#...O.O.#OO.O...#.........OO..OO...",
            ".#.O..O...#O.##.O.......##....O...##.......OOO..O...#.O#.......#...OO#.#.#......#O..#OO..O...OO...O.",
            ".O....O........#O.#..#.#...##.#..........O..O.#..#..#.##..#.#.#.#..#......O#........OO.....OO.#..#..",
            "#O..O.#....O.#..OO#......#.#.O.O..O.##.#.....#O..OO..O......O#...O#..O..O.....OO.#........O......#..",
            "O.#....O..#....O.O.OO#O..#...O##..OO#......O.#....O...#.O....##..O.O#OO..O......O.O.......#...O.O.#.",
            "..O......O..OO.OOO.....#...O...#..#.#...OOO.O.#O...O.#O.....OO.O.....O.O#.O.O..##..............OO...",
            "...OO#....O....#.......OOOO....#OO.O.O.O##.#.O..O.O......#.............#......O.O....#O##O.#.O.#O...",
            ".#..O..#..#O...##O..O#O...#..O#...#.O.........O..O.O......O##O.#O.....O.O..##.#.........#.......O...",
            ".O.OOOO.#...##.O#O#.#..#...#..OO..O##..##..OO.#...#...#....O..#O#.#...OO..O..O..#O..#.#OO.O#..O.O.##",
            "..O...#....O#........O......OO.......O..##.O...O...#O..O.....#...O#...O.O#.#.O.#.#OO.##.....O..O..O.",
            ".......#.O...O....O.O..#O.O..#O.#....##...................O#OO.....#....OO...O...##.#.O..#O#..#.O#..",
            ".OO.#...##....#O#.........OOOO.OO.#.#.O.#....#......O.O.O#..###.O#..#..##....OO.#..#....#.#.....O#..",
            "O.O...O..#....O.#......O##..#.O..#OO#O..........#O.OOO.......O......#OO#.....#..O#.#...##O..O.O.O...",
            ".....O.....#O###..........O...O...#O.O.#.O.....O..O...O...#O...##...O#.#...OO.........O...#.##O....#",
            "#OO.OO..##..O.O..OO.OO.O#.##.O.O..O##OO..#...#.O...OO.#.#...OO#.OO.....OO...##O..O...O....#.O...O##O",
            "#.O...O.#O.##O..##.#.#O.#OO.O.O.O.#..............#...#.O...#.O..#O..O.O.O.#.O..OO#..O#..#..O..#.#...",
            ".OO.#.O.O.O....O##O..O...O..O.##....#....#.......O...O.OO..#...#.O..#O....O......OO#O........##.O...",
            "..#.......#.....##O.###..OO.#....O.O.#..#.O.#O#O##..##.....#.#.........#...O........#..#..#...#O..#.",
            "..O#OO.#.OO#.OO...##..O..O.O.O......O.....#.....#O#.#.#O.#......#...O.....#O..O.#O...#.OOOO.OO......",
            "....#...#......O#.......#......#O....O.O#O......O..O...O..##..OOO.O.#..#.O.OO..#.#..#...O.#......O..",
            "O..O....O#....O...##O...#O##.#.....O..#.....#.#......#......O.....#.#.#..O.OO#..O...OO..OOOO.O......",
            ".O....O..O...OO....O.....O#.......O........O....O....O.......O..O..#..OO..#O...#......##.#....O..OO#",
            ".....#..OO.O.#.....O.O.O#O.#O#..O.O..O...#.#.O.O...#....O..#..#...##OO..#.#..#O.O...#.O#O......O.#..",
            "O..##.#.O..#.O#.#O....#O.##..#O.#....O...OOO.O......O....#.O..##..#.O...#........#.#..O..OO.O..###..",
            "....#O...O.O......#..O.O..........#.#OO.O#..#O..OO...#.O.O.#.#O...O..#...#..O#.O.OO..O........#OO...",
            "..#...O......O.##...#O.#.O...O#O..O..O......O#.......#...#O...O#.#.#........#.....O##O.#..#O#..OO..#",
            "#O#O#.O#..#.O...OO..........##.O#.....#.O...O.....O....O#OO..#O..O.....OO.#..#..O....#.O..O......O.#",
            "OO#.#.#......#......###.#.........#..OO.O.O#.....O#O.#.O...O##.....#..##OO..OO#.###.O.O.......#.O.##",
            "#.#O...#....#..#.......O......O..##....#..##..O...##O#..OO.....O..OOO.OO.O.#OO....O...#.......O..#..",
            ".O.#O.....#.O......OO..O....###.#...O.O...#....#OO..........O#O....O.........O..##OO.O..#.#..O##.#..",
            ".#..O..O.OOO.OOO.OO.O........##...OO#.O.O..O...O..O..#O.#.O.....OO...#....OO.#..O#.#.......#.O#....O",
            "....O.O#.O#...OO...#..#.##.OOO.....O.O.O.....OO..OO..OOO.#.......O...O...#....#O...O#.O...O##.##.#..",
            "##O#...O....O..OO.O..##OO.O#.O.....#.#.O.O.......O#...#..#.OO...#...#..OOO###.......#.O.....O.#O...O",
            "#.O..#.O.....OO..OO.#....###.#.#O..OO..........#O...O.O....O..##O..#..O..O.#OO...#....#...##..#.....",
            "#..O..###..#.O.........OO...#O........O..O..O...O......O....O...O...##.....O.......#.#...O#....O.O..",
            ".#O...O#....#....#...O.#...#O..#...O#...O.OO......O..OOO..#..O.#.O..O..#O.......O####O#.OO#..O.O.O..",
            "...#.#O#..#........O.#O....OO....O#..#.#.O..O....O....#.O#.#.#......O.#......O#..OO...##O.#O.....O#O"
    };

    decltype(input_real) input_test{
            "O....#....",
            "O.OO#....#",
            ".....##...",
            "OO.#O....O",
            ".O.....O#.",
            "O.#..O.#.#",
            "..O..#O..O",
            ".......O..",
            "#....###..",
            "#OO..#....",

    };
    // auto &input = input_test;
    auto &input = input_real;

    void move_north(ll top_idx, std::vector<std::string> &result) {
        ll bottom_idx = top_idx - 1;
        assert(top_idx > 0 && top_idx < result.size());
        assert(bottom_idx >= 0 && bottom_idx < result.size());

        auto &top = result.at(top_idx);
        auto &bottom = result.at(bottom_idx);

        for (ll i = 0; i < top.size(); i++) {
            if (bottom.at(i) == '.' && top.at(i) == 'O') {
                bottom.at(i) = 'O';
                top.at(i) = '.';
            }
        }
    }

    void move_south(ll top_idx, std::vector<std::string> &result) {
        ll bottom_idx = top_idx + 1;
        assert(top_idx >= 0 && top_idx < result.size());
        assert(bottom_idx > 0 && bottom_idx < result.size());

        auto &top = result.at(top_idx);
        auto &bottom = result.at(bottom_idx);

        for (ll i = 0; i < top.size(); i++) {
            if (bottom.at(i) == '.' && top.at(i) == 'O') {
                bottom.at(i) = 'O';
                top.at(i) = '.';
            }
        }
    }

    void move_west(ll top_idx, std::vector<std::string> &result) {
        ll bottom_idx = top_idx - 1;
        assert(top_idx > 0 && top_idx < result.at(0).size());
        assert(bottom_idx >= 0 && bottom_idx < result.at(0).size());

        for (ll j = 0; j < result.size(); j++) {
            if (result.at(j).at(bottom_idx) == '.' && result.at(j).at(top_idx) == 'O') {
                result.at(j).at(bottom_idx) = 'O';
                result.at(j).at(top_idx) = '.';
            }
        }
    }

    void move_east(ll top_idx, std::vector<std::string> &result) {
        ll bottom_idx = top_idx + 1;
        assert(top_idx >= 0 && top_idx < result.at(0).size());
        assert(bottom_idx > 0 && bottom_idx < result.at(0).size());

        for (ll j = 0; j < result.size(); j++) {
            if (result.at(j).at(bottom_idx) == '.' && result.at(j).at(top_idx) == 'O') {
                result.at(j).at(bottom_idx) = 'O';
                result.at(j).at(top_idx) = '.';
            }
        }
    }

    std::vector<std::string> perform_cycle(const std::vector<std::string> &map) {
        std::vector<std::string> result = map;
        for (ll moving_row = 1; moving_row < result.size(); moving_row++) {
            for (ll row = moving_row; row > 0; row--) {
                move_north(row, result);
            }
        }

        for (ll moving_column = 1; moving_column < result.size(); moving_column++) {
            for (ll column = moving_column; column > 0; column--) {
                move_west(column, result);
            }
        }

        for (ll moving_row = result.size() - 2; moving_row >= 0; moving_row--) {
            for (ll row = moving_row; row < result.size() - 1; row++) {
                move_south(row, result);
            }
        }

        for (ll moving_column = result.size() - 2; moving_column >= 0; moving_column--) {
            for (ll column = moving_column; column < result.size() - 1; column++) {
                move_east(column, result);
            }
        }
        return result;
    }

    ll get_load(const std::vector<std::string> &map) {
        ll result = 0;
        for (ll y = 0; y < map.size(); y++) {
            for (ll x = 0; x < map.at(y).size(); x++) {
                if (map.at(y).at(x) == 'O') {
                    result += (map.size() - y);
                }
            }
        }
        return result;
    }
}

int main14() {
    int64_t result0 = 0;
    int64_t result1 = 0;

    ASSERT_EQ(input.size(), input.at(0).size());

    auto test_after_1 = perform_cycle(input_test) == std::vector<std::string>(
            {".....#....",
             "....#...O#",
             "...OO##...",
             ".OO#......",
             ".....OOO#.",
             ".O#...O#.#",
             "....O#....",
             "......OOOO",
             "#...O###..",
             "#..OO#...."});
    assert(test_after_1);


    auto test_after_2 = perform_cycle(perform_cycle(input_test)) == std::vector<std::string>(
            {".....#....",
             "....#...O#",
             ".....##...",
             "..O#......",
             ".....OOO#.",
             ".O#...O#.#",
             "....O#...O",
             ".......OOO",
             "#..OO###..",
             "#.OOO#...O"});
    assert(test_after_2);

    auto test_after_3 = perform_cycle(perform_cycle(perform_cycle(input_test))) == std::vector<std::string>(
            {".....#....",
             "....#...O#",
             ".....##...",
             "..O#......",
             ".....OOO#.",
             ".O#...O#.#",
             "....O#...O",
             ".......OOO",
             "#...O###.O",
             "#.OOO#...O"});
    assert(test_after_3);

    {
        std::vector<std::string> input_after_move_north = input;
        for (ll moving_row = 1; moving_row < input_after_move_north.size(); moving_row++) {
            for (ll row = moving_row; row > 0; row--) {
                move_north(row, input_after_move_north);
            }
        }
        result0 = get_load(input_after_move_north);
    }

    ll cycles_nr = 1000000000;
    std::vector<std::vector<std::string>> results;

    auto &cycle_input = input;
    ll first_repeating_after = INT64_MIN;

    for (ll cycle = 0; cycle < cycles_nr; cycle++) {
        auto cycle_output = perform_cycle(cycle_input);
        auto existing_it = std::find(results.begin(), results.end(), cycle_output);
        if (existing_it != results.end()) {
            first_repeating_after = std::distance(results.begin(), existing_it) + 1;
            results.erase(results.begin(), existing_it);
            break;
        } else {
            results.push_back(std::move(cycle_output));
            cycle_input = results.back();
        }
    }


    auto effective_result_idx = (cycles_nr - first_repeating_after) % results.size();
    result1 = get_load(results.at(effective_result_idx));

    ASSERT_EQ(result0, 109654);
    ASSERT_EQ(result1, 94876);
    return 0;
}
