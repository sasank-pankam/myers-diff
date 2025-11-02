//
// Created by sasank on 10/28/25.
//

#include <iostream>
#include <vector>

#ifndef MYERS_DIFF_INTERNAL_UTILS_H
#define MYERS_DIFF_INTERNAL_UTILS_H


namespace myers::detail {

        template<typename T>
        class NegIndVector : public std::vector<T> {

                int wrap(int i) const { return i < 0 ? i + (int) this->size() : i; }

                using Base = std::vector<T>;

        public:
                using Base::Base;

                T &operator[](int idx) {
                        // convert the index to a wrappable -ve index
                        return Base::operator[](wrap(idx));
                }

                const T &operator[](int idx) const { return Base::operator[](wrap(idx)); }
        };

        template<typename T>
        inline std::ostream &operator<<(std::ostream &os, const NegIndVector<T> &v) {
                os << "[";
                for (int i = 0; i < v.size(); ++i) {
                        os << v[i];
                        if (i < v.size() - 1) {
                                os << ", ";
                        }
                }
                os << "]";
                return os;
        }

        inline std::ostream &operator<<(std::ostream &os, const NegIndVector<int> &v) {
                os << "[";
                for (int i = 0; i < v.size(); ++i) {
                        auto val = v[i];
                        if (val == -1) {
                                os << "  ";
                        } else {
                                os << val;
                        }

                        if (i < v.size() - 1) {
                                os << ", ";
                        }
                }
                os << "]";
                return os;
        }
} // namespace myers::detail


#endif // MYERS_DIFF_INTERNAL_UTILS_H
