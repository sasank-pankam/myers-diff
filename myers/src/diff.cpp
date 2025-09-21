//
// Created by sasank on 9/19/25.
//


#include "myers/diff.h"

#include <iostream>
#include <ostream>
#include <string>

#include "myers/utils.h"

template<typename T>
std::vector<NegIndVector<int>> myers::Diff<T>::shortest_edit_path(const std::vector<T> &a,
    const std::vector<T> &b) {
    if (a.empty() && b.empty()) {
        return {};
    }

    size_t n = a.size(), m = b.size();
    int max = n + m;  // TODO: check overflow

    NegIndVector<int> v(2 * max + 1, -1);
    std::vector<NegIndVector<int>> state;
    state.reserve(max + 1);
    v[1] = 0;

    for (int d = 0; d <= max; ++d) {
        state.push_back(v);   // copy

        for (int k = -d; k <= d; k += 2) {
            int x;
            if (k == -d || (k != d && v[k - 1] < v[k + 1])) {
                x = v[k + 1];
            } else {
                x = v[k - 1] + 1;
            }

            int y = x - k;
            while (x < n && y < m && this->comp_(a[x], b[y])) {
                ++x; ++y;
            }

            v[k] = x;
            if (x >= n && y >= m) {
                state.resize(d + 1); // release unnecessary allocated space.
                return state;
            }
        }
    }
    return {};
}

template<typename T>
std::vector<myers::Path> myers::Diff<T>::backtrack(const std::vector<T> &a, const std::vector<T> &b) {
    int x = a.size(), y = b.size();
    std::vector<myers::Path> ret;
    ret.reserve(x + y);

    auto shortest_path = this->shortest_edit_path(a, b);
    if (shortest_path.empty()) {
        return {};
    }

    for (int d = (int)shortest_path.size() - 1; d >= 0; --d) {
        int k = x - y;
        int prev_k;
        auto& v = shortest_path[d];

        if (k == -d || (k != d && v[k - 1] < v[k + 1])) {
            prev_k = k + 1;
        } else {
            prev_k = k - 1;
        }

        int prev_x = v[prev_k];
        int prev_y = prev_x - prev_k;

        while (x > prev_x && y > prev_y) {
            ret.emplace_back(myers::Path(x - 1, y - 1, x, y));
            --x; --y;
        }

        if (d > 0)
            ret.emplace_back(myers::Path(prev_x, prev_y, x, y));

        x = prev_x;
        y = prev_y;
    }

    return ret;
}

template<typename T>
std::vector<typename myers::Edit<T>> myers::Diff<T>::diff(const std::vector<T> &a, const std::vector<T> &b) {
    auto paths = backtrack(a, b);
    std::vector<Edit<T>> result_diff;
    result_diff.reserve(paths.size());

    for (auto& path : paths) {
        if (path.fr_x == path.to_x) {
            const T& b_line = b[path.fr_y];
            result_diff.emplace_back(Edit<T>(EditType::Insert, {}, b_line));
        } else if (path.fr_y == path.to_y) {
            const T& a_line = a[path.fr_x];
            result_diff.emplace_back(Edit<T>(EditType::Delete, a_line, {}));
        } else {
            const T& a_line = a[path.fr_x];
            result_diff.emplace_back(Edit<T>(EditType::Keep, a_line, a_line));
        }
    }

    std::reverse(result_diff.begin(), result_diff.end());
    return result_diff;
}


template class myers::Diff<std::string>;
template class myers::Diff<char>;
template class myers::Diff<int>;
