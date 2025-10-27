//
// Created by sasank on 9/19/25.
//

#ifndef MYERS_DIFF_H
#define MYERS_DIFF_H

#include <functional>
#include <vector>

#include "utils.h"

namespace myers {

        template<typename T>
        class DataView {
        public:
                virtual ~DataView() = default;
                virtual T get(size_t idx) const = 0;
                virtual size_t size() const = 0;
        };


        enum class EditType { Keep, Insert, Delete };

        template<typename T>
        struct Edit {
                EditType type;

                std::optional<T> old_value;
                std::optional<T> new_value;

                Edit(EditType t, std::optional<T> oldv = {}, std::optional<T> newv = {}) :
                    type(t), old_value(std::move(oldv)), new_value(std::move(newv)) {}
        };

        template<typename T>
        std::ostream &operator<<(std::ostream &os, const Edit<T> &e) {
                switch (e.type) {
                        case EditType::Keep:
                                os << "     " << (e.new_value ? e.new_value.value() : T{});
                                break;
                        case EditType::Insert:
                                os << "++++ " << (e.new_value ? e.new_value.value() : T{});
                                break;
                        case EditType::Delete:
                                os << "---- " << (e.old_value ? e.old_value.value() : T{});
                                break;
                }
                return os;
        }

        class Path {
        public:
                int fr_x, fr_y;
                int to_x, to_y;

                Path(int fr_x, int fr_y, int to_x, int to_y) : fr_x(fr_x), fr_y(fr_y), to_x(to_x), to_y(to_y) {};
        };

        inline std::ostream &operator<<(std::ostream &os, const Path &p) {
                os << "(" << p.fr_x << ", " << p.fr_y << ") -> (" << p.to_x << ", " << p.to_y << ")";
                return os;
        }

        template<typename T>
        class Diff {
                std::vector<Path> backtrack(const DataView<T> &a, const DataView<T> &b);
                std::vector<NegIndVector<int>> shortest_edit_path(const DataView<T> &a, const DataView<T> &b);

        public:
                using Comparator = std::function<bool(const T &, const T &)>;

                Diff(Comparator comp = std::equal_to<T>()) : comp_(comp) {}

                std::vector<Edit<T>> diff(const DataView<T> &a, const DataView<T> &b);

        private:
                Comparator comp_;
        };

} // namespace myers

#endif // MYERS_DIFF_H
