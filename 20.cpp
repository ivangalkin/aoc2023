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
#include <deque>

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

    std::map<std::string, std::vector<std::string>> input_real{
            {"%jf",         {"cr", "dn"}},
            {"%fd",         {"hm", "jx"}},
            {"%mb",         {"bq", "cr"}},
            {"&mr",         {"qt"}},
            {"%qd",         {"cr", "dg"}},
            {"%rs",         {"hh"}},
            {"%xl",         {"gq", "vj"}},
            {"%zl",         {"qn"}},
            {"%tj",         {"cr", "qd"}},
            {"%fn",         {"hn"}},
            {"%qc",         {"tf"}},
            {"%fh",         {"jj", "vj"}},
            {"&kk",         {"qt"}},
            {"%qn",         {"jx", "fn"}},
            {"%hm",         {"jx", "fq"}},
            {"%cm",         {"vj", "fh"}},
            {"%jj",         {"vj", "lp"}},
            {"%dr",         {"vj", "qc"}},
            {"broadcaster", {"db", "hd", "cm", "xf"}},
            {"%fq",         {"jx", "zk"}},
            {"%hd",         {"jx", "zl"}},
            {"&qt",         {"rx"}},
            {"&vj",         {"bb", "qc", "cm"}},
            {"%tt",         {"bd"}},
            {"%sf",         {"jx"}},
            {"%rg",         {"nl", "hr"}},
            {"%zk",         {"jx", "sf"}},
            {"%lp",         {"cz", "vj"}},
            {"%xf",         {"mb", "cr"}},
            {"&cr",         {"dg", "bq", "kk", "xf", "gm"}},
            {"%nb",         {"vj", "dr"}},
            {"%dg",         {"vm"}},
            {"%ql",         {"nl"}},
            {"&gl",         {"qt"}},
            {"&nl",         {"db", "hr", "mr", "hh", "hk", "rs", "bn"}},
            {"%ff",         {"ql", "nl"}},
            {"%rb",         {"cr"}},
            {"%lc",         {"vj"}},
            {"%vm",         {"gm", "cr"}},
            {"%tf",         {"vj", "xl"}},
            {"%hr",         {"kf"}},
            {"%kf",         {"xx", "nl"}},
            {"&bb",         {"qt"}},
            {"%ml",         {"nl", "bn"}},
            {"%bq",         {"tj"}},
            {"%db",         {"ml", "nl"}},
            {"%hn",         {"jx", "tt"}},
            {"%dn",         {"cr", "rb"}},
            {"%gm",         {"qs"}},
            {"%gq",         {"lc", "vj"}},
            {"%hh",         {"rg"}},
            {"%bd",         {"fd"}},
            {"%xx",         {"nl", "ff"}},
            {"%qs",         {"jf", "cr"}},
            {"&jx",         {"fn", "bd", "tt", "gl", "zl", "hd"}},
            {"%cz",         {"nb", "vj"}},
            {"%bn",         {"hk"}},
            {"%hk",         {"rs"}},
    };

    decltype(input_real) input_test1{
            {"broadcaster", {"a", "b", "c"}},
            {"%a",          {"b"}},
            {"%b",          {"c"}},
            {"%c",          {"inv"}},
            {"&inv",        {"a"}}
    };

    decltype(input_real) input_test2{
            {"broadcaster", {"a"}},
            {"%a",          {"inv", "con"}},
            {"&inv",        {"b"}},
            {"%b",          {"con"}},
            {"&con",        {"output"}},
    };

    enum Signal {
        LO = 0, HI = 1
    };

    // source, destination, signal
    using QueueElement = std::tuple<std::string, std::string, Signal>;
    using Queue = std::deque<QueueElement>;
    ll ITERATION = 1;
    std::string CRITICAL_CONJUNCTION;
    std::string CRITICAL_OUTPUT = "rx";

    class Element {
    public:
        std::string _name;
        std::vector<std::string> _inputs;
        std::vector<std::string> _outputs;

        virtual void process_signal(const QueueElement &event, std::array<ll, 2> &counter, Queue &queue) = 0;

    protected:
        void send_signal(Signal signal, std::array<ll, 2> &counter, Queue &queue) {
            for (auto &output: _outputs) {
                queue.push_back({_name, output, signal});
                counter[signal]++;
            }
        }
    };

    class FlipFlop : public Element {
        enum State {
            OFF, ON
        } state;

        void process_signal(const QueueElement &event, std::array<ll, 2> &counter, Queue &queue) override {
            const auto &[source, destination, signal] = event;
            if (signal == LO) {
                if (state == OFF) {
                    state = ON;
                    send_signal(HI, counter, queue);
                } else {
                    state = OFF;
                    send_signal(LO, counter, queue);
                }
            }
        }
    };

    class Broadcaster : public Element {
        void process_signal(const QueueElement &event, std::array<ll, 2> &counter, Queue &queue) override {
            const auto &[source, destination, signal] = event;
            send_signal(signal, counter, queue);
        }
    };

    class Conjunction : public Element {
    public:
        std::map<std::string, Signal> _last_signal_from_input;
        std::map<std::string, std::vector<ll>> _last_high_iteration;

        void process_signal(const QueueElement &event, std::array<ll, 2> &counter, Queue &queue) override {
            const auto &[source, destination, signal] = event;
            _last_signal_from_input[source] = signal;
            bool all_hi = true;
            bool any_hi = false;


            for (auto &input: _inputs) {
                bool input_is_hi = (_last_signal_from_input.contains(input) && _last_signal_from_input.at(input) == HI);
                all_hi &= input_is_hi;
                any_hi |= input_is_hi;
            }

            bool record_iterations_when_input_was_hi = _name == CRITICAL_CONJUNCTION && any_hi;
            if (record_iterations_when_input_was_hi) {
                for (auto &input: _inputs) {
                    bool input_is_hi = (_last_signal_from_input.contains(input) &&
                                        _last_signal_from_input.at(input) == HI);
                    if (!input_is_hi) {
                        continue;
                    }
                    auto &memory = _last_high_iteration[input];
                    if (memory.empty() || memory.back() != ITERATION) {
                        memory.push_back(ITERATION);
                    }


                    std::cout << input << ": ";
                    for (ll i = 0; i < memory.size() - 1; i++) {
                        std::cout << " " << memory.at(i + 1) - memory.at(i);
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
            if (all_hi) {
                send_signal(LO, counter, queue);
            } else {
                send_signal(HI, counter, queue);
            }
        }
    };


    class Output : public Element {
        void process_signal(const QueueElement &event, std::array<ll, 2> &counter, Queue &queue) override {
            const auto &[source, destination, signal] = event;
            // we reached a LO on the CRITICAL_OUTPUT by chance
            if (_name == CRITICAL_OUTPUT && signal == LO) {
                myprint(ITERATION);
                exit(0);
            }
        }
    };

    std::map<std::string, Element *> elements;


//    auto &input = input_test2;
    auto &input = input_real;
}

int main20() {
    int64_t result0 = 0;
    int64_t result1 = 0;

    // create
    for (auto &[name, outputs]: input) {
        if (name == "broadcaster") {
            auto *broadcaster = new Broadcaster();
            broadcaster->_name = name;
            broadcaster->_outputs = outputs;
            elements.emplace(name, broadcaster);
        } else if (name.starts_with('%')) {
            auto *flipflop = new FlipFlop();
            flipflop->_name = name.substr(1);
            flipflop->_outputs = outputs;
            elements.emplace(name.substr(1), flipflop);
        } else if (name.starts_with('&')) {
            auto *conjunction = new Conjunction();
            conjunction->_name = name.substr(1);
            conjunction->_outputs = outputs;
            elements.emplace(name.substr(1), conjunction);
        } else {
            assert(false && "unknown input element");
        }
    }

    // connect inputs
    for (auto &[name, outputs]: input) {
        for (auto &output: outputs) {
            Element *output_element = nullptr;
            if (elements.contains(output)) {
                output_element = elements.at(output);
            } else {
                output_element = new Output();
                output_element->_name = output;
                elements.emplace(output, output_element);
            }

            auto &name_without_prefix = (name.starts_with('%') || name.starts_with('&')) ? name.substr(1) : name;
            output_element->_inputs.push_back(name_without_prefix);
        }
    }

    // we need a LO on the critical element
    Element *critical_output = elements.at(CRITICAL_OUTPUT);
    // it has 1 input and we know it's a conjunction
    ASSERT_EQ(critical_output->_inputs.size(), 1);
    CRITICAL_CONJUNCTION = critical_output->_inputs.at(0);
    // it has to be set in order to detec cycles
    assert(!CRITICAL_CONJUNCTION.empty());

    std::array<ll, 2> global_counter{0, 0};
    std::array<ll, 2> counter_per_iteration;
    // perform many many iterations in order to
    // 1. detect number of signals after 1000 iterations
    // 2. detect cycles on the CRITICAL_CONJUNCTION
    for (ITERATION = 1; ITERATION <= 100000; ITERATION++) {
        counter_per_iteration.fill(0);
        Queue queue;

        // button
        counter_per_iteration.at(LO)++;
        elements.at("broadcaster")->process_signal({"button", "broadcaster", LO}, counter_per_iteration, queue);

        while (!queue.empty()) {
            Queue queue2;
            for (auto &event: queue) {
                auto &[source, destination, signal] = event;
                elements.at(destination)->process_signal(event, counter_per_iteration, queue2);
            }
            queue.clear();
            std::swap(queue, queue2);
        }

        global_counter.at(LO) += counter_per_iteration.at(LO);
        global_counter.at(HI) += counter_per_iteration.at(HI);

        if (ITERATION == 1000) {
            myprint(global_counter.at(LO) * global_counter.at(HI));
        }
    }


    Conjunction *qt = static_cast<Conjunction *>(elements.at(CRITICAL_CONJUNCTION));

    // periodicity for HI signals is recorded for all inputs of "qt"
    ASSERT_EQ(qt->_inputs.size(), qt->_last_high_iteration.size());

    ll input_hi_MAX_iteration = 0;
    ll input_hi_MAX_inc = INT64_MIN;

    std::cout << "Goto https://www.calculatorsoup.com/calculators/math/lcm.php and calculate LCM from" << std::endl;
    for (auto &[input_name, high_iterations]: qt->_last_high_iteration) {
        assert(high_iterations.size() >= 2);
        ll hi_periodicity =
                high_iterations.at(high_iterations.size() - 1) - high_iterations.at(high_iterations.size() - 2);
        // the cycle for HI signal for the given input was constant
        for (ll step = 0; step < high_iterations.size() - 1; step++) {
            ASSERT_EQ(high_iterations.at(step + 1) - high_iterations.at(step), hi_periodicity);
        }
        std::cout << hi_periodicity << " ";
    }
    std::cout << std::endl;

    // 243037165713371

    return 0;
}
