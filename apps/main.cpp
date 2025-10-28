#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "myers/diff.h"
#include "myers/utils.h"

template<typename T>
void run_test(const std::string &test_name, const myers::DataView<T> &a, const myers::DataView<T> &b,
              std::ofstream &logger) {
        std::cout << test_name << " start\n";

        myers::Diff<T> differ;

        auto start = std::chrono::high_resolution_clock::now();
        auto edits = differ.diff(a, b);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << test_name << " edits lenght: " << edits.size() << "\n";
        for (auto &e: edits) {
                std::cout << e << "\n";
        }

        if (logger.is_open()) {
                logger << test_name << ": " << duration << " µs\n";
        }

        std::cout << test_name << " end (" << duration << " µs)\n";
}
const std::string log_file = "diff_benchmarks.log";

void test_diff_vector() {
        std::ofstream logger(log_file, std::ofstream::app);

        logger << "Naive impl\n";
        {
                std::string s1 = "ABCABBAACBACABACABBAACABBCABAC"
                                 "ABCACBBACABACABBAACBACABACABBC"
                                 "ABACABCABBAACBACABACABBCABACAB"
                                 "ACABCABBAACBACABACABBCABACABAC";
                std::string s2 = "CBABACABACABBACABACABBACACBBA"
                                 "CABACABBAACACBABACABACABBACABA"
                                 "CABACABBAACACBBACABACABBCABACA"
                                 "CABACABBAACACBBACABACABBCABACA";
                myers::external::VectorWrapper a(std::vector<char>{s1.begin(), s1.end()});
                myers::external::VectorWrapper b(std::vector<char>{s2.begin(), s2.end()});

                run_test("Chars test", a, b, logger);
        }
        {
                std::vector<std::string> a, b;
                for (int i = 0; i < 220; ++i) {
                        a.push_back("line" + std::to_string(i));
                        if (i % 10 == 0) {
                                b.push_back("lineZ" + std::to_string(i)); // mismatch every 10th
                        } else {
                                b.push_back("line" + std::to_string(i));
                        }
                }
                myers::external::VectorWrapper a_t(a);
                myers::external::VectorWrapper b_t(b);
                run_test("String test", a_t, b_t, logger);
        }
        {
                std::vector<int> a, b;
                for (int i = 0; i < 300; ++i) {
                        a.push_back(i * 2);
                        b.push_back(i * 2);
                }

                myers::external::VectorWrapper a_t(a);
                myers::external::VectorWrapper b_t(b);
                run_test("Int test", a_t, b_t, logger);
        }
}

void test_files() {
        std::ifstream f1("test_txt_1.txt", std::ifstream::in), f2("test_txt_2.txt", std::ifstream::in);
        std::ofstream logger(log_file, std::ofstream::app);

        myers::external::StreamWrapper s1(f1), s2(f2);
        run_test("File test", s1, s2, logger);
}

int main() {
        // test_diff_vector();
        test_files();

        return 0;
}
