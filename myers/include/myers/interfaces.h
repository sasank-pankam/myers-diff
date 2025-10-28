//
// Created by sasank on 10/28/25.
//

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

}

#endif // MYERS_DIFF_INTERFACES_H
