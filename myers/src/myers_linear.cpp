//
// Created by sasank on 10/28/25.
//


#include <vector>

#include "myers/internal_utils.h"
#include "myers/diff_linear.h"

namespace myers {

        template <typename T>
        std::vector<Edit<T>> DiffLinear<T>::diff(const DataView<T> &a, const DataView<T> &b) {
                std::vector<Edit<T>> out;
                out.reserve(a.size() + b.size());
                diff_rec(a, 0, (int) a.size(), b, 0, (int) b.size(), out);
                return out;
        }

        template <typename T>
        std::tuple<int, int, int, int> DiffLinear<T>::middle_snake(const DataView<T> &a, int a_lo, int a_hi,
                                                    const DataView<T> &b, int b_lo, int b_hi) {
                int N = a_hi - a_lo;
                int M = b_hi - b_lo;

                if (N == 0 || M == 0) {
                        // No snake: return trivial empty snake at beginning
                        return {a_lo, b_lo, a_lo, b_lo};
                }

                int maxD = (N + M + 1) / 2;
                int offset = maxD;

                NegIndVector<int> vf(2 * maxD + 1, -1);
                NegIndVector<int> vb(2 * maxD + 1, -1);

                vf[1] = 0;
                vb[1] = 0;

                for (int D = 0; D <= maxD; ++D) {
                        for (int k = -D; k <= D; k += 2) {
                                int idx = k;
                                int x;
                                if (k == -D || (k != D && vf[k - 1] < vf[k + 1])) {
                                        x = vf[k + 1];
                                } else {
                                        x = vf[k - 1] + 1;
                                }
                                int y = x - k;

                                while (x < N && y < M && this->m_comp(a.get(a_lo + x), b.get(b_lo + y))) {
                                        ++x;
                                        ++y;
                                }
                                vf[k] = x;

                                int k_rev = (N - M) - k;

                                if ((D % 2) == 0) {
                                        if (k_rev >= -maxD && k_rev <= maxD && vb[k_rev] != -1) {
                                                int x_rev = vb[k_rev];

                                                if (vf[k] + vb[k_rev] >= N) {
                                                        int x_start = vf[k];
                                                        int y_start = x_start - k;

                                                        int u = a_lo + x_start;
                                                        int v = b_lo + y_start;

                                                        int x_meet = vf[k];
                                                        int y_meet = x_meet - k;

                                                        int x0 = x_meet;
                                                        int y0 = y_meet;
                                                        while (x0 > 0 && y0 > 0 &&
                                                               this->m_comp(a.get(a_lo + x0 - 1), b.get(b_lo + y0 - 1))) {
                                                                --x0;
                                                                --y0;
                                                        }
                                                        int x1 = x_meet;
                                                        int y1 = y_meet;
                                                        while (x1 < N && y1 < M &&
                                                               this->m_comp(a.get(a_lo + x1), b.get(b_lo + y1))) {
                                                                ++x1;
                                                                ++y1;
                                                        }

                                                        int start_x = a_lo + x0;
                                                        int start_y = b_lo + y0;
                                                        int end_x = a_lo + x1;
                                                        int end_y = b_lo + y1;
                                                        return {start_x, start_y, end_x, end_y};
                                                }
                                        }
                                }
                        }

                        for (int k = -D; k <= D; k += 2) {
                                int idx = k;
                                int x;
                                if (k == -D || (k != D && vb[k - 1] < vb[k + 1])) {
                                        x = vb[k + 1];
                                } else {
                                        x = vb[k - 1] + 1;
                                }
                                int y = x - k;

                                while (x < N && y < M && this->m_comp(a.get(a_hi - 1 - x), b.get(b_hi - 1 - y))) {
                                        ++x;
                                        ++y;
                                }
                                vb[k] = x;

                                int k_fwd = (N - M) - k;
                                if ((D % 2) == 1) {
                                        if (k_fwd >= -maxD && k_fwd <= maxD && vf[k_fwd] != -1) {
                                                int x_fwd = vf[k_fwd];
                                                if (x_fwd + vb[k] >= N) {
                                                        int x_meet_from_start = x_fwd;
                                                        int y_meet_from_start = x_meet_from_start - k_fwd;
                                                        int x_meet = x_meet_from_start;
                                                        int y_meet = y_meet_from_start;

                                                        int x0 = x_meet;
                                                        int y0 = y_meet;
                                                        while (x0 > 0 && y0 > 0 &&
                                                               this->m_comp(a.get(a_lo + x0 - 1), b.get(b_lo + y0 - 1))) {
                                                                --x0;
                                                                --y0;
                                                        }
                                                        int x1 = x_meet;
                                                        int y1 = y_meet;
                                                        while (x1 < N && y1 < M &&
                                                               this->m_comp(a.get(a_lo + x1), b.get(b_lo + y1))) {
                                                                ++x1;
                                                                ++y1;
                                                        }
                                                        int start_x = a_lo + x0;
                                                        int start_y = b_lo + y0;
                                                        int end_x = a_lo + x1;
                                                        int end_y = b_lo + y1;
                                                        return {start_x, start_y, end_x, end_y};
                                                }
                                        }
                                }
                        }
                }

                return {a_lo, b_lo, a_lo, b_lo};
        }

        template<typename T>
        void DiffLinear<T>::diff_rec(const DataView<T> &a, int a_lo, int a_hi, const DataView<T> &b, int b_lo, int b_hi,
                      std::vector<Edit<T>> &out) {

                while (a_lo < a_hi && b_lo < b_hi && this->m_comp(a.get(a_lo), b.get(b_lo))) {
                        out.emplace_back(Edit<T>(EditType::Keep, a.get(a_lo), b.get(b_lo)));
                        ++a_lo;
                        ++b_lo;
                }

                while (a_lo < a_hi && b_lo < b_hi && this->m_comp(a.get(a_hi - 1), b.get(b_hi - 1))) {
                        --a_hi;
                        --b_hi;
                }

                if (a_lo == a_hi) {
                        for (int j = b_lo; j < b_hi; ++j) {
                                out.emplace_back(Edit<T>(EditType::Insert, {}, b.get(j)));
                        }
                        return;
                }
                if (b_lo == b_hi) {
                        for (int i = a_lo; i < a_hi; ++i) {
                                out.emplace_back(Edit<T>(EditType::Delete, a.get(i), {}));
                        }
                        return;
                }

                auto [sx, sy, ex, ey] = middle_snake(a, a_lo, a_hi, b, b_lo, b_hi);

                if (sx == ex && sy == ey) {
                        for (int i = a_lo; i < a_hi; ++i)
                                out.emplace_back(Edit<T>(EditType::Delete, a.get(i), {}));
                        for (int j = b_lo; j < b_hi; ++j)
                                out.emplace_back(Edit<T>(EditType::Insert, {}, b.get(j)));
                        return;
                }

                diff_rec(a, a_lo, sx, b, b_lo, sy, out);

                for (int i = sx, j = sy; i < ex && j < ey; ++i, ++j) {
                        out.emplace_back(Edit<T>(EditType::Keep, a.get(i), b.get(j)));
                }

                diff_rec(a, ex, a_hi, b, ey, b_hi, out);
        }

} // namespace myers

template class myers::DiffLinear<std::string>;
template class myers::DiffLinear<char>;
template class myers::DiffLinear<int>;
