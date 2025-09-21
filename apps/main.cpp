#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include "myers/diff.h"

template <typename T>
void run_test(const std::string& test_name,
              const std::vector<T>& a,
              const std::vector<T>& b,
              std::ofstream& logger)
{
    using namespace std::chrono;

    std::cout << test_name << " start\n";

    myers::Diff<T> differ;

    auto start = high_resolution_clock::now();
    auto edits = differ.diff(a, b);
    auto end   = high_resolution_clock::now();

    // for (auto& e : edits) {
    //     std::cout << e << std::endl;
    // }

    auto duration = duration_cast<microseconds>(end - start).count();

    if (logger.is_open()) {
        logger << test_name << ": " << duration << " µs\n";
    }

    std::cout << test_name << " end (" << duration << " µs)\n";
}

int main() {
    std::string log_file = "diff_benchmarks.log";
    std::ofstream logger(log_file, std::ofstream::app);

    logger << "Naive impl\n"; {
        std::string s1 =
                "ABCABBAACBACABACABBAACABBCABAC"
                "ABCACBBACABACABBAACBACABACABBC"
                "ABACABCABBAACBACABACABBCABACAB"
                "ACABCABBAACBACABACABBCABACABAC";
        std::string s2 =
                "CBABACABACABBACABACABBACACBBA"
                "CABACABBAACACBABACABACABBACABA"
                "CABACABBAACACBBACABACABBCABACA"
                "CABACABBAACACBBACABACABBCABACA";
        std::vector<char> a(s1.begin(), s1.end());
        std::vector<char> b(s2.begin(), s2.end());
        run_test("Chars test", a, b, logger);
    } {
        std::vector<std::string> a, b;
        for (int i = 0; i < 220; ++i) {
            a.push_back("line" + std::to_string(i));
            if (i % 10 == 0) {
                b.push_back("lineZ" + std::to_string(i)); // mismatch every 10th
            } else {
                b.push_back("line" + std::to_string(i));
            }
        }
        run_test("String test", a, b, logger);
    } {
        std::vector<int> a, b;
        for (int i = 0; i < 300; ++i) {
            a.push_back(i * 2);
            b.push_back(i * 2 );
        }

        run_test("Int test", a, b, logger);
    }

    return 0;
}
