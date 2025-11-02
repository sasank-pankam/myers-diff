//
// Created by sasank on 9/19/25.
//

#ifndef MYERS_DIFF_H
#define MYERS_DIFF_H

#include "differ.h"
#include "internal_utils.h"

namespace myers {

        template<typename T>
        class QuadraticDiff : public BaseDiffer<T> {
                std::vector<Path> backtrack(const DataView<T> &a, const DataView<T> &b);
                std::vector<detail::NegIndVector<int>> shortest_edit_path(const DataView<T> &a, const DataView<T> &b);

        public:
                std::vector<Edit<T>> diff(const DataView<T> &a, const DataView<T> &b) override;
        };
} // namespace myers

#endif // MYERS_DIFF_H
