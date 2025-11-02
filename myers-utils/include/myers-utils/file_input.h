//
// Created by sasank on 11/2/25.
//

#include <cstdint>
#include <fstream>

#include "myers/types.h"

#ifndef MYERS_DIFF_FILE_INPUT_H
#define MYERS_DIFF_FILE_INPUT_H

namespace myers::utils {

        class StreamWrapper : public DataView<std::string> {
                std::ifstream &m_stream;
                std::vector<uint64_t> m_offsets{}; // offset

                void build() {
                        if (!m_stream)
                                return;

                        m_offsets.clear();
                        std::string line;

                        uint64_t pos = 0;
                        while (std::getline(m_stream, line)) {
                                m_offsets.emplace_back(pos);
                                pos = static_cast<uint64_t>(m_stream.tellg());
                                if (pos == static_cast<uint64_t>(-1)) {
                                        break;
                                }
                        }

                        m_stream.clear();
                        m_stream.seekg(0, std::ios::beg);
                }


        public:
                explicit StreamWrapper(std::ifstream &stream) : m_stream(stream), m_offsets(std::vector<uint64_t>{}) {
                        build();
                }
                explicit StreamWrapper(std::ifstream &&stream) : m_stream(stream), m_offsets(std::vector<uint64_t>{}) {
                        build();
                }

                [[nodiscard]] std::string get(size_t idx) const override {
                        // index handled by vector.
                        m_stream.seekg(m_offsets[idx]);

                        std::string s;
                        std::getline(m_stream, s);

                        return s;
                }
                [[nodiscard]] size_t size() const override { return m_offsets.size(); }

                ~StreamWrapper() override { m_stream.close(); }
        };

} // namespace myers::utils


#endif // MYERS_DIFF_FILE_INPUT_H
