//
// Created by sasank on 10/28/25.
//

#include <functional>

#ifndef MYERS_DIFF_INTERFACES_H
#define MYERS_DIFF_INTERFACES_H

namespace myers {
        template<typename T>
        class DataView {
        public:
                virtual ~DataView() = default;
                virtual T get(size_t idx) const = 0;
                virtual size_t size() const = 0;
        };

        template<typename T>
        class BaseDiff {
        protected:
                using Comparator = std::function<bool(const T &, const T &)>;
                Comparator m_comp;
        public:
                virtual ~BaseDiff() = default;
                BaseDiff(Comparator comp = std::equal_to<T>()) : m_comp(comp) {}

                virtual std::vector<Edit<T>> diff(const DataView<T> &a, const DataView<T> &b) = 0;
        };

}

#endif // MYERS_DIFF_INTERFACES_H
