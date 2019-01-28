//
// Created by Ryan Vilim on 2019-01-28.
//

#include <bitset>
#include <vector>
#include <array>

#include "params.h"

#ifndef RIDDLER_CROSSWORD_MASKS_H
#define RIDDLER_CROSSWORD_MASKS_H

std::array<std::vector<std::bitset<N> >, 1<<N > GetSegmentedMasks();
std::vector<std::bitset<N>> SegmentMask(std::bitset<N> &mask);

#endif //RIDDLER_CROSSWORD_MASKS_H
