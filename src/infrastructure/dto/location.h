#ifndef DTO_LOCATION_H
#define DTO_LOCATION_H

#include <vector>

#include "types.h"

struct DTO_Location {
    LocationID id = -1;
    mutable bool expanded = false;
    uint8_t depth = 0;
    QString name;
    std::vector<DTO_Location> children;

    static decltype(std::bind(std::declval<int (DTO_Location::*)() const>(),
                              std::placeholders::_1)) functor;

    int count_children() const {
        return std::transform_reduce(children.cbegin(), children.cend(), 0, std::plus{}, functor);
    }

    int count() const {
        return expanded ? 1 + count_children() : 1;
    }

    inline void expand() const {
        expanded = true;
    }

    inline void set_depth(uint8_t depth = 0) {
        this->depth = depth++;
        for (auto& i : children)
            i.set_depth(depth);
    }

    const DTO_Location& at(int& index) const {
        if (!index)
            return *this;
        index--;
        for (const auto& i : children) {
            auto count = i.count();
            if (count > index)
                return i.at(index);
            index -= count;
        }
    }
};

#endif // DTO_LOCATION_H
