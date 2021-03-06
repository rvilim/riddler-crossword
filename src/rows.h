//
// Created by Ryan Vilim on 2019-01-28.
//

#include <bitset>         // std::bitset
#include <vector>

#include "params.h"
#include "masks.h"

#ifndef RIDDLER_CROSSWORD_ROWS_H
#define RIDDLER_CROSSWORD_ROWS_H

std::vector<std::bitset<N> > GetValidRows();
bool ValidRow(std::bitset<N> n);

bool IsValid3Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3);
bool IsValid4Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4);
bool IsValidLastRow(const std::set<std::bitset<N>, MaskCmp>& masks, const std::bitset<N>& row1,
                    const std::bitset<N>& row2, const std::bitset<N>& row3, std::bitset<N>& row4);

std::vector<std::bitset<N> > GetValidSymmetricRows(std::vector<std::bitset<N> > valids);
std::bitset<N> ReverseBitset(const std::bitset<N>& row);

bool IsValid4(bool bit1, bool bit2, bool bit3, bool bit4);


#endif //RIDDLER_CROSSWORD_ROWS_H
