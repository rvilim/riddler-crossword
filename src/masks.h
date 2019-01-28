//
// Created by Ryan Vilim on 2019-01-28.
//

#include <bitset>
#include <vector>
#include <array>

#include "params.h"

#ifndef RIDDLER_CROSSWORD_MASKS_H
#define RIDDLER_CROSSWORD_MASKS_H

struct MaskCmp {
    bool operator()(const std::bitset<N>& lhs, const std::bitset<N>& rhs) const {
        return lhs.to_ullong() < rhs.to_ullong();
    }
};

std::array<std::vector<std::bitset<N> >, 1<<N > GetSegmentedMasks();
std::vector<std::bitset<N>> SegmentMask(std::bitset<N> &mask);
std::set<std::bitset<N>, MaskCmp> GetNewMasks(std::bitset<N> &prevrow, std::bitset<N> &currentrow, std::vector<std::bitset<N>> &prevmasks);

#endif //RIDDLER_CROSSWORD_MASKS_H
