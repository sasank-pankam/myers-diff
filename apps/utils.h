//
// Created by sasank on 10/27/25.
//

#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

template<typename T>
class VectorWrapper : public myers::DataView<T> {
        const std::vector<T> m_vec;

public:
        explicit VectorWrapper(const std::vector<T> &&vec) : m_vec(vec) {}
        explicit VectorWrapper(const std::vector<T> &vec) : m_vec(vec) {}

        T get(size_t idx) const override { return m_vec[idx]; }

        size_t size() const override { return m_vec.size(); };
};


class StreamWrapper : public myers::DataView<std::string> {
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
        explicit StreamWrapper(std::ifstream &stream) : m_stream(stream), m_offsets(std::vector<uint64_t>{}) {
                build();
        }
        explicit StreamWrapper(std::ifstream &&stream) : m_stream(stream), m_offsets(std::vector<uint64_t>{}) {
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

#endif // MAIN_UTILS_H
