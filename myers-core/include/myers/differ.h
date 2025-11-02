//
// Created by sasank on 11/2/25.
//

#include <functional>
#include "types.h"

#ifndef MYERS_DIFF_DIFFER_H
#define MYERS_DIFF_DIFFER_H


namespace myers {
        template<typename T>
        class BaseDiffer {
        protected:
                using Comparator = std::function<bool(const T &, const T &)>;
                Comparator m_comp;
        public:
                virtual ~BaseDiffer() = default;
                explicit BaseDiffer(Comparator comp = std::equal_to<T>()) : m_comp(comp) {}

                virtual std::vector<Edit<T>> diff(const DataView<T> &a, const DataView<T> &b) = 0;
        };
}

#endif // MYERS_DIFF_DIFFER_H
