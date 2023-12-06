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

    std::vector<ll> times = {44, 70, 70, 80};
    std::vector<ll> distances = {283, 1134, 1134, 1491};

}

int main06() {
    int64_t result0 = 0;
    int64_t result1 = 0;

    result0 = 1;
    for (ll max_time_idx = 0; max_time_idx < times.size(); max_time_idx++) {
        ll way_to_win = 0;
        for (ll time_to_charge = 1; time_to_charge <= times.at(max_time_idx); time_to_charge++) {
            ll distance_to_beat = distances.at(max_time_idx);
            ll time_to_race = times.at(max_time_idx) - time_to_charge;
            if (time_to_race == 0) {
                break;
            }
            ll race_distance = time_to_race * time_to_charge;

            if (race_distance > distance_to_beat) {
                ++way_to_win;
            }
        }
        result0 *= way_to_win;
    }


    ll max_time = 44707080;
    ll distance_to_beat = 283113411341491;
    ll first_charge_time_to_win = 0;
    ll last_charge_time_to_win = 0;
    for (ll time_to_charge = 1; time_to_charge <= max_time; time_to_charge++) {
        ll time_to_race = max_time - time_to_charge;
        assert(time_to_race > 0);
        ll race_distance = time_to_race * time_to_charge;

        if (race_distance > distance_to_beat) {
            first_charge_time_to_win = time_to_charge;
            break;
        }
    }

    for (ll time_to_charge = max_time - 1; time_to_charge >= 0; time_to_charge--) {
        ll time_to_race = max_time - time_to_charge;
        assert(time_to_race > 0);
        ll race_distance = time_to_race * time_to_charge;

        if (race_distance > distance_to_beat) {
            last_charge_time_to_win = time_to_charge;
            break;
        }
    }

    result1 = last_charge_time_to_win - first_charge_time_to_win + 1;

    ASSERT_EQ(result0, 219849);
    ASSERT_EQ(result1, 29432455);
    return 0;
}
