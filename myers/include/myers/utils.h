//
// Created by sasank on 9/20/25.
//

#ifndef MYERS_DIFF_UTILS_H
#define MYERS_DIFF_UTILS_H


#include "interfaces.h"
#include <string>
#include <cstdint>
#include <fstream>


namespace myers {
        namespace external {
                template<typename T>
                class VectorWrapper : public DataView<T> {
                        const std::vector<T> m_vec;

                public:
                        explicit VectorWrapper(const std::vector<T> &&vec) : m_vec(vec) {}
                        explicit VectorWrapper(const std::vector<T> &vec) : m_vec(vec) {}

                        T get(size_t idx) const override { return m_vec[idx]; }

                        size_t size() const override { return m_vec.size(); };
                };


                class StreamWrapper : public DataView<std::string> {
                        std::ifstream &m_stream;
                        std::vector<uint64_t> m_offsets; // offset

                        void build() {
                                if (!m_stream)
                                        return;

                                m_offsets.clear();
                                std::string line;

                                uint64_t pos = 0;
                                while (std::getline(m_stream, line)) {
                                        m_offsets.emplace_back(pos);
                                        pos = (uint64_t) m_stream.tellg();
                                        if (pos == (uint64_t) -1) {
                                                break;
                                        }
                                }

                                m_stream.clear();
                                m_stream.seekg(0, std::ios::beg);
                        }


                public:
                        explicit StreamWrapper(std::ifstream &stream) :
                            m_stream(stream), m_offsets(std::vector<uint64_t>{}) {
                                build();
                        }
                        explicit StreamWrapper(std::ifstream &&stream) :
                            m_stream(stream), m_offsets(std::vector<uint64_t>{}) {
                                build();
                        }

                        std::string get(size_t idx) const override {

                                // index handled by vector.
                                m_stream.seekg(m_offsets[idx]);


                                std::string s;
                                std::getline(m_stream, s);


                                return s;
                        }
                        size_t size() const override { return m_offsets.size(); }

                        ~StreamWrapper() override { m_stream.close(); }
                };
        } // namespace external

} // namespace myers

#endif // MYERS_DIFF_UTILS_H