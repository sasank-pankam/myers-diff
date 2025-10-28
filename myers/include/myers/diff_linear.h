//
// Created by sasank on 10/28/25.
//



#include "common.h"
#include "interfaces.h"

#ifndef MYERS_DIFF_DIFF_LINEAR_H
#define MYERS_DIFF_DIFF_LINEAR_H


namespace myers {

        template<typename T>
        class DiffLinear : public BaseDiff<T> {

        std::tuple<int,int,int,int> middle_snake(
                   const DataView<T>& a, int a_lo, int a_hi,
                   const DataView<T>& b, int b_lo, int b_hi);

        void diff_rec(const DataView<T>& a, int a_lo, int a_hi,
                     const DataView<T>& b, int b_lo, int b_hi,
                     std::vector<Edit<T>>& out);
        public:
                std::vector<Edit<T>> diff(const DataView<T> &a, const DataView<T> &b) override;
        };

} // namespace myers

#endif // MYERS_DIFF_DIFF_LINEAR_H
