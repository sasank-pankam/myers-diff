//
// Created by sasank on 11/2/25.
//
#include "myers/types.h"

#ifndef MYERS_DIFF_VECTOR_INPUT_H
#define MYERS_DIFF_VECTOR_INPUT_H


namespace myers::utils {

        template<typename T>
        class VectorWrapper : public DataView<T> {
                const std::vector<T> m_vec{};

        public:
                explicit VectorWrapper(const std::vector<T> &&vec) : m_vec(vec) {}
                explicit VectorWrapper(const std::vector<T> &vec) : m_vec(vec) {}

                T get(size_t idx) const override { return m_vec[idx]; }

                [[nodiscard]] size_t size() const override { return m_vec.size(); };
        };
} // namespace myers::utils


#endif // MYERS_DIFF_VECTOR_INPUT_H
